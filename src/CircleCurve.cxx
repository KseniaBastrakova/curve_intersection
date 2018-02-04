#include "CircleCurve.hxx"
#include <cmath>
Range CircleCurve::GetRange() const {
	return Range (0.0, 2 * PI);
}

Point CircleCurve::GetPoint (double t) const {
	Point aPoint;
	aPoint.X = myRadius * cos(t) + my—enter.X;
	aPoint.Y = myRadius * sin(t) + my—enter.Y;
	return (aPoint);
}

Point CircleCurve::GetDerivedPoint (double t) const {
	Point aPoint;
	aPoint.X = -myRadius * sin (t);
	aPoint.Y =  myRadius * cos (t);
	return (aPoint);
}

Point CircleCurve::GetCenter() const {
	return my—enter;
}

double CircleCurve::GetRadius() const {
	return myRadius;
}

std::string CircleCurve::GetName() const {
	return "Circle";
}
bool CircleCurve::EqualTo (const ICurve& theOther) const {
	const CircleCurve& aOther = static_cast<const CircleCurve&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetRadius() == this->GetRadius());
}

