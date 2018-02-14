//original source https://github.com/d-snp/Farseer-Physics/blob/master/SourceFiles/Common/TextureTools/TextureConverter.cs

#include "../../submodules/BaluRender/BaluLib/Source/Math/matrix.h"
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
		VerticesDetectionType GetPolygonDetectionType();
		void SetPolygonDetectionType(VerticesDetectionType value);
		/// <summary>
		/// Will detect texture 'holes' if set to true. Slows down the detection. Default is false.
		/// </summary>
		bool GetHoleDetection();
		void SetHoleDetection(bool value);
		//}

		/// <summary>
		/// Will detect texture multiple 'solid' isles if set to true. Slows down the detection. Default is false.
		/// </summary>
		bool GetMultipartDetection();
		void SetMultipartDetection(bool value);

		/// <summary>
		/// Will optimize the vertex positions along the interpolated normal between two edges about a half pixel (post processing). Default is false.
		/// </summary>
		bool GetPixelOffsetOptimization();
		void SetPixelOffsetOptimization(bool value);

		/// <summary>
		/// Can be used for scaling.
		/// </summary>
		TMatrix2 GetTransform();
		void SetTransform(TMatrix2 value);

		/// <summary>
		/// Alpha (coverage) tolerance. Default is 20: Every pixel with a coverage value equal or greater to 20 will be counts as solid.
		/// </summary>
		char GetAlphaTolerance();
		void SetAlphaTolerance(unsigned int value);
		/// <summary>
		/// Default is 1.5f.
		/// </summary>
		float GetHullTolerance();
		void SetHullTolerance(float value);

		TextureConverter();

		TextureConverter(Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform);

		TextureConverter(unsigned int* data, int data_length, int width);

		TextureConverter(unsigned int* data, int data_length, int width, Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform);
	private:
		void Initialize(unsigned int* data, int data_length, Nullable<int> width, Nullable<char> alphaTolerance, Nullable<float> hullTolerance,
			Nullable<bool> holeDetection, Nullable<bool> multipartDetection, Nullable<bool> pixelOffsetOptimization, Nullable<TMatrix2> transform);

		void SetTextureData(unsigned int* data, int data_length, int width);
	public:
		/// <summary>
		/// Detects the vertices of the supplied texture data. (PolygonDetectionType.Integrated)
		/// </summary>
		/// <param name="data">The texture data.</param>
		/// <param name="width">The texture width.</param>
		/// <returns></returns>
		static	Vertices DetectVertices(unsigned int* data, int data_length, int width);

		/// <summary>
		/// Detects the vertices of the supplied texture data.
		/// </summary>
		/// <param name="data">The texture data.</param>
		/// <param name="width">The texture width.</param>
		/// <param name="holeDetection">if set to <c>true</c> it will perform hole detection.</param>
		/// <returns></returns>
		static Vertices DetectVertices(unsigned int* data, int data_length, int width, bool holeDetection);

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
		static std::vector<Vertices> DetectVertices(unsigned int* data, int data_length, int width, float hullTolerance, char alphaTolerance, bool multiPartDetection, bool holeDetection);

		std::vector<Vertices> DetectVertices();
	private:
		void ApplyTriangulationCompatibleWinding(std::vector<Vertices>& detectedPolygons);

		void ApplyTransform(std::vector<Vertices>& detectedPolygons);

		int _tempIsSolidX;
		int _tempIsSolidY;
	public:
		bool IsSolid(TVec2 v);

		bool IsSolid(int x, int y);

		bool IsSolid(int index);

		bool InBounds(TVec2 coord);

	private:

		/// <summary>
		/// Function to search for an entrance point of a hole in a polygon. It searches the polygon from top to bottom between the polygon edges.
		/// </summary>
		/// <param name="polygon">The polygon to search in.</param>
		/// <param name="lastHoleEntrance">The last entrance point.</param>
		/// <returns>The next holes entrance point. Null if ther are no holes.</returns>
		Nullable<TVec2> SearchHoleEntrance(Vertices polygon, Nullable<TVec2> lastHoleEntrance);

		bool DistanceToHullAcceptableHoles(Vertices polygon, TVec2 point, bool higherDetail);

		bool DistanceToHullAcceptable(Vertices polygon, TVec2 point, bool higherDetail);

		bool InPolygon(Vertices polygon, TVec2 point);

		Nullable<TVec2> GetTopMostVertex(Vertices vertices);

		float GetTopMostCoord(Vertices vertices);

		float GetBottomMostCoord(Vertices vertices);

		std::vector<float> SearchCrossingEdgesHoles(Vertices polygon, int y);

		/// <summary>
		/// Searches the polygon for the x coordinates of the edges that cross the specified y coordinate.
		/// </summary>
		/// <param name="polygon">Polygon to search in.</param>
		/// <param name="y">Y coordinate to check for edges.</param>
		/// <returns>Descending sorted list of x coordinates of edges that cross the specified y coordinate.</returns>
		std::vector<float> SearchCrossingEdges(Vertices polygon, int y);

		bool SplitPolygonEdge(Vertices polygon, TVec2 coordInsideThePolygon, int& vertex1Index, int& vertex2Index);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="entrance"></param>
		/// <param name="last"></param>
		/// <returns></returns>
		Vertices CreateSimplePolygon(TVec2 entrance, TVec2 last);

		bool SearchNearPixels(bool searchingForSolidPixel, TVec2& current, TVec2& foundPixel);

		bool IsNearPixel(TVec2& current, TVec2& near);

		bool SearchHullEntrance(TVec2& entrance);

		/// <summary>
		/// Searches for the next shape.
		/// </summary>
		/// <param name="detectedPolygons">Already detected polygons.</param>
		/// <param name="start">Search start coordinate.</param>
		/// <param name="entrance">Returns the found entrance coordinate. Null if no other shapes found.</param>
		/// <returns>True if a new shape was found.</returns>
		bool SearchNextHullEntrance(std::vector<Vertices> detectedPolygons, TVec2 start, Nullable<TVec2>& entrance);

		bool GetNextHullPoint(TVec2& last, TVec2& current, TVec2& next);

		bool SearchForOutstandingVertex(Vertices hullArea, TVec2& outstanding);

		int GetIndexOfFirstPixelToCheck(TVec2& last, TVec2& current);
	};
}
