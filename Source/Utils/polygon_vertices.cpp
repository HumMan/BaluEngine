#include "polygon_vertices.h"

#include <algorithm>

using namespace FarseerPhysics_Common;

Vertices::Vertices() { }

Vertices::Vertices(int capacity) { this->reserve(capacity); }

Vertices::Vertices(std::vector<TVec2> vertices) :std::vector<TVec2>(vertices)
{
}

bool Vertices::GetAttachedToBody()
{
	return _AttachedToBody;
}
void Vertices::SetAttachedToBody(bool value)
{
	_AttachedToBody = value;
}

std::vector<Vertices>& Vertices::GetHoles()
{
	return _Holes;
}
void Vertices::SetHoles(std::vector<Vertices> value)
{
	_Holes = value;
}

int Vertices::NextIndex(int index)
{
	return (index + 1 > size() - 1) ? 0 : index + 1;
}

TVec2 Vertices::NextVertex(int index)
{
	return (*this)[NextIndex(index)];
}

int Vertices::PreviousIndex(int index)
{
	return index - 1 < 0 ? size() - 1 : index - 1;
}

TVec2 Vertices::PreviousVertex(int index)
{
	return (*this)[PreviousIndex(index)];
}

float Vertices::GetSignedArea()
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

float Vertices::GetArea()
{
	float area = GetSignedArea();
	return (area < 0 ? -area : area);
}

TVec2 Vertices::GetCentroid()
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

TAABB2 Vertices::GetAABB()
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

void Vertices::Translate(TVec2 value)
{
	if(!_AttachedToBody)
	assert("Translating vertices that are used by a Body can result in unstable behavior. Use Body.Position instead.");

	for (int i = 0; i < size(); i++)
		(*this)[i] += value;

	if (_Holes.size() > 0)
	{
		for (Vertices hole : _Holes)
		{
			hole.Translate(value);
		}
	}
}

void Vertices::Scale(TVec2 value)
{
	if(!_AttachedToBody)
	assert("Scaling vertices that are used by a Body can result in unstable behavior.");

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

void Vertices::Rotate(float value)
{
	if(!_AttachedToBody)
	assert("Rotating vertices that are used by a Body can result in unstable behavior.");

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

bool Vertices::IsConvex()
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

bool Vertices::IsCounterClockWise()
{
	//The simplest polygon which can exist in the Euclidean plane has 3 sides.
	if (size() < 3)
		return false;

	return (GetSignedArea() > 0.0f);
}

void Vertices::ForceCounterClockWise()
{
	//The simplest polygon which can exist in the Euclidean plane has 3 sides.
	if (size() < 3)
		return;

	if (!IsCounterClockWise())
		std::reverse((*this).begin(), (*this).end());
}

bool Vertices::IsSimple()
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

PolygonError Vertices::CheckPolygon()
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

void Vertices::ProjectToAxis(TVec2 axis, float& min, float& max)
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

int Vertices::PointInPolygon(TVec2 point)
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

bool Vertices::PointInPolygonAngle(TVec2 point)
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

void Vertices::Transform(TMatrix2 transform)
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
