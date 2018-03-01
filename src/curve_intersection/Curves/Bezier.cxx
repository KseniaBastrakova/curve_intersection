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


Bezier::Bezier(const std::vector<Point>& theControlPoints) {

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
	return (Point(x, y));
}

Vector Bezier::GetDerivative(Parameter theParameter) const {
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

double  Bezier::CalculateBinomialCoefficient(int i, int n) const {
	return Factorial(n) / (Factorial(i) * Factorial(n - i));
}

double  Bezier::CalculateBernsteinPolynom(size_t i, size_t n, double t) const {

	return pow(t, (int)i) * pow(1 - t, (int)(n - i)) * CalculateBinomialCoefficient((int)i, (int)n);
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

bool Bezier::IsValid() const {
	return !myControlPoints.empty();
}
}


