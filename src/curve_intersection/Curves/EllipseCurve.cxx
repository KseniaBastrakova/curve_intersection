#include "EllipseCurve.hxx"
#include "Vector.hxx"

namespace CurveIntersection {

namespace {

static bool PointsOneLine(Point point1, Point point2, Point point3)
{
	return IsCollinear(Vector(point1 - point2), Vector(point2 - point3));
}

static bool CorrectEllipseData(Point point1, Point point2, Point point3)
{
	return  !((point1 == point2 ||
		point2 == point3 ||
		point1 == point3) ||
		(PointsOneLine(point1, point2, point3)));

}
}

EllipseCurve::EllipseCurve(Point thecenter, double ther1, double ther2, double thealpha) :
	myCenter(Point(0.0, 0.0)),
	myR1(0.0),
	myR2(0.0),
	myAlpha(0.0)
{
	if (ther1 > NULL_TOL && ther2 > NULL_TOL)
	{
		myR1 = ther1;
		myR2 = ther2;
		myCenter = thecenter;
		myAlpha = thealpha;
	}
}

EllipseCurve::EllipseCurve(const std::vector<Point>& points) :
	myCenter(Point(0.0, 0.0)),
	myR1(0.0),
	myR2(0.0),
	myAlpha(0.0)
{
	if (points.size() >= 3)
	{
		if (CorrectEllipseData(points[0], points[1], points[2]))
		{
			myCenter = points[0];
			Point pointV(points[1]);
			double x = pointV.x - myCenter.x;
			double y = pointV.y - myCenter.y;
			double axisA = sqrt(x * x + y * y);
			myAlpha = atan2(y, x);
			myR1 = axisA;
			//vector
			Vector newCoord(std::fabs((points[2] - myCenter).x), std::fabs((points[2] - myCenter).y));
			newCoord = Rotate(newCoord, myAlpha);

			double axisB = (sqrt(fabs((newCoord.y) * (newCoord.y) /
				(1 - (newCoord.x) * (newCoord.x) / (myR1 * myR1)))));
			myR2 = axisB;
		}
	}

}

Range EllipseCurve::GetRange() const {
	return Range(0.0, 2.0 * PI);
}

Point EllipseCurve::GetPoint(double t) const {
	Point point(myR1 * cos(t), myR2 * sin(t));
	double x = point.x * cos(myAlpha) + point.y * cos(myAlpha + PI / 2.);
	double y = point.x * sin(myAlpha) + point.y * sin(myAlpha + PI / 2.);
	return myCenter + Point(x, y);
}

Point EllipseCurve::GetDerivedPoint(double t) const {
	Vector vector(myR1 * -sin(t), myR2 * cos(t));
	double x = vector.x * cos(myAlpha) + vector.y * cos(myAlpha + PI / 2.);
	double y = vector.x * sin(myAlpha) + vector.y * sin(myAlpha + PI / 2.);
	return Point(x, y);
}

double EllipseCurve::GetR1() const {
	return myR1;
}

double EllipseCurve::GetAlpha() const {
	return myAlpha;
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

bool EllipseCurve::IsValid() const
{
	return (myR1 > NULL_TOL && myR2 > NULL_TOL);
}
}