#include "Ellipse.hxx"
#include "Vector.hxx"

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

Ellipse::Ellipse(Point theCenter, double theR1, double theR2, double theAngle)
{
	if (theR1 > 0. && theR2 > 0.)
	{
		myR1 = theR1;
		myR2 = theR2;
		myCenter = theCenter;
		myAngle = theAngle;
	}
}

Ellipse::Ellipse(Point theCenter, Point thePoint2, Point thePoint3)
{
	if (IsCorrectEllipseData(theCenter, thePoint2, thePoint3))
	{
		myCenter = theCenter;
		Vector aSideDirection = thePoint2 - myCenter;
		myR1 = aSideDirection.Lenght();
		myAngle = atan2(aSideDirection.y, aSideDirection.x);
		Vector newCoord(fabs(thePoint3.x - myCenter.x), fabs(thePoint3.y - myCenter.y));
		newCoord = Rotate(newCoord, myAngle);

		double axisB = (sqrt(fabs((newCoord.y) * (newCoord.y) /
			(1 - (newCoord.x) * (newCoord.x) / (myR1 * myR1)))));
		myR2 = axisB;
	}

}

Range Ellipse::GetRange() const {
	return Range(0.0, 2.0 * PI);
}

Point Ellipse::GetPoint(Parameter parameter) const {
	Vector aCanonical(myR1 * cos(parameter), myR2 * sin(parameter));
	return myCenter + Rotate(aCanonical, myAngle);
}

Vector Ellipse::GetDerivative(Parameter parameter) const {
	Vector aCanonical(myR1 * -sin(parameter), myR2 * cos(parameter));
	return Rotate(aCanonical, myAngle);
}

double Ellipse::GetR1() const {
	return myR1;
}

double Ellipse::GetAngle() const {
	return myAngle;
}

double Ellipse::GetR2() const {
	return myR2;
}

Point Ellipse::GetCenter() const {
	return myCenter;
}

std::string Ellipse::GetName() const {
	return "Ellipse";
}

bool Ellipse::EqualTo(const ICurve& theOther) const {
	const Ellipse& aOther = static_cast<const Ellipse&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetR1() == this->GetR1() &&
		aOther.GetR2() == this->GetR2());
}

}
