#include "curve_intersection/Curves/CircleCurve.hxx"
#include "curve_intersection/Core/Constants.hxx"
#include <cmath>

namespace CurveIntersection {

CircleCurve::CircleCurve(const Point& theÑenter, double theRadius) :
	myÑenter(theÑenter), myRadius(theRadius) {
	if (theRadius < 0.)
		throw std::invalid_argument("radius should not be negative!");
}

Range CircleCurve::GetRange() const {
	return Range(0.0, 2 * PI);
}

Point CircleCurve::GetPoint(Parameter theParameter) const {
	return myÑenter + myRadius * Vector(cos(theParameter), sin(theParameter));
}

Vector CircleCurve::GetDerivative(Parameter theParameter) const {
	return myRadius * Vector(-sin(theParameter), cos(theParameter));
}

Point CircleCurve::TryGetPoint(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 2 * PI)
		throw std::invalid_argument("parameter must be from [0.,2*PI]");
	return GetPoint(theParameter);
}

Vector CircleCurve::TryGetDerivative(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 2 * PI)
		throw std::invalid_argument("parameter must be from [0.,2*PI]");
	return GetDerivative(theParameter);
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
	return (aOther.GetCenter() == this->GetCenter() 
		&& aOther.GetRadius() == this->GetRadius());
}

}
