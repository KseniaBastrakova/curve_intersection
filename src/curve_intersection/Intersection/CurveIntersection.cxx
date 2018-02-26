#include "CurveIntersection.hxx"
#include "ConjugateGradientMethod.hxx"
#include "MethodDivisionThree.hxx"
#include "EvaluationLipschitzConstant.hxx"
#include <functional>

namespace {
	double SquaredDistance(const Point& Point1, const Point& Point2) {
		return (Point2.X - Point1.X) * (Point2.X - Point1.X) + (Point2.Y - Point1.Y) * (Point2.Y - Point1.Y);
	}
}

std::vector<Point> CurveIntersection::Perform(const ICurve& FirstCurve, const ICurve& SecoundCurve) {

	std::function<double(double, double)> aDistFunction = [&](double t1, double t2) {
		return SquaredDistance(FirstCurve.GetPoint(t1), SecoundCurve.GetPoint(t2));
	};
	std::function<Point(double, double)> aDistDerivedFunction = [&](double t1, double t2) {
		Point aPoint1 = FirstCurve.GetPoint(t1);
		Point aGrad1 = FirstCurve.GetDerivedPoint(t1);

		Point aPoint2 = SecoundCurve.GetPoint(t2);
		Point aGrad2 = SecoundCurve.GetDerivedPoint(t2);
		double aResultT1 = 2.0 * (aPoint1.X - aPoint2.X) * aGrad1.X + 2.0 * (aPoint1.Y - aPoint2.Y) * aGrad1.Y;
		double aResultT2 = 2.0 * (aPoint2.X - aPoint1.X) * aGrad2.X + 2.0 * (aPoint2.Y - aPoint1.Y) * aGrad2.Y;
		return Point(aResultT1, aResultT2);
	};
	LipschitzConstantEvaluator aLC(aDistFunction, FirstCurve.GetRange(), SecoundCurve.GetRange());

	ConjugateGradientMethod aMethod(aDistDerivedFunction, aDistFunction);

	MethodDivisionIntoThree Intersection(aDistFunction, FirstCurve.GetRange(), SecoundCurve.GetRange(),
		aLC.Evaluate(50), &(aMethod));

	return Intersection.Method();
}