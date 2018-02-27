#include "LineCurve.hxx"

namespace CurveIntersection {

LineSegment::LineSegment(const std::vector<Point>& points) {

	if (points.size() >= 2)
	{
		myStartPoint = points[0];
		myEndPoint = points[1];
	}

}

LineSegment::LineSegment(const Point& thePoint1, const Point& thePoint2) {

	myDirectingVector = Point(thePoint2.x - thePoint1.x, thePoint2.y - thePoint1.y);
	myStartPoint = thePoint1;
	myEndPoint = thePoint2;

}

Point LineSegment::GetPoint(double t) const {
	Point aPointValue;
	aPointValue.x = myDirectingVector.x * t + myStartPoint.x;
	aPointValue.y = myDirectingVector.y * t + myStartPoint.y;
	return aPointValue;
}

Range LineSegment::GetRange() const {
	return Range(0.0, 1.0);
}

Point LineSegment::GetDerivedPoint(double t) const {
	return myDirectingVector;
}

Point LineSegment::GetStartPoint() const {
	return myStartPoint;
}

Point LineSegment::GetEndPoint() const {
	return myEndPoint;
}

std::string LineSegment::GetName() const {
	return "Line";
}

bool LineSegment::EqualTo(const ICurve& theOther) const {
	const LineSegment& aOther = static_cast<const LineSegment&> (theOther);
	return (aOther.GetStartPoint() == this->GetStartPoint() && aOther.GetEndPoint() == this->GetEndPoint());
}

bool LineSegment::IsValid() const
{
	return (!(myStartPoint == myEndPoint));
}
}

