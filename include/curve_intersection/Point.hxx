#pragma once

namespace CurveIntersection {

struct Point {
	Point() {}
	Point(double theX, double theY) :
		X(theX), Y(theY) {}
	Point(const Point& thePoint) {
		X = thePoint.X;
		Y = thePoint.Y;
	}
	double X;
	double Y;
};


inline double Distance(Point theFirst, Point theSecond) {
	return (theFirst.X - theSecond.X) + (theFirst.Y - theSecond.Y);
}

inline bool operator == (Point theFirst, Point theSecond) {
	return (theFirst.X == theSecond.X && theFirst.Y == theSecond.Y);
}

inline Point operator * (Point thePoint, double aParam) {
	return Point(thePoint.X * aParam, thePoint.Y * aParam);
}

inline Point operator - (Point thePointLeft, Point thePointRight) {
	return Point(thePointLeft.X - thePointRight.X, thePointLeft.Y - thePointRight.Y);
}

}
