#include "curve_intersection/Curves/Ellipse.hxx"

namespace CurveIntersection {

namespace {

static bool IsPointsOneLine(Point thePoint1, Point thePoint2, Point thePoint3)
{
	return IsCollinear(thePoint1 - thePoint2, thePoint2 - thePoint3);
}

static bool IsCorrectEllipseData(Point thePoint1, Point thePoint2, Point thePoint3)
{
	return  !((thePoint1 == thePoint2 ||
		thePoint2 == thePoint3 ||
		thePoint1 == thePoint3) ||
		(IsPointsOneLine(thePoint1, thePoint2, thePoint3)));
}

}

Ellipse::Ellipse(Point theCenter, double theMajorAxis, double theMinorAxis, double theAngle)
{
	if (theMajorAxis < 0. || theMinorAxis < 0.)
		throw std::invalid_argument("Axis should not be negative!");
	myMajorAxis = theMajorAxis;
	myMinorAxis = theMinorAxis;
	myCenter = theCenter;
	myAngle = theAngle;
}

Ellipse::Ellipse(Point theCenter, Point thePoint2, Point thePoint3)
{
	if (!IsCorrectEllipseData(theCenter, thePoint2, thePoint3))
		throw std::invalid_argument("Incorrect Ellipse data!");
	myCenter = theCenter;
	Vector aSideDirection = thePoint2 - myCenter;
	myMajorAxis = aSideDirection.Lenght();
	myAngle = atan2(aSideDirection.y, aSideDirection.x);
	Vector newCoord(fabs(thePoint3.x - myCenter.x), fabs(thePoint3.y - myCenter.y));
	newCoord = Rotate(newCoord, myAngle);

	double axisB = (sqrt(fabs((newCoord.y) * (newCoord.y) /
		(1 - (newCoord.x) * (newCoord.x) / (myMajorAxis * myMajorAxis)))));
	myMinorAxis = axisB;
}

Range Ellipse::GetRange() const {
	return Range(0.0, 2.0 * PI);
}

Point Ellipse::GetPoint(Parameter parameter) const {
	Vector aCanonical(myMajorAxis * cos(parameter), myMinorAxis * sin(parameter));
	return myCenter + Rotate(aCanonical, myAngle);
}

Vector Ellipse::GetDerivative(Parameter parameter) const {
	Vector aCanonical(myMajorAxis * -sin(parameter), myMinorAxis * cos(parameter));
	return Rotate(aCanonical, myAngle);
}

Vector Ellipse::TryGetDerivative(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 2 * PI)
		throw std::invalid_argument("parameter must be from [0.,2*PI]");
	return GetDerivative(theParameter);
}

Point Ellipse::TryGetPoint(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 2 * PI)
		throw std::invalid_argument("parameter must be from [0.,2*PI]");
	return GetPoint(theParameter);
}

double Ellipse::GetMajorAxis() const {
	return myMajorAxis;
}

double Ellipse::GetAngle() const {
	return myAngle;
}

double Ellipse::GetMinorAxis() const {
	return myMinorAxis;
}

Point Ellipse::GetCenter() const {
	return myCenter;
}

std::string Ellipse::GetName() const {
	return "Ellipse";
}

bool Ellipse::EqualTo(const ICurve& theOther) const {
	const Ellipse& aOther = static_cast<const Ellipse&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetMajorAxis() == this->GetMajorAxis() &&
		aOther.GetMinorAxis() == this->GetMinorAxis());
}

}
