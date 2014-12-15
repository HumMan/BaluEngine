//Original source
//https://github.com/d-snp/Farseer-Physics/blob/master/SourceFiles/Common/Vertices.cs

/*
* Farseer Physics Engine:
* Copyright (c) 2012 Ian Qvist
*/

#include "../../BaluLib/Source/Math/Vec.h"
#include "../../BaluLib/Source/BVolumes/AABB.h"
#include <vector>

namespace FarseerPhysics_Common
{
	const static int MaxPolygonVertices = 8;
	const float Epsilon = 1.192092896e-07f;

	enum PolygonError
	{
		/// <summary>
		/// There were no errors in the polygon
		/// </summary>
		NoError,

		/// <summary>
		/// Polygon must have between 3 and Settings.MaxPolygonVertices vertices.
		/// </summary>
		InvalidAmountOfVertices,

		/// <summary>
		/// Polygon must be simple. This means no overlapping edges.
		/// </summary>
		NotSimple,

		/// <summary>
		/// Polygon must have a counter clockwise winding.
		/// </summary>
		NotCounterClockWise,

		/// <summary>
		/// The polygon is concave, it needs to be convex.
		/// </summary>
		NotConvex,

		/// <summary>
		/// Polygon area is too small.
		/// </summary>
		AreaTooSmall,

		/// <summary>
		/// The polygon has a side that is too short.
		/// </summary>
		SideTooSmall
	};

	class Vertices : public std::vector<TVec2>
	{
		bool _AttachedToBody;
		std::vector<Vertices> _Holes;
	public:
		 Vertices() { }

		 Vertices(int capacity) : std::vector<TVec2>(capacity) { }

		 Vertices(std::vector<TVec2> vertices) :std::vector<TVec2>(vertices)
		{
		}

		 bool GetAttachedToBody()
		 {
			 return _AttachedToBody;
		 }
		 void SetAttachedToBody(bool value)
		 {
			 _AttachedToBody = value;
		 }

			/// <summary>
			/// You can add holes to this collection.
			/// It will get respected by some of the triangulation algoithms, but otherwise not used.
			/// </summary>
		 std::vector<Vertices>& GetHoles()
		 {
			 return _Holes;
		 }
		 void SetHoles(std::vector<Vertices> value)
		 {
			 _Holes = value;
		 }

			/// <summary>
			/// Gets the next index. Used for iterating all the edges with wrap-around.
			/// </summary>
			/// <param name="index">The current index</param>
			int NextIndex(int index)
		{
			return (index + 1 > size() - 1) ? 0 : index + 1;
		}

		/// <summary>
		/// Gets the next vertex. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		TVec2 NextVertex(int index)
		{
			return (*this)[NextIndex(index)];
		}

		/// <summary>
		/// Gets the previous index. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		int PreviousIndex(int index)
		{
			return index - 1 < 0 ? size() - 1 : index - 1;
		}

		/// <summary>
		/// Gets the previous vertex. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		TVec2 PreviousVertex(int index)
		{
			return (*this)[PreviousIndex(index)];
		}

		/// <summary>
		/// Gets the signed area.
		/// If the area is less than 0, it indicates that the polygon is clockwise winded.
		/// </summary>
		/// <returns>The signed area</returns>
		float GetSignedArea()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return 0;

			int i;
			float area = 0;

			for (i = 0; i < size(); i++)
			{
				int j = (i + 1) % size();

				TVec2 vi = (*this)[i];
				TVec2 vj = (*this)[j];

				area += vi[0] * vj[1];
				area -= vi[1] * vj[0];
			}
			area /= 2.0f;
			return area;
		}

		/// <summary>
		/// Gets the area.
		/// </summary>
		/// <returns></returns>
		float GetArea()
		{
			float area = GetSignedArea();
			return (area < 0 ? -area : area);
		}

		/// <summary>
		/// Gets the centroid.
		/// </summary>
		/// <returns></returns>
		TVec2 GetCentroid()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return TVec2(NAN, NAN);

			// Same algorithm is used by Box2D
			TVec2 c = TVec2(0);
			float area = 0.0f;
			const float inv3 = 1.0f / 3.0f;

			for (int i = 0; i < size(); ++i)
			{
				// Triangle vertices.
				TVec2 current = (*this)[i];
				TVec2 next = (i + 1 < size() ? (*this)[i + 1] : (*this)[0]);

				float triangleArea = 0.5f * (current[0] * next[1] - current[1] * next[0]);
				area += triangleArea;

				// Area weighted centroid
				c += (current + next) * (triangleArea * inv3);
			}

			// Centroid
			c *= 1.0f / area;
			return c;
		}

		/// <summary>
		/// Returns an AABB that fully contains this polygon.
		/// </summary>
		TAABB2 GetAABB()
		{
			TAABB2 aabb;
			TVec2 lowerBound = TVec2(std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
			TVec2 upperBound = TVec2(std::numeric_limits<float>().lowest(), std::numeric_limits<float>().lowest());

			for (int i = 0; i < size(); ++i)
			{
				if ((*this)[i][0] < lowerBound[0])
				{
					lowerBound[0] = (*this)[i][0];
				}
				if ((*this)[i][0] > upperBound[0])
				{
					upperBound[0] = (*this)[i][0];
				}

				if ((*this)[i][1] < lowerBound[1])
				{
					lowerBound[1] = (*this)[i][1];
				}
				if ((*this)[i][1] > upperBound[1])
				{
					upperBound[1] = (*this)[i][1];
				}
			}

			aabb.SetLowerBound(lowerBound);
			aabb.SetUpperBound(upperBound);

			return aabb;
		}

		/// <summary>
		/// Translates the vertices with the specified vector.
		/// </summary>
		/// <param name="value">The vector.</param>
		void Translate(TVec2 value)
		{
			assert(!_AttachedToBody, "Translating vertices that are used by a Body can result in unstable behavior. Use Body.Position instead.");

			for (int i = 0; i < size(); i++)
				(*this)[i] += value;

			if (_Holes.size() > 0)
			{
				for(Vertices hole: _Holes)
				{
					hole.Translate(value);
				}
			}
		}

		/// <summary>
		/// Scales the vertices with the specified vector.
		/// </summary>
		/// <param name="value">The Value.</param>
		void Scale(TVec2 value)
		{
			assert(!_AttachedToBody, "Scaling vertices that are used by a Body can result in unstable behavior.");

			for (int i = 0; i < size(); i++)
				(*this)[i] *= value;

			if (_Holes.size() > 0)
			{
				for (Vertices hole : _Holes)
				{
					hole.Scale(value);
				}
			}
		}

		/// <summary>
		/// Rotate the vertices with the defined value in radians.
		/// 
		/// Warning: Using this method on an active set of vertices of a Body,
		/// will cause problems with collisions. Use Body.Rotation instead.
		/// </summary>
		/// <param name="value">The amount to rotate by in radians.</param>
		void Rotate(float value)
		{
			assert(!_AttachedToBody, "Rotating vertices that are used by a Body can result in unstable behavior.");

			float num1 = cosf(value);
			float num2 = sinf(value);

			for (int i = 0; i < size(); i++)
			{
				TVec2 position = (*this)[i];
				(*this)[i] = TVec2((position[0] * num1 + position[1] * -num2), (position[0] * num2 + position[1] * num1));
			}

			if (_Holes.size() > 0)
			{
				for (Vertices hole : _Holes)
				{
					hole.Rotate(value);
				}
			}
		}

		/// <summary>
		/// Determines whether the polygon is convex.
		/// O(n^2) running time.
		/// 
		/// Assumptions:
		/// - The polygon is in counter clockwise order
		/// - The polygon has no overlapping edges
		/// </summary>
		/// <returns>
		/// 	<c>true</c> if it is convex; otherwise, <c>false</c>.
		/// </returns>
		bool IsConvex()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return false;

			//Triangles are always convex
			if (size() == 3)
				return true;

			// Checks the polygon is convex and the interior is to the left of each edge.
			for (int i = 0; i < size(); ++i)
			{
				int next = i + 1 < size() ? i + 1 : 0;
				TVec2 edge = (*this)[next] - (*this)[i];

				for (int j = 0; j < size(); ++j)
				{
					// Don't check vertices on the current edge.
					if (j == i || j == next)
						continue;

					TVec2 r = (*this)[j] - (*this)[i];

					float s = edge[0] * r[1] - edge[1] * r[0];

					if (s <= 0.0f)
						return false;
				}
			}
			return true;
		}

		/// <summary>
		/// Indicates if the vertices are in counter clockwise order.
		/// Warning: If the area of the polygon is 0, it is unable to determine the winding.
		/// </summary>
		bool IsCounterClockWise()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return false;

			return (GetSignedArea() > 0.0f);
		}

		/// <summary>
		/// Forces the vertices to be counter clock wise order.
		/// </summary>
		void ForceCounterClockWise()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return;

			if (!IsCounterClockWise())
				std::reverse((*this).begin(), (*this).end());
		}

		/// <summary>
		/// Checks if the vertices forms an simple polygon by checking for edge crossings.
		/// </summary>
		bool IsSimple()
		{
			//The simplest polygon which can exist in the Euclidean plane has 3 sides.
			if (size() < 3)
				return false;

			for (int i = 0; i < size(); ++i)
			{
				TVec2 a1 = (*this)[i];
				TVec2 a2 = NextVertex(i);
				for (int j = i + 1; j < size(); ++j)
				{
					TVec2 b1 = (*this)[j];
					TVec2 b2 = NextVertex(j);

					TVec2 temp;

					if (SegmentSegmentCollide(TSegment<float, 2>(a1, a2), TSegment<float, 2>(b1, b2)))
						return false;
				}
			}
			return true;
		}

		/// <summary>
		/// Checks if the polygon is valid for use in the engine.
		///
		/// Performs a full check, for simplicity, convexity,
		/// orientation, minimum angle, and volume.
		/// 
		/// From Eric Jordan's convex decomposition library
		/// </summary>
		/// <returns>PolygonError::NoError if there were no error.</returns>
		PolygonError CheckPolygon()
		{
			if (size() < 3 || size() > MaxPolygonVertices)
				return PolygonError::InvalidAmountOfVertices;

			if (!IsSimple())
				return PolygonError::NotSimple;

			if (GetArea() <= Epsilon)
				return PolygonError::AreaTooSmall;

			if (!IsConvex())
				return PolygonError::NotConvex;

			//Check if the sides are of adequate length.
			for (int i = 0; i < size(); ++i)
			{
				int next = i + 1 < size() ? i + 1 : 0;
				TVec2 edge = (*this)[next] - (*this)[i];
				if (edge.SqrLength() <= Epsilon*Epsilon)
				{
					return PolygonError::SideTooSmall;
				}
			}

			if (!IsCounterClockWise())
				return PolygonError::NotCounterClockWise;

			return PolygonError::NoError;
		}

		/// <summary>
		/// Projects to axis.
		/// </summary>
		/// <param name="axis">The axis.</param>
		/// <param name="min">The min.</param>
		/// <param name="max">The max.</param>
		void ProjectToAxis(TVec2 axis, float& min, float& max)
		{
			// To project a point on an axis use the dot product
			float dotProduct = axis * (*this)[0];
			min = dotProduct;
			max = dotProduct;

			for (int i = 0; i < size(); i++)
			{
				dotProduct = (*this)[i] * axis;
				if (dotProduct < min)
				{
					min = dotProduct;
				}
				else
				{
					if (dotProduct > max)
					{
						max = dotProduct;
					}
				}
			}
		}

		/// <summary>
		/// Winding number test for a point in a polygon.
		/// </summary>
		/// See more info about the algorithm here: http://softsurfer.com/Archive/algorithm_0103/algorithm_0103.htm
		/// <param name="point">The point to be tested.</param>
		/// <returns>-1 if the winding number is zero and the point is outside
		/// the polygon, 1 if the point is inside the polygon, and 0 if the point
		/// is on the polygons edge.</returns>
		int PointInPolygon(TVec2 point)
		{
			// Winding number
			int wn = 0;

			// Iterate through polygon's edges
			for (int i = 0; i < size(); i++)
			{
				// Get points
				TVec2 p1 = (*this)[i];
				TVec2 p2 = (*this)[NextIndex(i)];

				// Test if a point is directly on the edge
				TVec2 edge = p2 - p1;
				float area = MathUtils::Area(p1, p2, point);
				if (area == 0.0f && (point - p1) * edge >= 0.0f && (point - p2)* edge <= 0.0f)
				{
					return 0;
				}
				// Test edge for intersection with ray from point
				if (p1[1] <= point[1])
				{
					if (p2[1] > point[1] && area > 0.0f)
					{
						++wn;
					}
				}
				else
				{
					if (p2[1] <= point[1] && area < 0.0f)
					{
						--wn;
					}
				}
			}
			return (wn == 0 ? -1 : 1);
		}

		/// <summary>
		/// Compute the sum of the angles made between the test point and each pair of points making up the polygon. 
		/// If this sum is 2pi then the point is an interior point, if 0 then the point is an exterior point. 
		/// ref: http://ozviz.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/  - Solution 2 
		/// </summary>
		bool PointInPolygonAngle(TVec2 point)
		{
			double angle = 0;

			// Iterate through polygon's edges
			for (int i = 0; i < size(); i++)
			{
				// Get points
				TVec2 p1 = (*this)[i] - point;
				TVec2 p2 = (*this)[NextIndex(i)] - point;

				angle += MathUtils::VectorAngle(p1, p2);
			}

			if (abs(angle) < M_PI)
			{
				return false;
			}

			return true;
		}

		/// <summary>
		/// Transforms the polygon using the defined matrix.
		/// </summary>
		/// <param name="transform">The matrix to use as transformation.</param>
		void Transform(TMatrix2 transform)
		{
			// Transform main polygon
			for (int i = 0; i < size(); i++)
				(*this)[i] = transform*(*this)[i];

			// Transform holes
			if (_Holes.size() > 0)
			{
				for (int i = 0; i < _Holes.size(); i++)
				{
					std::vector<TVec2>& temp = _Holes[i];
					for (int k = 0; k < temp.size(); k++)
						temp[i] = transform * temp[i];
				}
			}
		}
	};
}