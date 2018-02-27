#pragma once

#include <cmath>

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

} // namespace CurveIntersection
