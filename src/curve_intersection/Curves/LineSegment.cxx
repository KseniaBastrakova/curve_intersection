#include "curve_intersection/Curves/LineSegment.hxx"
#include <stdexcept>
#include <stdexcept>

namespace CurveIntersection {

LineSegment::LineSegment(const Point& theStart, const Point& theEnd) {
	if (IsEqual(theStart, theEnd, 1e-7))
		throw std::invalid_argument("Points must be different!");
	myStart = theStart;
	myEnd = theEnd;
	myDirection = myEnd - myStart;
	myRange = Range(0., 1.);
}

Point LineSegment::GetPoint(Parameter theParameter) const {
	return myStart + myDirection * theParameter;
}

Vector LineSegment::GetDerivative(Parameter theParameter) const {
	return myDirection;
}

Range LineSegment::GetRange() const {
	return myRange;
}

Point LineSegment::TryGetPoint(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 1.)
		throw std::invalid_argument("parameter must be from [0.,1]");
	return GetPoint(theParameter);
}

Vector LineSegment::TryGetDerivative(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 1.)
		throw std::invalid_argument("parameter must be from [0.,1]");
	return myDirection;
}

Point LineSegment::GetStart() const {
	return myStart;
}

Point LineSegment::GetEnd() const {
	return myEnd;
}

std::string LineSegment::GetName() const {
	return "LineSegment";
}

bool LineSegment::EqualTo(const ICurve& theOther) const {
	const LineSegment& aOther = static_cast<const LineSegment&> (theOther);
	return (aOther.GetStart() == this->GetStart() && aOther.GetEnd() == this->GetEnd());
}

}
