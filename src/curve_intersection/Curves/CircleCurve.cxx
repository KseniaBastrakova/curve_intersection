#include "CircleCurve.hxx"
#include "Base_Structures.hxx"
#include <cmath>

namespace CurveIntersection {

CircleCurve::CircleCurve(const Point& the�enter, double theRadius) :
	my�enter(the�enter), myRadius(theRadius) {}

Range CircleCurve::GetRange() const {
	return Range(0.0, 2 * PI);
}

Point CircleCurve::GetPoint(Parameter theParameter) const {
	return my�enter + myRadius * Vector(cos(theParameter), sin(theParameter));
}

Vector CircleCurve::GetDerivative(Parameter theParameter) const {
	return myRadius * Vector(-sin(theParameter), cos(theParameter));
}

Point CircleCurve::GetCenter() const {
	return my�enter;
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
