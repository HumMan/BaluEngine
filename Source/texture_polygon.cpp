//original source https://github.com/d-snp/Farseer-Physics/blob/master/SourceFiles/Common/TextureTools/TextureConverter.cs

#include "../../BaluLib/Source/Math/Matrix.h"
#include <vector>
#include <algorithm> 

#include "polygon_vertices.h"

using namespace FarseerPhysics_Common;

namespace FarseerPhysics_Common_TextureTools
{
	template<class T>
	class Nullable
	{
		bool is_null;
		T value;
	public:
		Nullable()
		{
			is_null = true;
		}
		Nullable(const T& value)
		{
			this->value = value;
			is_null = false;
		}
		Nullable(T* ref_value)
		{
			if (ref_value != nullptr)
			{
				is_null = false;
				this->value = *ref_value;
			}
			else
			{
				is_null = true;
			}
		}
		void operator=(const T& value)
		{
			this->value = value;
			is_null = false;
		}
		bool IsNull()
		{
			return is_null;
		}
		bool HasValue()
		{
			return !is_null;
		}
		const T& Value()
		{
			return value;
		}
	};

	// User contribution from Sickbattery aka David Reschke.

	/// <summary>
	/// The detection type affects the resulting polygon data.
	/// </summary>
	enum VerticesDetectionType
	{
		/// <summary>
		/// Holes are integrated into the main polygon.
		/// </summary>
		Integrated = 0,

		/// <summary>
		/// The data of the main polygon and hole polygons is returned separately.
		/// </summary>
		Separated = 1
	};

	class TextureConverter
	{
	private:
		const int ClosepixelsLength = 8;

		/// <summary>
		/// This array is ment to be readonly.
		/// It's not because it is accessed very frequently.
		/// </summary>
		std::vector<std::vector<int>> _closePixels;

		unsigned int *_data;
		int _dataLength;
		int _width;
		int _height;

		VerticesDetectionType _polygonDetectionType;

		unsigned int _alphaTolerance;
		float _hullTolerance;

		bool _holeDetection;
		bool _multipartDetection;
		bool _pixelOffsetOptimization;

		TMatrix2 _transform;

		void InitFields()
		{
			_transform = TMatrix2::GetIdentity();
			_closePixels = { { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } };

		}
	public:
		/// <summary>
		/// Get or set the polygon detection type.
		/// </summary>
		VerticesDetectionType GetPolygonDetectionType()
		{
			return _polygonDetectionType;
		}
		void SetPolygonDetectionType(VerticesDetectionType value)
		{
			_polygonDetectionType = value;
		}

		/// <summary>
		/// Will detect texture 'holes' if set to true. Slows down the detection. Default is false.
		/// </summary>
		bool GetHoleDetection()
		{
			return _holeDetection;
		}
		void SetHoleDetection(bool value)
		{
			_holeDetection = value;
		}
		//}

		/// <summary>
		/// Will detect texture multiple 'solid' isles if set to true. Slows down the detection. Default is false.
		/// </summary>
		bool GetMultipartDetection()
		{
			return _multipartDetection;
		}
		void SetMultipartDetection(bool value)
		{
			_multipartDetection = value;
		}

		/// <summary>
		/// Will optimize the vertex positions along the interpolated normal between two edges about a half pixel (post processing). Default is false.
		/// </summary>
		bool GetPixelOffsetOptimization()
		{
			return _pixelOffsetOptimization;
		}
		void SetPixelOffsetOptimization(bool value)
		{
			_pixelOffsetOptimization = value;
		}

		/// <summary>
		/// Can be used for scaling.
		/// </summary>
		TMatrix2 GetTransform()
		{
			return _transform;
		}
		void SetTransform(TMatrix2 value)
		{
			_transform = value;
		}

		/// <summary>
		/// Alpha (coverage) tolerance. Default is 20: Every pixel with a coverage value equal or greater to 20 will be counts as solid.
		/// </summary>
		char GetAlphaTolerance()
		{
			return (char)(_alphaTolerance >> 24);
		}
		void SetAlphaTolerance(unsigned int value)
		{
			_alphaTolerance = (unsigned int)value << 24;
		}
		/// <summary>
		/// Default is 1.5f.
		/// </summary>
		float GetHullTolerance()
		{
			return _hullTolerance;
		}
		void SetHullTolerance(float value)
		{
			if (value > 4.0f)
			{
				_hullTolerance = 4.0f;
			}
			else if (value < 0.9f)
			{
				_hullTolerance = 0.9f;
			}
			else
			{
				_hullTolerance = value;
			}
		}

		TextureConverter()
		{
			Initialize(nullptr, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
		}

		TextureConverter(Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform)
		{
			Initialize(nullptr, 0, nullptr, alphaTolerance, hullTolerance, holeDetection,
				multipartDetection, pixelOffsetOptimization, transform);
		}

		TextureConverter(unsigned int* data, int data_length, int width)
		{
			Initialize(data, data_length, width, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
		}

		TextureConverter(unsigned int* data, int data_length, int width, Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform)
		{
			Initialize(data, data_length, width, alphaTolerance, hullTolerance, holeDetection,
				multipartDetection, pixelOffsetOptimization, transform);
		}
	private:
		void Initialize(unsigned int* data, int data_length, Nullable<int> width, Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform)
		{
			if (data != nullptr && !width.HasValue())
				throw std::invalid_argument("'width' can't be nullptr if 'data' is set.");

			if (data == nullptr && width.HasValue())
				throw std::invalid_argument("'data' can't be nullptr if 'width' is set.");

			if (data != nullptr && width.HasValue())
				SetTextureData(data, data_length, width.Value());

			if (alphaTolerance.HasValue())
				SetAlphaTolerance(alphaTolerance.Value());
			else
				SetAlphaTolerance(20);

			if (hullTolerance.HasValue())
				SetHullTolerance(hullTolerance.Value());
			else
				SetHullTolerance(1.5f);

			if (holeDetection.HasValue())
				SetHoleDetection(holeDetection.Value());
			else
				SetHoleDetection(false);

			if (multipartDetection.HasValue())
				SetMultipartDetection(multipartDetection.Value());
			else
				SetMultipartDetection(false);

			if (pixelOffsetOptimization.HasValue())
				SetPixelOffsetOptimization(pixelOffsetOptimization.Value());
			else
				SetPixelOffsetOptimization(false);

			if (transform.HasValue())
				SetTransform(transform.Value());
			else
				SetTransform(TMatrix2::GetIdentity());
		}

		void SetTextureData(unsigned int* data, int data_length, int width)
		{
			if (data == nullptr)
				throw std::invalid_argument("'data' can't be nullptr.");

			if (data_length < 4)
				throw std::out_of_range("'data' length can't be less then 4. Your texture must be at least 2 x 2 pixels in size.");

			if (width < 2)
				throw std::out_of_range("'width' can't be less then 2. Your texture must be at least 2 x 2 pixels in size.");

			if (data_length % width != 0)
				throw std::invalid_argument("'width' has an invalid value.");

			_data = data;
			_dataLength = data_length;
			_width = width;
			_height = _dataLength / width;
		}
	public:
		/// <summary>
		/// Detects the vertices of the supplied texture data. (PolygonDetectionType.Integrated)
		/// </summary>
		/// <param name="data">The texture data.</param>
		/// <param name="width">The texture width.</param>
		/// <returns></returns>
		static	Vertices DetectVertices(unsigned int* data, int data_length, int width)
		{
			TextureConverter tc(data, data_length, width);

			std::vector<Vertices> detectedVerticesList = tc.DetectVertices();

			return detectedVerticesList[0];
		}

		/// <summary>
		/// Detects the vertices of the supplied texture data.
		/// </summary>
		/// <param name="data">The texture data.</param>
		/// <param name="width">The texture width.</param>
		/// <param name="holeDetection">if set to <c>true</c> it will perform hole detection.</param>
		/// <returns></returns>
		static Vertices DetectVertices(unsigned int* data, int data_length, int width, bool holeDetection)
		{
			TextureConverter tc(data, data_length, width);
			tc.SetHoleDetection(holeDetection);

			std::vector<Vertices> detectedVerticesList = tc.DetectVertices();

			return detectedVerticesList[0];
		}

		/// <summary>
		/// Detects the vertices of the supplied texture data.
		/// </summary>
		/// <param name="data">The texture data.</param>
		/// <param name="width">The texture width.</param>
		/// <param name="holeDetection">if set to <c>true</c> it will perform hole detection.</param>
		/// <param name="hullTolerance">The hull tolerance.</param>
		/// <param name="alphaTolerance">The alpha tolerance.</param>
		/// <param name="multiPartDetection">if set to <c>true</c> it will perform multi part detection.</param>
		/// <returns></returns>
		static std::vector<Vertices> DetectVertices(unsigned int* data, int data_length, int width, float hullTolerance, char alphaTolerance, bool multiPartDetection, bool holeDetection)
		{
			TextureConverter tc(data, data_length, width);
			tc.SetHullTolerance(hullTolerance);
			tc.SetAlphaTolerance(alphaTolerance);
			tc.SetMultipartDetection(multiPartDetection);
			tc.SetHoleDetection(holeDetection);

			std::vector<Vertices> detectedVerticesList = tc.DetectVertices();
			std::vector<Vertices> result = std::vector<Vertices>();

			for (int i = 0; i < detectedVerticesList.size(); i++)
			{
				result.push_back(detectedVerticesList[i]);
			}

			return result;
		}

		std::vector<Vertices> DetectVertices()
		{

			if (_data == nullptr)
				throw std::exception("'_data' can't be nullptr. You have to use SetTextureData(unsigned int* data, int width) before calling this method.");

			if (_dataLength < 4)
				throw std::exception("'_data' length can't be less then 4. Your texture must be at least 2 x 2 pixels in size. "
				"You have to use SetTextureData(unsigned int* data, int width) before calling this method.");

			if (_width < 2)
				throw std::exception("'_width' can't be less then 2. Your texture must be at least 2 x 2 pixels in size. "
				"You have to use SetTextureData(unsigned int* data, int width) before calling this method.");

			if (_dataLength % _width != 0)
				throw std::exception("'_width' has an invalid value. You have to use SetTextureData(unsigned int* data, int width) before calling this method.");

			std::vector<Vertices> detectedPolygons;

			Nullable<TVec2> holeEntrance;
			Nullable<TVec2> polygonEntrance;

			std::vector<TVec2> blackList = std::vector<TVec2>();

			bool searchOn;
			do
			{
				Vertices polygon;
				if (detectedPolygons.size() == 0)
				{
					// First pass / single polygon
					polygon = Vertices(CreateSimplePolygon(TVec2(0), TVec2(0)));

					if (polygon.size() > 2)
						polygonEntrance = GetTopMostVertex(polygon);
				}
				else if (polygonEntrance.HasValue())
				{
					// Multi pass / multiple polygons
					polygon = Vertices(CreateSimplePolygon(polygonEntrance.Value(), TVec2(polygonEntrance.Value()[0] - 1.0f, polygonEntrance.Value()[1])));
				}
				else
					break;

				searchOn = false;


				if (polygon.size() > 2)
				{
					if (_holeDetection)
					{
						do
						{
							holeEntrance = SearchHoleEntrance(polygon, holeEntrance);

							if (holeEntrance.HasValue())
							{
								if (std::find(blackList.begin(), blackList.end(), holeEntrance.Value()) == blackList.end())
								{
									blackList.push_back(holeEntrance.Value());
									Vertices holePolygon = CreateSimplePolygon(holeEntrance.Value(),
										TVec2(holeEntrance.Value()[0] + 1, holeEntrance.Value()[1]));

									if (holePolygon.size() > 2)
									{
										switch (_polygonDetectionType)
										{
										case VerticesDetectionType::Integrated:

											// Add first hole polygon vertex to close the hole polygon.
											holePolygon.push_back(holePolygon[0]);

											int vertex1Index, vertex2Index;
											if (SplitPolygonEdge(polygon, holeEntrance.Value(), vertex1Index, vertex2Index))
												polygon.insert(polygon.begin() + vertex2Index, holePolygon.begin(), holePolygon.end());

											break;

										case VerticesDetectionType::Separated:

											polygon.GetHoles().push_back(holePolygon);
											break;
										}
									}
								}
								else
									break;
							}
							else
								break;
						} while (true);
					}

					detectedPolygons.push_back(polygon);
				}

				if (_multipartDetection || polygon.size() <= 2)
				{
					if (SearchNextHullEntrance(detectedPolygons, polygonEntrance.Value(), polygonEntrance))
						searchOn = true;
				}
			} while (searchOn);

			if (detectedPolygons.size() == 0)
				throw std::exception("Couldn't detect any vertices.");

			// Post processing.
			if (GetPolygonDetectionType() == VerticesDetectionType::Separated) // Only when VerticesDetectionType.Separated? -> Recheck.
				ApplyTriangulationCompatibleWinding(detectedPolygons);

			if (_transform != TMatrix2::GetIdentity())
				ApplyTransform(detectedPolygons);

			return detectedPolygons;
		}
	private:
		void ApplyTriangulationCompatibleWinding(std::vector<Vertices>& detectedPolygons)
		{
			for (int i = 0; i < detectedPolygons.size(); i++)
			{
				std::reverse(detectedPolygons[i].begin(), detectedPolygons[i].end());

				if (detectedPolygons[i].GetHoles().size() > 0)
				{
					for (int j = 0; j < detectedPolygons[i].GetHoles().size(); j++)
						std::reverse(detectedPolygons[i].GetHoles()[j].begin(), detectedPolygons[i].GetHoles()[j].end());
				}
			}
		}

		void ApplyTransform(std::vector<Vertices>& detectedPolygons)
		{
			for (int i = 0; i < detectedPolygons.size(); i++)
				detectedPolygons[i].Transform(_transform);
		}

		int _tempIsSolidX;
		int _tempIsSolidY;
	public:
		bool IsSolid(TVec2 v)
		{
			_tempIsSolidX = (int)v[0];
			_tempIsSolidY = (int)v[1];

			if (_tempIsSolidX >= 0 && _tempIsSolidX < _width && _tempIsSolidY >= 0 && _tempIsSolidY < _height)
				return (_data[_tempIsSolidX + _tempIsSolidY * _width] >= _alphaTolerance);
			//return ((_data[_tempIsSolidX + _tempIsSolidY * _width] & 0xFF000000) >= _alphaTolerance);

			return false;
		}

		bool IsSolid(int x, int y)
		{
			if (x >= 0 && x < _width && y >= 0 && y < _height)
				return (_data[x + y * _width] >= _alphaTolerance);
			//return ((_data[x + y * _width] & 0xFF000000) >= _alphaTolerance);

			return false;
		}

		bool IsSolid(int index)
		{
			if (index >= 0 && index < _dataLength)
				return (_data[index] >= _alphaTolerance);
			//return ((_data[index] & 0xFF000000) >= _alphaTolerance);

			return false;
		}

		bool InBounds(TVec2 coord)
		{
			return (coord[0] >= 0.0f && coord[0] < _width && coord[1] >= 0.0f && coord[1] < _height);
		}

	private:

		/// <summary>
		/// Function to search for an entrance point of a hole in a polygon. It searches the polygon from top to bottom between the polygon edges.
		/// </summary>
		/// <param name="polygon">The polygon to search in.</param>
		/// <param name="lastHoleEntrance">The last entrance point.</param>
		/// <returns>The next holes entrance point. Null if ther are no holes.</returns>
		Nullable<TVec2> SearchHoleEntrance(Vertices polygon, Nullable<TVec2> lastHoleEntrance)
		{
			if (polygon.size() == 0)
				throw std::invalid_argument("'polygon' can't be nullptr.");

			if (polygon.size() < 3)
				throw std::invalid_argument("'polygon.MainPolygon.size()' can't be less then 3.");


			std::vector<float> xCoords;
			Nullable<TVec2> entrance;

			int startY;
			int endY;

			int lastSolid = 0;
			bool foundSolid;
			bool foundTransparent;

			// Set start y coordinate.
			if (lastHoleEntrance.HasValue())
			{
				// We need the y coordinate only.
				startY = (int)lastHoleEntrance.Value()[1];
			}
			else
			{
				// Start from the top of the polygon if last entrance == nullptr.
				startY = (int)GetTopMostCoord(polygon);
			}

			// Set the end y coordinate.
			endY = (int)GetBottomMostCoord(polygon);

			if (startY > 0 && startY < _height && endY > 0 && endY < _height)
			{
				// go from top to bottom of the polygon
				for (int y = startY; y <= endY; y++)
				{
					// get x-coord of every polygon edge which crosses y
					xCoords = SearchCrossingEdges(polygon, y);

					// We need an even number of crossing edges. 
					// It's always a pair of start and end edge: nothing | polygon | hole | polygon | nothing ...
					// If it's not then don't bother, it's probably a peak ...
					// ...which should be filtered out by SearchCrossingEdges() anyway.
					if (xCoords.size() > 1 && xCoords.size() % 2 == 0)
					{
						// Ok, this is short, but probably a little bit confusing.
						// This part searches from left to right between the edges inside the polygon.
						// The problem: We are using the polygon data to search in the texture data.
						// That's simply not accurate, but necessary because of performance.
						for (int i = 0; i < xCoords.size(); i += 2)
						{
							foundSolid = false;
							foundTransparent = false;

							// We search between the edges inside the polygon.
							for (int x = (int)xCoords[i]; x <= (int)xCoords[i + 1]; x++)
							{
								// First pass: IsSolid might return false.
								// In that case the polygon edge doesn't lie on the texture's solid pixel, because of the hull tolearance.
								// If the edge lies before the first solid pixel then we need to skip our transparent pixel finds.

								// The algorithm starts to search for a relevant transparent pixel (which indicates a possible hole) 
								// after it has found a solid pixel.

								// After we've found a solid and a transparent pixel (a hole's left edge) 
								// we search for a solid pixel again (a hole's right edge).
								// When found the distance of that coodrinate has to be greater then the hull tolerance.

								if (IsSolid(x, y))
								{
									if (!foundTransparent)
									{
										foundSolid = true;
										lastSolid = x;
									}

									if (foundSolid && foundTransparent)
									{
										entrance = new TVec2(lastSolid, y);

										if (DistanceToHullAcceptable(polygon, entrance.Value(), true))
											return entrance;

										entrance = nullptr;
										break;
									}
								}
								else
								{
									if (foundSolid)
										foundTransparent = true;
								}
							}
						}
					}
					else
					{
						//if (xCoords.size() % 2 == 0)
						//Debug.WriteLine("SearchCrossingEdges() % 2 != 0");
					}
				}
			}

			return nullptr;
		}

		bool DistanceToHullAcceptableHoles(Vertices polygon, TVec2 point, bool higherDetail)
		{
			if (polygon.size() < 3)
				throw std::invalid_argument("'polygon.MainPolygon.size()' can't be less then 3.");

			// Check the distance to main polygon.
			if (DistanceToHullAcceptable(polygon, point, higherDetail))
			{
				for (int i = 0; i < polygon.GetHoles().size(); i++)
				{
					// If there is one distance not acceptable then return false.
					if (!DistanceToHullAcceptable(polygon.GetHoles()[i], point, higherDetail))
						return false;
				}

				// All distances are larger then _hullTolerance.
				return true;
			}

			// Default to false.
			return false;
		}

		bool DistanceToHullAcceptable(Vertices polygon, TVec2 point, bool higherDetail)
		{
			if (polygon.size() < 3)
				throw std::invalid_argument("'polygon.size()' can't be less then 3.");


			TVec2 edgeVertex2 = polygon[polygon.size() - 1];
			TVec2 edgeVertex1;

			if (higherDetail)
			{
				for (int i = 0; i < polygon.size(); i++)
				{
					edgeVertex1 = polygon[i];
					if (DistanceBetweenPointSegment(point, TSegment<float, 2>(edgeVertex1, edgeVertex2)) <= _hullTolerance || point.Distance(edgeVertex1) <= _hullTolerance)
						return false;

					edgeVertex2 = polygon[i];
				}

				return true;
			}
			else
			{
				for (int i = 0; i < polygon.size(); i++)
				{
					edgeVertex1 = polygon[i];

					if (DistanceBetweenPointSegment(point, TSegment<float, 2>(edgeVertex1, edgeVertex2)) <= _hullTolerance)
						return false;

					edgeVertex2 = polygon[i];
				}

				return true;
			}
		}

		bool InPolygon(Vertices polygon, TVec2 point)
		{
			bool inPolygon = !DistanceToHullAcceptableHoles(polygon, point, true);

			if (!inPolygon)
			{
				std::vector<float> xCoords = SearchCrossingEdgesHoles(polygon, (int)point[1]);

				if (xCoords.size() > 0 && xCoords.size() % 2 == 0)
				{
					for (int i = 0; i < xCoords.size(); i += 2)
					{
						if (xCoords[i] <= point[0] && xCoords[i + 1] >= point[0])
							return true;
					}
				}

				return false;
			}

			return true;
		}

		Nullable<TVec2> GetTopMostVertex(Vertices vertices)
		{
			float topMostValue = std::numeric_limits<float>().max();
			Nullable<TVec2> topMost;

			for (int i = 0; i < vertices.size(); i++)
			{
				if (topMostValue > vertices[i][1])
				{
					topMostValue = vertices[i][1];
					topMost = vertices[i];
				}
			}

			return topMost;
		}

		float GetTopMostCoord(Vertices vertices)
		{
			float returnValue = std::numeric_limits<float>().max();

			for (int i = 0; i < vertices.size(); i++)
			{
				if (returnValue > vertices[i][1])
				{
					returnValue = vertices[i][1];
				}
			}

			return returnValue;
		}

		float GetBottomMostCoord(Vertices vertices)
		{
			float returnValue = std::numeric_limits<float>().lowest();

			for (int i = 0; i < vertices.size(); i++)
			{
				if (returnValue < vertices[i][1])
				{
					returnValue = vertices[i][1];
				}
			}

			return returnValue;
		}

		std::vector<float> SearchCrossingEdgesHoles(Vertices polygon, int y)
		{

			if (polygon.size() < 3)
				throw std::invalid_argument("'polygon.MainPolygon.size()' can't be less then 3.");

			std::vector<float> result = SearchCrossingEdges(polygon, y);


			for (int i = 0; i < polygon.GetHoles().size(); i++)
			{
				auto temp = SearchCrossingEdges(polygon.GetHoles()[i], y);
				result.insert(result.end(), temp.begin(), temp.end());
			}
			std::sort(result.begin(), result.end());
			return result;
		}

		/// <summary>
		/// Searches the polygon for the x coordinates of the edges that cross the specified y coordinate.
		/// </summary>
		/// <param name="polygon">Polygon to search in.</param>
		/// <param name="y">Y coordinate to check for edges.</param>
		/// <returns>Descending sorted list of x coordinates of edges that cross the specified y coordinate.</returns>
		std::vector<float> SearchCrossingEdges(Vertices polygon, int y)
		{
			// sick-o-note:
			// Used to search the x coordinates of edges in the polygon for a specific y coordinate.
			// (Usualy comming from the texture data, that's why it's an int and not a float.)

			std::vector<float> edges = std::vector<float>();

			// current edge
			TVec2 slope;
			TVec2 vertex1;    // i
			TVec2 vertex2;    // i - 1

			// next edge
			TVec2 nextSlope;
			TVec2 nextVertex; // i + 1

			bool addFind;

			if (polygon.size() > 2)
			{
				// There is a gap between the last and the first vertex in the vertex list.
				// We will bridge that by setting the last vertex (vertex2) to the last 
				// vertex in the list.
				vertex2 = polygon[polygon.size() - 1];

				// We are moving along the polygon edges.
				for (int i = 0; i < polygon.size(); i++)
				{
					vertex1 = polygon[i];

					// Approx. check if the edge crosses our y coord.
					if ((vertex1[1] >= y && vertex2[1] <= y) ||
						(vertex1[1] <= y && vertex2[1] >= y))
					{
						// Ignore edges that are parallel to y.
						if (vertex1[1] != vertex2[1])
						{
							addFind = true;
							slope = vertex2 - vertex1;

							// Special threatment for edges that end at the y coord.
							if (vertex1[1] == y)
							{
								// Create preview of the next edge.
								nextVertex = polygon[(i + 1) % polygon.size()];
								nextSlope = vertex1 - nextVertex;

								// Ignore peaks. 
								// If thwo edges are aligned like this: /\ and the y coordinate lies on the top,
								// then we get the same x coord twice and we don't need that.
								if (slope[1] > 0)
									addFind = (nextSlope[1] <= 0);
								else
									addFind = (nextSlope[1] >= 0);
							}

							if (addFind)
								edges.push_back((y - vertex1[1]) / slope[1] * slope[0] + vertex1[0]); // Calculate and add the x coord.
						}
					}

					// vertex1 becomes vertex2 :).
					vertex2 = vertex1;
				}
			}
			std::sort(edges.begin(), edges.end());
			return edges;
		}

		bool SplitPolygonEdge(Vertices polygon, TVec2 coordInsideThePolygon, int& vertex1Index, int& vertex2Index)
		{
			TVec2 slope;
			int nearestEdgeVertex1Index = 0;
			int nearestEdgeVertex2Index = 0;
			bool edgeFound = false;

			float shortestDistance = std::numeric_limits<float>().max();

			bool edgeCoordFound = false;
			TVec2 foundEdgeCoord = TVec2(0);

			std::vector<float> xCoords = SearchCrossingEdges(polygon, (int)coordInsideThePolygon[1]);

			vertex1Index = 0;
			vertex2Index = 0;

			foundEdgeCoord[1] = coordInsideThePolygon[1];

			if (xCoords.size() > 1 && xCoords.size() % 2 == 0)
			{
				float distance;
				for (int i = 0; i < xCoords.size(); i++)
				{
					if (xCoords[i] < coordInsideThePolygon[0])
					{
						distance = coordInsideThePolygon[0] - xCoords[i];

						if (distance < shortestDistance)
						{
							shortestDistance = distance;
							foundEdgeCoord[0] = xCoords[i];

							edgeCoordFound = true;
						}
					}
				}

				if (edgeCoordFound)
				{
					shortestDistance = std::numeric_limits<float>().max();

					int edgeVertex2Index = polygon.size() - 1;

					int edgeVertex1Index;
					for (edgeVertex1Index = 0; edgeVertex1Index < polygon.size(); edgeVertex1Index++)
					{
						TVec2 tempVector1 = polygon[edgeVertex1Index];
						TVec2 tempVector2 = polygon[edgeVertex2Index];

						distance = DistanceBetweenPointSegment(foundEdgeCoord, TSegment<float, 2>(tempVector1, tempVector2));

						if (distance < shortestDistance)
						{
							shortestDistance = distance;

							nearestEdgeVertex1Index = edgeVertex1Index;
							nearestEdgeVertex2Index = edgeVertex2Index;

							edgeFound = true;
						}

						edgeVertex2Index = edgeVertex1Index;
					}

					if (edgeFound)
					{
						slope = polygon[nearestEdgeVertex2Index] - polygon[nearestEdgeVertex1Index];
						slope.Normalize();

						TVec2 tempVector = polygon[nearestEdgeVertex1Index];
						distance = tempVector.Distance(foundEdgeCoord);

						vertex1Index = nearestEdgeVertex1Index;
						vertex2Index = nearestEdgeVertex1Index + 1;

						polygon.insert(polygon.begin() + nearestEdgeVertex1Index, slope*distance + polygon[vertex1Index]);
						polygon.insert(polygon.begin() + nearestEdgeVertex1Index, slope*distance + polygon[vertex2Index]);

						return true;
					}
				}
			}

			return false;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="entrance"></param>
		/// <param name="last"></param>
		/// <returns></returns>
		Vertices CreateSimplePolygon(TVec2 entrance, TVec2 last)
		{
			bool entranceFound = false;
			bool endOfHull = false;

			Vertices polygon(32);
			Vertices hullArea(32);
			Vertices endOfHullArea(32);

			TVec2 current(0);

			// Get the entrance point. //todo: alle möglichkeiten testen
			if (entrance == TVec2(0) || !InBounds(entrance))
			{
				entranceFound = SearchHullEntrance(entrance);

				if (entranceFound)
				{
					current = TVec2(entrance[0] - 1.0f, entrance[1]);
				}
			}
			else
			{
				if (IsSolid(entrance))
				{
					if (IsNearPixel(entrance, last))
					{
						current = last;
						entranceFound = true;
					}
					else
					{
						TVec2 temp;
						if (SearchNearPixels(false, entrance, temp))
						{
							current = temp;
							entranceFound = true;
						}
						else
						{
							entranceFound = false;
						}
					}
				}
			}

			if (entranceFound)
			{
				polygon.push_back(entrance);
				hullArea.push_back(entrance);

				TVec2 next = entrance;

				do
				{
					// Search in the pre vision list for an outstanding point.
					TVec2 outstanding;
					if (SearchForOutstandingVertex(hullArea, outstanding))
					{
						if (endOfHull)
						{
							// We have found the next pixel, but is it on the last bit of the hull?
							if (std::find(endOfHullArea.begin(), endOfHullArea.end(), outstanding) != endOfHullArea.end())
							{
								// Indeed.
								polygon.push_back(outstanding);
							}

							// That's enough, quit.
							break;
						}

						// Add it and remove all vertices that don't matter anymore
						// (all the vertices before the outstanding).
						polygon.push_back(outstanding);
						hullArea.erase(hullArea.begin(), std::find(hullArea.begin(), hullArea.end(), outstanding));
					}

					// Last point gets current and current gets next. Our little spider is moving forward on the hull ;).
					last = current;
					current = next;

					// Get the next point on hull.
					if (GetNextHullPoint(last, current, next))
					{
						// Add the vertex to a hull pre vision list.
						hullArea.push_back(next);
					}
					else
					{
						// Quit
						break;
					}

					if (next == entrance && !endOfHull)
					{
						// It's the last bit of the hull, search on and exit at next found vertex.
						endOfHull = true;
						endOfHullArea.insert(endOfHullArea.end(), hullArea.begin(), hullArea.end());

						// We don't want the last vertex to be the same as the first one, because it causes the triangulation code to crash.
						auto entrance_it = std::find(endOfHullArea.begin(), endOfHullArea.end(), entrance);
						if (entrance_it != endOfHullArea.end())
							endOfHullArea.erase(entrance_it);
					}

				} while (true);
			}

			return polygon;
		}

		bool SearchNearPixels(bool searchingForSolidPixel, TVec2& current, TVec2& foundPixel)
		{
			for (int i = 0; i < ClosepixelsLength; i++)
			{
				int x = (int)current[0] + _closePixels[i][0];
				int y = (int)current[1] + _closePixels[i][1];

				if (!searchingForSolidPixel ^ IsSolid(x, y))
				{
					foundPixel = TVec2(x, y);
					return true;
				}
			}

			// Nothing found.
			foundPixel = TVec2(0);
			return false;
		}

		bool IsNearPixel(TVec2& current, TVec2& near)
		{
			for (int i = 0; i < ClosepixelsLength; i++)
			{
				int x = (int)current[0] + _closePixels[i][0];
				int y = (int)current[1] + _closePixels[i][1];

				if (x >= 0 && x <= _width && y >= 0 && y <= _height)
				{
					if (x == (int)near[0] && y == (int)near[1])
					{
						return true;
					}
				}
			}

			return false;
		}

		bool SearchHullEntrance(TVec2& entrance)
		{
			// Search for first solid pixel.
			for (int y = 0; y <= _height; y++)
			{
				for (int x = 0; x <= _width; x++)
				{
					if (IsSolid(x, y))
					{
						entrance = TVec2(x, y);
						return true;
					}
				}
			}

			// If there are no solid pixels.
			entrance = TVec2(0);
			return false;
		}

		/// <summary>
		/// Searches for the next shape.
		/// </summary>
		/// <param name="detectedPolygons">Already detected polygons.</param>
		/// <param name="start">Search start coordinate.</param>
		/// <param name="entrance">Returns the found entrance coordinate. Null if no other shapes found.</param>
		/// <returns>True if a new shape was found.</returns>
		bool SearchNextHullEntrance(std::vector<Vertices> detectedPolygons, TVec2 start, Nullable<TVec2>& entrance)
		{
			int x;

			bool foundTransparent = false;
			bool inPolygon = false;

			for (int i = (int)start[0] + (int)start[1] * _width; i <= _dataLength; i++)
			{
				if (IsSolid(i))
				{
					if (foundTransparent)
					{
						x = i % _width;
						entrance = new TVec2(x, (i - x) / (float)_width);

						inPolygon = false;
						for (int polygonIdx = 0; polygonIdx < detectedPolygons.size(); polygonIdx++)
						{
							if (InPolygon(detectedPolygons[polygonIdx], entrance.Value()))
							{
								inPolygon = true;
								break;
							}
						}

						if (inPolygon)
							foundTransparent = false;
						else
							return true;
					}
				}
				else
					foundTransparent = true;
			}

			entrance = nullptr;
			return false;
		}

		bool GetNextHullPoint(TVec2& last, TVec2& current, TVec2& next)
		{
			int x;
			int y;

			int indexOfFirstPixelToCheck = GetIndexOfFirstPixelToCheck(last, current);
			int indexOfPixelToCheck;

			for (int i = 0; i < ClosepixelsLength; i++)
			{
				indexOfPixelToCheck = (indexOfFirstPixelToCheck + i) % ClosepixelsLength;

				x = (int)current[0] + _closePixels[indexOfPixelToCheck][0];
				y = (int)current[1] + _closePixels[indexOfPixelToCheck][1];

				if (x >= 0 && x < _width && y >= 0 && y <= _height)
				{
					if (IsSolid(x, y))
					{
						next = TVec2(x, y);
						return true;
					}
				}
			}

			next = TVec2(0);
			return false;
		}

		bool SearchForOutstandingVertex(Vertices hullArea, TVec2& outstanding)
		{
			TVec2 outstandingResult = TVec2(0);
			bool found = false;

			if (hullArea.size() > 2)
			{
				int hullAreaLastPoint = hullArea.size() - 1;

				TVec2 tempVector1;
				TVec2 tempVector2 = hullArea[0];
				TVec2 tempVector3 = hullArea[hullAreaLastPoint];

				// Search between the first and last hull point.
				for (int i = 1; i < hullAreaLastPoint; i++)
				{
					tempVector1 = hullArea[i];

					// Check if the distance is over the one that's tolerable.
					if (DistanceBetweenPointSegment(tempVector1, TSegment<float, 2>(tempVector2, tempVector3)) >= _hullTolerance)
					{
						outstandingResult = hullArea[i];
						found = true;
						break;
					}
				}
			}

			outstanding = outstandingResult;
			return found;
		}

		int GetIndexOfFirstPixelToCheck(TVec2& last, TVec2& current)
		{
			// .: pixel
			// l: last position
			// c: current position
			// f: first pixel for next search

			// f . .
			// l c .
			// . . .

			//Calculate in which direction the last move went and decide over the next pixel to check.
			switch ((int)(current[0] - last[0]))
			{
			case 1:
				switch ((int)(current[1] - last[1]))
				{
				case 1:
					return 1;

				case 0:
					return 0;

				case -1:
					return 7;
				}
				break;

			case 0:
				switch ((int)(current[1] - last[1]))
				{
				case 1:
					return 2;

				case -1:
					return 6;
				}
				break;

			case -1:
				switch ((int)(current[1] - last[1]))
				{
				case 1:
					return 3;

				case 0:
					return 4;

				case -1:
					return 5;
				}
				break;
			}

			return 0;
		}
	};
}