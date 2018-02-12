#include "EllipseCurve.hxx"

Range EllipseCurve::GetRange() const {
	return Range(0.0, 2 * PI);
}

Point EllipseCurve::GetPoint (double t) const {
	Point aPoint;
	aPoint.X = myR1 * cos(t);
	aPoint.Y = myR2 * sin(t);
	return aPoint;
}

Point EllipseCurve::GetDerivedPoint (double t) const {
	Point aPoint;
	aPoint.X = myR1 * -sin (t);
	aPoint.Y = myR2 * cos (t);
	return aPoint;
}

double EllipseCurve::GetR1() const{
	return myR1;
}

double EllipseCurve::GetR2() const {
	return myR2;
}

Point EllipseCurve::GetCenter() const {
	return myCenter;
}

std::string EllipseCurve::GetName() const {
	return "Ellipse";
}

bool EllipseCurve::EqualTo(const ICurve& theOther) const {
	const EllipseCurve& aOther = static_cast<const EllipseCurve&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetR1() == this->GetR1() &&
		aOther.GetR2() == this->GetR2());
}