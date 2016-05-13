#include "polygon_decomp.h"

// Written by Mark Bayazit (darkzerox)
// March 23, 2009
//http://mnbayazit.com/406/bayazit

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;



namespace ByazitDecomp
{


	Scalar min(const Scalar &a, const Scalar &b) {
		return a < b ? a : b;
	}

	bool eq(const Scalar &a, const Scalar &b) {
		return abs(a - b) <= 1e-8;
	}

	int wrap(const int &a, const int &b) {
		return a < 0 ? a % b + b : a % b;
	}

	Scalar srand(const Scalar &min = 0, const Scalar &max = 1) {
		return rand() / (Scalar)RAND_MAX * (max - min) + min;
	}

	template<class T>
	T& at(vector<T> v, int i) {
		return v[wrap(i, v.size())];
	};

	Scalar area(const Point &a, const Point &b, const Point &c) {
		return (((b[0] - a[0])*(c[1] - a[1])) - ((c[0] - a[0])*(b[1] - a[1])));
	}

	bool left(const Point &a, const Point &b, const Point &c) {
		return area(a, b, c) > 0;
	}

	bool leftOn(const Point &a, const Point &b, const Point &c) {
		return area(a, b, c) >= 0;
	}

	bool right(const Point &a, const Point &b, const Point &c) {
		return area(a, b, c) < 0;
	}

	bool rightOn(const Point &a, const Point &b, const Point &c) {
		return area(a, b, c) <= 0;
	}

	bool collinear(const Point &a, const Point &b, const Point &c) {
		return area(a, b, c) == 0;
	}




	bool isReflex(const Polygon &p, const int &i);
	void makeCCW(Polygon &poly);
	void decomposePoly(Polygon poly);

	void makeCCW(Polygon &poly) {
		int br = 0;

		// find bottom right point
		for (int i = 1; i < poly.size(); ++i) {
			if (poly[i][1] < poly[br][1] || (poly[i][1] == poly[br][1] && poly[i][0] > poly[br][0])) {
				br = i;
			}
		}

		// reverse poly if clockwise
		if (!left(at(poly, br - 1), at(poly, br), at(poly, br + 1))) {
			reverse(poly.begin(), poly.end());
		}
	}

	bool isReflex(const Polygon &poly, const int &i) {
		return right(at(poly, i - 1), at(poly, i), at(poly, i + 1));
	}

	Point intersection(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
		Point i;
		Scalar a1, b1, c1, a2, b2, c2, det;
		a1 = p2[1] - p1[1];
		b1 = p1[0] - p2[0];
		c1 = a1 * p1[0] + b1 * p1[1];
		a2 = q2[1] - q1[1];
		b2 = q1[0] - q2[0];
		c2 = a2 * q1[0] + b2 * q1[1];
		det = a1 * b2 - a2*b1;
		if (!eq(det, 0)) { // lines are not parallel
			i[0] = (b2 * c1 - b1 * c2) / det;
			i[1] = (a1 * c2 - a2 * c1) / det;
		}
		return i;
	}

	void swap(int &a, int &b) {
		int c;
		c = a;
		a = b;
		b = c;
	}

	void decomposePoly(Polygon poly, vector<Polygon>& polys, vector<Point>& steinerPoints, vector<Point>& reflexVertices)
	{
		Point upperInt, lowerInt, p, closestVert;
		Scalar upperDist, lowerDist, d, closestDist;
		int upperIndex, lowerIndex, closestIndex = 0;
		Polygon lowerPoly, upperPoly;

		for (int i = 0; i < poly.size(); ++i) {
			if (isReflex(poly, i)) {
				reflexVertices.push_back(poly[i]);
				upperDist = lowerDist = numeric_limits<Scalar>::max();
				for (int j = 0; j < poly.size(); ++j) {
					if (left(at(poly, i - 1), at(poly, i), at(poly, j))
						&& rightOn(at(poly, i - 1), at(poly, i), at(poly, j - 1))) { // if line intersects with an edge
						p = intersection(at(poly, i - 1), at(poly, i), at(poly, j), at(poly, j - 1)); // find the point of intersection
						if (right(at(poly, i + 1), at(poly, i), p)) { // make sure it's inside the poly
							d = poly[i].SqrDistance(p);
							if (d < lowerDist) { // keep only the closest intersection
								lowerDist = d;
								lowerInt = p;
								lowerIndex = j;
							}
						}
					}
					if (left(at(poly, i + 1), at(poly, i), at(poly, j + 1))
						&& rightOn(at(poly, i + 1), at(poly, i), at(poly, j))) {
						p = intersection(at(poly, i + 1), at(poly, i), at(poly, j), at(poly, j + 1));
						if (left(at(poly, i - 1), at(poly, i), p)) {
							d = poly[i].SqrDistance(p);
							if (d < upperDist) {
								upperDist = d;
								upperInt = p;
								upperIndex = j;
							}
						}
					}
				}

				// if there are no vertices to connect to, choose a point in the middle
				if (lowerIndex == (upperIndex + 1) % poly.size()) {
					printf("Case 1: Vertex(%d), lowerIndex(%d), upperIndex(%d), poly.size(%d)\n", i, lowerIndex, upperIndex, (int)poly.size());
					p[0] = (lowerInt[0] + upperInt[0]) / 2;
					p[1] = (lowerInt[1] + upperInt[1]) / 2;
					steinerPoints.push_back(p);

					if (i < upperIndex) {
						lowerPoly.insert(lowerPoly.end(), poly.begin() + i, poly.begin() + upperIndex + 1);
						lowerPoly.push_back(p);
						upperPoly.push_back(p);
						if (lowerIndex != 0) upperPoly.insert(upperPoly.end(), poly.begin() + lowerIndex, poly.end());
						upperPoly.insert(upperPoly.end(), poly.begin(), poly.begin() + i + 1);
					}
					else {
						if (i != 0) lowerPoly.insert(lowerPoly.end(), poly.begin() + i, poly.end());
						lowerPoly.insert(lowerPoly.end(), poly.begin(), poly.begin() + upperIndex + 1);
						lowerPoly.push_back(p);
						upperPoly.push_back(p);
						upperPoly.insert(upperPoly.end(), poly.begin() + lowerIndex, poly.begin() + i + 1);
					}
				}
				else {
					// connect to the closest point within the triangle
					printf("Case 2: Vertex(%d), closestIndex(%d), poly.size(%d)\n", i, closestIndex, (int)poly.size());

					if (lowerIndex > upperIndex) {
						upperIndex += poly.size();
					}
					closestDist = numeric_limits<Scalar>::max();
					for (int j = lowerIndex; j <= upperIndex; ++j) {
						if (leftOn(at(poly, i - 1), at(poly, i), at(poly, j))
							&& rightOn(at(poly, i + 1), at(poly, i), at(poly, j))) {
							d = at(poly, i).SqrDistance(at(poly, j));
							if (d < closestDist) {
								closestDist = d;
								closestVert = at(poly, j);
								closestIndex = j % poly.size();
							}
						}
					}

					if (i < closestIndex) {
						lowerPoly.insert(lowerPoly.end(), poly.begin() + i, poly.begin() + closestIndex + 1);
						if (closestIndex != 0) upperPoly.insert(upperPoly.end(), poly.begin() + closestIndex, poly.end());
						upperPoly.insert(upperPoly.end(), poly.begin(), poly.begin() + i + 1);
					}
					else {
						if (i != 0) lowerPoly.insert(lowerPoly.end(), poly.begin() + i, poly.end());
						lowerPoly.insert(lowerPoly.end(), poly.begin(), poly.begin() + closestIndex + 1);
						upperPoly.insert(upperPoly.end(), poly.begin() + closestIndex, poly.begin() + i + 1);
					}
				}

				// solve smallest poly first
				if (lowerPoly.size() < upperPoly.size()) {
					decomposePoly(lowerPoly, polys, steinerPoints, reflexVertices);
					decomposePoly(upperPoly, polys, steinerPoints, reflexVertices);
				}
				else {
					decomposePoly(upperPoly, polys, steinerPoints, reflexVertices);
					decomposePoly(lowerPoly, polys, steinerPoints, reflexVertices);
				}
				return;
			}
		}
		polys.push_back(poly);
	}

	vector<Polygon> DecomposePolygon(Polygon poly)
	{
		vector<Polygon> polys;
		vector<Point> steinerPoints;
		vector<Point> reflexVertices;
		decomposePoly(poly, polys, steinerPoints, reflexVertices);

		return polys;
	}
}
