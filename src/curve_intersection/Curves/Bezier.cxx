#include "Bezier.hxx"

namespace CurveIntersection {

namespace {

size_t Factorial(int x) {
	if (x == 0)
		return 1;
	else
		return x * Factorial(x - 1);
}

double CalculateBinomialCoefficient(int i, int n) {
	return Factorial(n) / (Factorial(i) * Factorial(n - i));
}

double CalculateBernsteinPolynom(size_t i, size_t n, double t) {
	return pow(t, (int)i) * pow(1 - t, (int)(n - i)) * CalculateBinomialCoefficient((int)i, (int)n);
}

}

Bezier::Bezier(const std::vector<Point>& theControlPoints) {
	if (theControlPoints.empty())
		throw std::invalid_argument("the number of points must be greater than zero");
	myControlPoints = theControlPoints;
}

Range Bezier::GetRange() const {
	return Range(0.0, 1.0);
}

Point Bezier::GetPoint(Parameter theParameter) const {
	double x = 0;
	double y = 0;

	size_t n = myControlPoints.size() - 1;
	for (size_t i = 0; i <= n; i++)
	{
		double BernsteinCoefficient = CalculateBernsteinPolynom(i, n, theParameter);
		x += BernsteinCoefficient * myControlPoints[i].x;
		y += BernsteinCoefficient * myControlPoints[i].y;
	}
	return Point(x, y);
}

Vector Bezier::GetDerivative(Parameter theParameter) const {
	double x = 0;
	double y = 0;

	size_t n = myControlPoints.size() - 1;
	for (size_t i = 0; i <= n; i++)
	{
		double BernsteinCoefficient = CalculateBernsteinPolynom(i, n, theParameter) * (i - n * theParameter) / (theParameter * (1 - theParameter));
		x += BernsteinCoefficient * myControlPoints[i].x;
		y += BernsteinCoefficient * myControlPoints[i].y;
	}
	return Vector(x, y);
}

Point Bezier::TryGetPoint(Parameter theParameter) const {
	if (theParameter < 0. || theParameter > 1.)
		throw std::invalid_argument("parameter must be from [0.,1]");
	return GetPoint(theParameter);
}

Vector Bezier::TryGetDerivative(Parameter theParameter) const
{
	if (theParameter < 0. || theParameter > 1.)
		throw std::invalid_argument("parameter must be from [0.,1]");
	return GetDerivative(theParameter);
}

std::vector<Point> Bezier::GetControlPoints() const {
	return myControlPoints;
}

std::string Bezier::GetName() const {
	return "Bezier";
}

bool Bezier::EqualTo(const ICurve& theOther) const {
	const Bezier& aOther = static_cast<const Bezier&> (theOther);
	return aOther.GetControlPoints() == this->GetControlPoints();
}

}
