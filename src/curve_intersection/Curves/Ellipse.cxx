#include "EllipseCurve.hxx"
#include "Vector.hxx"

namespace CurveIntersection {

	namespace {

		static bool PointsOneLine(Point thePoint1, Point thePoint2, Point thePoint3)
		{
			return IsCollinear(Vector(thePoint1 - thePoint2), Vector(thePoint2 - thePoint3));
		}

		static bool CorrectEllipseData(Point thePoint1, Point thePoint2, Point thePoint3)
		{
			return  !((thePoint1 == thePoint2 ||
				thePoint2 == thePoint3 ||
				thePoint1 == thePoint3) ||
				(PointsOneLine(thePoint1, thePoint2, thePoint3)));
		}

	}

	Ellipse::Ellipse(Point theCenter, double theR1, double theR2, double theAngle) :
		myCenter(Point(0.0, 0.0)),
		myR1(0.0),
		myR2(0.0),
		myAlpha(0.0)
	{
		if (theR1 > NULL_TOL && theR2 > NULL_TOL)
		{
			myR1 = theR1;
			myR2 = theR2;
			myCenter = theCenter;
			myAlpha = theAngle;
		}
	}

	Ellipse::Ellipse(Point thePoint1, Point thePoint2, Point thePoint3) :
		myCenter(Point(0.0, 0.0)),
		myR1(0.0),
		myR2(0.0),
		myAlpha(0.0)
	{

		if (CorrectEllipseData(thePoint1, thePoint2, thePoint3))
		{
			myCenter = thePoint1;
			Vector aSideDirection = thePoint2 - myCenter;
			double axisA = sqrt(aSideDirection.Lenght());
			myAlpha = atan2(aSideDirection.y, aSideDirection.x);
			myR1 = axisA;
			//vector
			Vector newCoord(std::fabs((thePoint3 - myCenter).x), std::fabs((thePoint3 - myCenter).y));
			newCoord = Rotate(newCoord, myAlpha);

			double axisB = (sqrt(fabs((newCoord.y) * (newCoord.y) /
				(1 - (newCoord.x) * (newCoord.x) / (myR1 * myR1)))));
			myR2 = axisB;
		}

	}

	Range Ellipse::GetRange() const {
		return Range(0.0, 2.0 * PI);
	}

	Point Ellipse::GetPoint(Parameter parameter) const {
		Point point(myR1 * cos(parameter), myR2 * sin(parameter));
		double x = point.x * cos(myAlpha) + point.y * cos(myAlpha + PI / 2.);
		double y = point.x * sin(myAlpha) + point.y * sin(myAlpha + PI / 2.);
		return myCenter + Vector(x, y);
	}

	Vector Ellipse::GetDerivative(Parameter parameter) const {
		Vector vector(myR1 * -sin(parameter), myR2 * cos(parameter));
		double x = vector.x * cos(myAlpha) + vector.y * cos(myAlpha + PI / 2.);
		double y = vector.x * sin(myAlpha) + vector.y * sin(myAlpha + PI / 2.);
		return Point(x, y);
	}

	double Ellipse::GetR1() const {
		return myR1;
	}

	double Ellipse::GetAngle() const {
		return myAlpha;
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