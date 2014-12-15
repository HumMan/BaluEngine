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

	class Vertices : public std::vector < TVec2 >
	{
		bool _AttachedToBody;
		std::vector<Vertices> _Holes;
	public:
		Vertices();
		Vertices(int capacity);
		Vertices(std::vector<TVec2> vertices);
		bool GetAttachedToBody();
		void SetAttachedToBody(bool value);

		/// <summary>
		/// You can add holes to this collection.
		/// It will get respected by some of the triangulation algoithms, but otherwise not used.
		/// </summary>
		std::vector<Vertices>& GetHoles();
		void SetHoles(std::vector<Vertices> value);

		/// <summary>
		/// Gets the next index. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		int NextIndex(int index);

		/// <summary>
		/// Gets the next vertex. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		TVec2 NextVertex(int index);

		/// <summary>
		/// Gets the previous index. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		int PreviousIndex(int index);

		/// <summary>
		/// Gets the previous vertex. Used for iterating all the edges with wrap-around.
		/// </summary>
		/// <param name="index">The current index</param>
		TVec2 PreviousVertex(int index);

		/// <summary>
		/// Gets the signed area.
		/// If the area is less than 0, it indicates that the polygon is clockwise winded.
		/// </summary>
		/// <returns>The signed area</returns>
		float GetSignedArea();

		/// <summary>
		/// Gets the area.
		/// </summary>
		/// <returns></returns>
		float GetArea();

		/// <summary>
		/// Gets the centroid.
		/// </summary>
		/// <returns></returns>
		TVec2 GetCentroid();

		/// <summary>
		/// Returns an AABB that fully contains this polygon.
		/// </summary>
		TAABB2 GetAABB();

		/// <summary>
		/// Translates the vertices with the specified vector.
		/// </summary>
		/// <param name="value">The vector.</param>
		void Translate(TVec2 value);

		/// <summary>
		/// Scales the vertices with the specified vector.
		/// </summary>
		/// <param name="value">The Value.</param>
		void Scale(TVec2 value);

		/// <summary>
		/// Rotate the vertices with the defined value in radians.
		/// 
		/// Warning: Using this method on an active set of vertices of a Body,
		/// will cause problems with collisions. Use Body.Rotation instead.
		/// </summary>
		/// <param name="value">The amount to rotate by in radians.</param>
		void Rotate(float value);

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
		bool IsConvex();

		/// <summary>
		/// Indicates if the vertices are in counter clockwise order.
		/// Warning: If the area of the polygon is 0, it is unable to determine the winding.
		/// </summary>
		bool IsCounterClockWise();

		/// <summary>
		/// Forces the vertices to be counter clock wise order.
		/// </summary>
		void ForceCounterClockWise();

		/// <summary>
		/// Checks if the vertices forms an simple polygon by checking for edge crossings.
		/// </summary>
		bool IsSimple();

		/// <summary>
		/// Checks if the polygon is valid for use in the engine.
		///
		/// Performs a full check, for simplicity, convexity,
		/// orientation, minimum angle, and volume.
		/// 
		/// From Eric Jordan's convex decomposition library
		/// </summary>
		/// <returns>PolygonError::NoError if there were no error.</returns>
		PolygonError CheckPolygon();

		/// <summary>
		/// Projects to axis.
		/// </summary>
		/// <param name="axis">The axis.</param>
		/// <param name="min">The min.</param>
		/// <param name="max">The max.</param>
		void ProjectToAxis(TVec2 axis, float& min, float& max);

		/// <summary>
		/// Winding number test for a point in a polygon.
		/// </summary>
		/// See more info about the algorithm here: http://softsurfer.com/Archive/algorithm_0103/algorithm_0103.htm
		/// <param name="point">The point to be tested.</param>
		/// <returns>-1 if the winding number is zero and the point is outside
		/// the polygon, 1 if the point is inside the polygon, and 0 if the point
		/// is on the polygons edge.</returns>
		int PointInPolygon(TVec2 point);

		/// <summary>
		/// Compute the sum of the angles made between the test point and each pair of points making up the polygon. 
		/// If this sum is 2pi then the point is an interior point, if 0 then the point is an exterior point. 
		/// ref: http://ozviz.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/  - Solution 2 
		/// </summary>
		bool PointInPolygonAngle(TVec2 point);

		/// <summary>
		/// Transforms the polygon using the defined matrix.
		/// </summary>
		/// <param name="transform">The matrix to use as transformation.</param>
		void Transform(TMatrix2 transform);
	};
}