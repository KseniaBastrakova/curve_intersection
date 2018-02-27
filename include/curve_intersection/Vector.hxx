#pragma once
#include <cmath>
#include "Point.hxx"

namespace CurveIntersection {

struct Vector {
	Vector() :
		Vector(0.,0.) {}
	Vector(double theX, double theY) :
		x(theX), y(theY) {}
	Vector(const Point& thePoint) {
		x = thePoint.x;
		y = thePoint.y;
	}
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

inline Point operator + (Point thePoint, Vector theVector) {
	return Point(thePoint.x + theVector.x, thePoint.y + theVector.y);
}

inline double VectorMult(Vector theFirstVector, Vector theSecondVctor)
{
	return theSecondVctor.x * theFirstVector.y - theSecondVctor.y * theFirstVector.x;
}

inline bool IsCollinear(Vector theFirstVector, Vector theSecondVector)
{
	return (fabs(VectorMult(theFirstVector, theSecondVector)) < 1e-7);
}

inline Vector operator - (Vector theVector) {
	return Vector(-theVector.x, -theVector.y);
}

inline Vector operator - (Point thePointLeft, Point thePointRight) {
	return Vector(thePointLeft.x - thePointRight.x, thePointLeft.y - thePointRight.y);
}

inline Vector Rotate(Vector point, double alpha) {
	double cosAlpha = cos(alpha);
	double sinAlpha = sin(alpha);
	double oldx = point.x;
	double oldy = point.y;
	return Vector(oldx * cosAlpha - oldy * sinAlpha, oldx * sinAlpha + oldy * cosAlpha);
}

}// namespace CurveIntersection
