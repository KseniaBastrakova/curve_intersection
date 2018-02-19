#include "LineCurve.hxx"

LineCurve::LineCurve (const Point& thePoint1, const Point& thePoint2) {

	myDirectingVector = Point(thePoint2.X - thePoint1.X, thePoint2.Y - thePoint1.Y);
	myStartPoint = thePoint1;
	myEndPoint = thePoint2;

}

Point LineCurve::GetPoint (double t) const {
	Point aPointValue;
	aPointValue.X = myDirectingVector.X * t + myStartPoint.X;
	aPointValue.Y = myDirectingVector.Y * t + myStartPoint.Y;
	return aPointValue;
}

Range LineCurve::GetRange() const {
	return Range (0.0, 1.0);
}

Point LineCurve::GetDerivedPoint (double t) const {
	return myDirectingVector;
}

Point LineCurve::GetStartPoint() const {
	return myStartPoint;
}

Point LineCurve::GetEndPoint() const {
	return myEndPoint;
}

std::string LineCurve::GetName() const {
	return "Line";
}

bool LineCurve::EqualTo(const ICurve& theOther) const {
	const LineCurve& aOther = static_cast<const LineCurve&> (theOther);
	return (aOther.GetStartPoint() == this->GetStartPoint() && aOther.GetEndPoint() == this->GetEndPoint());
}

bool LineCurve::IsValid() const
{
	return (!(myStartPoint == myEndPoint));
}

