#pragma once

#include <baluLib.h>
using namespace BaluLib;

#include <vector>

namespace ByazitDecomp
{

	typedef float Scalar;
	typedef TVec<Scalar, 2> Point;
	typedef std::vector<Point> Polygon;

	std::vector<Polygon> DecomposePolygon(Polygon poly);
}