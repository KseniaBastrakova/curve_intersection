#include "CircleCurve.hxx"
#include "Vector.hxx"
#include "Range.hxx"
#include <cmath>

namespace CurveIntersection {

namespace {

static bool IsCorrectCircleData(Point thePoint1, Point thePoint2)
{
	return !(thePoint1 == thePoint2);
}

}

CircleCurve::CircleCurve(Point thePoint1, Point thePoint2) {

	if (IsCorrectCircleData(thePoint1, thePoint2))
	{
		myÑenter = thePoint1;
		const Vector v = thePoint2 - myÑenter;
		const double r = v.Lenght();
		myRadius = r;
	}
	
}

Range CircleCurve::GetRange() const {
	return Range(0.0, 2 * PI);
}

Point CircleCurve::GetPoint(Parameter theParameter) const {
	Point aPoint;
	aPoint.x = myRadius * cos(theParameter) + myÑenter.x;
	aPoint.y = myRadius * sin(theParameter) + myÑenter.y;
	return aPoint;
}

Vector CircleCurve::GetDerivative(Parameter theParameter) const {
	Vector aVector;
	return Vector(-myRadius * sin(theParameter), myRadius * cos(theParameter));
}

Point CircleCurve::GetCenter() const {
	return myÑenter;
}

double CircleCurve::GetRadius() const {
	return myRadius;
}

std::string CircleCurve::GetName() const {
	return "Circle";
}

bool CircleCurve::EqualTo(const ICurve& theOther) const {
	const CircleCurve& aOther = static_cast<const CircleCurve&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetRadius() == this->GetRadius());
}

}

