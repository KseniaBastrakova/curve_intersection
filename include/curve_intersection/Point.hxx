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

inline Point Rotate(Point point, double alpha) {
	double cosAlpha = cos(alpha);
	double sinAlpha = sin(alpha);
	double oldx = point.X;
	double oldy = point.Y;
	return Point(oldx * cosAlpha - oldy * sinAlpha, oldx * sinAlpha + oldy * cosAlpha);
}

inline double Distance(Point theFirst, Point theSecond) {
	return (theFirst.X - theSecond.X) + (theFirst.Y - theSecond.Y);
}

inline bool operator == (Point theFirst, Point theSecond) {
	return (theFirst.X == theSecond.X && theFirst.Y == theSecond.Y);
}

inline Point operator + (Point thePoint, Vector theVector) {
	return Point(thePoint.X + theVector.X, thePoint.Y + theVector.Y);
}
inline Point operator - (Point thePoint) {
	return Point(-thePoint.X, -thePoint.Y);
}

inline Point operator * (Point thePoint, double aParam) {
	return Point(thePoint.X * aParam, thePoint.Y * aParam);
}

inline Point operator - (Point thePointLeft, Point thePointRight) {
	return Point(thePointLeft.X - thePointRight.X, thePointLeft.Y - thePointRight.Y);
}

inline double NormSq(Point thePoint) {
	return (thePoint.X *thePoint.X + thePoint.Y * thePoint.Y);
}
}
