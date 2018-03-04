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

inline bool IsNear(Point theFirst, Point theSecond, double theThreshold)
{
	return fabs(theFirst.x - theSecond.x) < theThreshold && fabs(theFirst.y - theSecond.y) < theThreshold;
}

const double DefaultPointEqualityTolerance = NULL_TOL;
inline bool IsEqual(Point theFirst,
	Point theSecond, double theMaxDiscrepancy = DefaultPointEqualityTolerance)
{
	return IsNear(theFirst, theSecond, theMaxDiscrepancy);
}

} // namespace CurveIntersection
