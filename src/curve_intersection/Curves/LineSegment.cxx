#include "LineSegment.hxx"
#include <stdexcept>

namespace CurveIntersection {

LineSegment::LineSegment(const Point& thePoint1, const Point& thePoint2) {
	myStart = thePoint1;
	myEnd = thePoint2;
	myDirection = myEnd - myStart;
	myRange = Range(0., 1.);
}

Point LineSegment::GetPoint(Parameter theParameter) const {
	return myStart + myDirection * theParameter;
}


Point LineSegment::TryGetPoint(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 1.)
		throw std::invalid_argument("parameter must be from [0.,1]");
	return GetPoint(theParameter);
}

Vector LineSegment::GetDerivative(Parameter theParameter) const {
	return myDirection;
}

Range LineSegment::GetRange() const {
	return myRange;
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
