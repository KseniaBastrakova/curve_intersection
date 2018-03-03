#include "Curves/LineSegment.hxx"

namespace CurveIntersection {

LineSegment::LineSegment(const Point& thePoint1, const Point& thePoint2) {
	myStart = thePoint1;
	myEnd = thePoint2;
	myDirection = myEnd - myStart;
	myRange = Range(0., 1.);
}

Point LineSegment::GetPoint(Parameter parameter) const {
	return myStart + myDirection * parameter;
}

Range LineSegment::GetRange() const {
	return myRange;
}

Vector LineSegment::GetDerivative(Parameter parameter) const {
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
