#pragma once
#include <cmath>
#include "Point.hxx"

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

inline bool IsCollinear(Vector vectorFirst, Vector vectorSecound)
{
	return (fabs(VectorMult(vectorFirst, vectorSecound)) < 1e-7);
}

inline bool operator == (Range theFirst, Range theSecond) {
	return (theFirst.Begin == theSecond.Begin && theFirst.End == theSecond.End);
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
