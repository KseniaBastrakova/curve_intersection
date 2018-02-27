#pragma once
#include <cmath>

namespace CurveIntersection {

struct Range {
	Range() {}
	Range(double theBegin, double theEnd) :
		Begin(theBegin), End(theEnd) {}
	double Begin;
	double End;
	double Lenght() const {
		return (End - Begin);
	}
};

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

struct Vector {
	Vector() {}
	Vector(double theX, double theY) :
		X(theX), Y(theY) {}
	Vector(const Vector& theVector) {
		X = theVector.X;
		Y = theVector.Y;
	}
	Vector(const Point& point) {
		X = point.X;
		Y = point.Y;
	}
	double Lenght() const {
		return sqrt(X * X + Y * Y);
	}
	double X;
	double Y;
};

inline Vector operator * (Vector theVector, double theScalar) {
	return Vector(theVector.X * theScalar, theVector.Y * theScalar);
}

inline Vector operator * (double theScalar, Vector theVector) {
	return Vector(theVector.X * theScalar, theVector.Y * theScalar);
}

inline double VectorMult(Vector vectorFirst, Vector vectorSecound)
{
	return vectorSecound.X * vectorFirst.Y - vectorSecound.Y * vectorFirst.X;
}

inline Point Rotate(Point point, double alpha) {
	double cosAlpha = cos(alpha);
	double sinAlpha = sin(alpha);
	double oldx = point.X;
	double oldy = point.Y;
	return Point(oldx * cosAlpha - oldy * sinAlpha, oldx * sinAlpha + oldy * cosAlpha);
}


inline bool IsCollinear(Vector vectorFirst, Vector vectorSecound)
{
	return (fabs(VectorMult(vectorFirst, vectorSecound)) < 1e-7);
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

inline bool operator == (Range theFirst, Range theSecond) {
	return (theFirst.Begin == theSecond.Begin && theFirst.End == theSecond.End);
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

struct Box {
	Range myRangeX;
	Range myRangeY;
	Box(Range theRangeX, Range theRangeY) :
		myRangeX(theRangeX), myRangeY(theRangeY) {}
	Point Center() {
		return Point(myRangeX.Begin + (myRangeX.Lenght()) / 2.0, myRangeY.Begin + myRangeY.Lenght() / 2.0);
	}
	bool IsMaxX() {
		return ((myRangeX.Lenght()) > (myRangeY.Lenght()));
	}
	double RCharacteristic;
};

const double PI = 3.14159265358979323846;
const double NULL_TOL = 1e-4;
}
