#include "Base_Structures.hxx"
#include "Bezier.hxx"

namespace CurveIntersection {

namespace {

long double Factorial(int X) {
	if (X < 0)
		return 0;
	if (X == 0)
		return 1;
	else
		return X * Factorial(X - 1);
}
}


BezierCurve::BezierCurve(const std::vector<Point>& theControlPoints) {

	myControlPoints = theControlPoints;

}

Range BezierCurve::GetRange() const {
	return Range(0.0, 1.0);
}

Point BezierCurve::GetPoint(Parameter theParameter) const {
	double x = 0;
	double y = 0;

	size_t n = myControlPoints.size() - 1;
	for (size_t i = 0; i <= n; i++)
	{
		double BernsteinCoefficient = CalculateBernsteinPolynom(i, n, theParameter);
		x += BernsteinCoefficient * myControlPoints[i].x;
		y += BernsteinCoefficient * myControlPoints[i].y;
	}
	return (Point(x, y));
}

Vector BezierCurve::GetDerivative(Parameter theParameter) const {
	double x = 0;
	double y = 0;

	size_t n = myControlPoints.size() - 1;
	for (size_t i = 0; i <= n; i++)
	{
		double  BernsteinCoefficient = CalculateBernsteinPolynom(i, n, theParameter) * (i - n * theParameter) / (theParameter * (1 - theParameter));
		x += BernsteinCoefficient * myControlPoints[i].x;
		y += BernsteinCoefficient * myControlPoints[i].y;
	}
	return Point(x, y);
}

double  BezierCurve::CalculateBinomialCoefficient(int i, int n) const {
	return Factorial(n) / (Factorial(i) * Factorial(n - i));
}

double  BezierCurve::CalculateBernsteinPolynom(size_t i, size_t n, double t) const {

	return pow(t, (int)i) * pow(1 - t, (int)(n - i)) * CalculateBinomialCoefficient((int)i, (int)n);
}

std::vector<Point> BezierCurve::GetControlPoints() const {
	return myControlPoints;
}

std::string BezierCurve::GetName() const {
	return "Bezier";
}

bool BezierCurve::EqualTo(const ICurve& theOther) const {
	const BezierCurve& aOther = static_cast<const BezierCurve&> (theOther);
	return aOther.GetControlPoints() == this->GetControlPoints();
}

bool BezierCurve::IsValid() const {
	return !myControlPoints.empty();
}
}


