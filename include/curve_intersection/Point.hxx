#pragma once

#include <cmath>
#include "Base_Structures.hxx"

namespace CurveIntersection {

struct Point {
	Point():
		Point(0., 0.){}
	Point(double theX, double theY) :
		x(theX), y(theY) {}
	double x;
	double y;
};

inline double Distance(Point theFirst, Point theSecond) {
	return sqrt((theFirst.x - theSecond.x) * (theFirst.x - theSecond.x) + (theFirst.y - theSecond.y)
		* (theFirst.y - theSecond.y));
}

inline bool operator == (Point theFirst, Point theSecond) {
	return (theFirst.x == theSecond.x && theFirst.y == theSecond.y);
}

inline bool operator != (Point theFirst, Point theSecond) {
	return (theFirst.x != theSecond.x || theFirst.y != theSecond.y);
}

inline bool IsEqualPoints(Point p1, Point p2, double eps = NULL_TOL)
{
	return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
}

} // namespace CurveIntersection
