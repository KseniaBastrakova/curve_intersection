#include "CircleCurve.hxx"
#include "Vector.hxx"
#include <cmath>

namespace CurveIntersection {

namespace {

static bool IsCorrectCircleData(Point point1, Point point2)
{
	return !(point1 == point2);
}

}

CircleCurve::CircleCurve(const std::vector<Point>& points) {
	if (points.size() == 2)
	{
		if (IsCorrectCircleData(points[0], points[1]))
		{
			my�enter = points[0];
			const Vector v = points[1] - my�enter;
			const double r = v.Lenght();
			myRadius = r;
		}
	}
}

Range CircleCurve::GetRange() const {
	return Range(0.0, 2 * PI);
}

Point CircleCurve::GetPoint(double t) const {
	Point aPoint;
	aPoint.x = myRadius * cos(t) + my�enter.x;
	aPoint.y = myRadius * sin(t) + my�enter.y;
	return (aPoint);
}

Point CircleCurve::GetDerivedPoint(double t) const {
	Point aPoint;
	aPoint.x = -myRadius * sin(t);
	aPoint.y = myRadius * cos(t);
	return (aPoint);
}

Point CircleCurve::GetCenter() const {
	return my�enter;
}

double CircleCurve::GetRadius() const {
	return myRadius;
}

std::string CircleCurve::GetName() const {
	return "Circle";
}

bool CircleCurve::EqualTo(const ICurve& theOther) const {
	const CircleCurve& aOther = static_cast<const CircleCurve&> (theOther);
	return (aOther.GetCenter() == this->GetCenter() && aOther.GetRadius() == this->GetRadius());
}

bool CircleCurve::IsValid() const {
	return myRadius > NULL_TOL;
}
}

