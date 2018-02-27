#pragma once

#include "Point.hxx"
#include <cmath>

namespace CurveIntersection {

struct Vector {
	Vector() :
		Vector(0., 0.) {}
	Vector(double theX, double theY) :
		x(theX), y(theY) {}
	Vector(const Point& thePoint):
		Vector(thePoint.x, thePoint.y) {}
	double Lenght() const {
		return sqrt(x * x + y * y);
	}
	double x;
	double y;
};

inline Vector operator * (Vector theVector, double theScalar) {
	return Vector(theVector.x * theScalar, theVector.y * theScalar);
}

inline Vector operator * (double theScalar, Vector theVector) {
	return Vector(theVector.x * theScalar, theVector.y * theScalar);
}

inline Vector operator / (Vector theVector, double theScalar) {
	return Vector(theVector.x / theScalar, theVector.y / theScalar);
}

inline Point operator + (Point thePoint, Vector theVector) {
	return Point(thePoint.x + theVector.x, thePoint.y + theVector.y);
}

inline double VectorMult(Vector theFirst, Vector theSecond)
{
	return theSecond.x * theFirst.y - theSecond.y * theFirst.x;
}

inline bool IsCollinear(Vector theFirst, Vector theSecond, double theTolerance = 1e-7)
{
	return (fabs(VectorMult(theFirst, theSecond)) < theTolerance);
}

inline Vector operator - (Vector theVector) {
	return Vector(-theVector.x, -theVector.y);
}

inline Vector operator - (Point theEnd, Point theStart) {
	return Vector(theEnd.x - theStart.x, theEnd.y - theStart.y);
}

inline Vector Rotate(Vector theVector, double theAngle) {
	double aCos = cos(theAngle);
	double aSin = sin(theAngle);
	return Vector(theVector.x * aCos - theVector.y * aSin,
		theVector.x * aSin + theVector.y * aCos);
}

}// namespace CurveIntersection
