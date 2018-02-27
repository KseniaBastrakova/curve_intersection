#include "CurveIntersection.hxx"
#include "ConjugateGradientMethod.hxx"
#include "MethodDivisionThree.hxx"
#include "EvaluationLipschitzConstant.hxx"
#include <functional>

namespace CurveIntersection {
	namespace {
		double SquaredDistance(const Point& Point1, const Point& Point2) {
			return (Point2.x - Point1.x) * (Point2.x - Point1.x) + (Point2.y - Point1.y) * (Point2.y - Point1.y);
		}
	}

	std::vector<Point> CurveIntersection::Perform(const ICurve& FirstCurve, const ICurve& SecoundCurve) {

		std::function<double(double, double)> aDistFunction = [&](double t1, double t2) {
			return SquaredDistance(FirstCurve.GetPoint(t1), SecoundCurve.GetPoint(t2));
		};
		std::function<Vector(double, double)> aDistDerivedFunction = [&](double t1, double t2) {
			Point aPoint1 = FirstCurve.GetPoint(t1);
			Vector aGrad1 = FirstCurve.GetDerivative(t1);

			Point aPoint2 = SecoundCurve.GetPoint(t2);
			Vector aGrad2 = SecoundCurve.GetDerivative(t2);
			double aResultT1 = 2.0 * (aPoint1.x - aPoint2.x) * aGrad1.x + 2.0 * (aPoint1.y - aPoint2.y) * aGrad1.y;
			double aResultT2 = 2.0 * (aPoint2.x - aPoint1.x) * aGrad2.x + 2.0 * (aPoint2.y - aPoint1.y) * aGrad2.y;
			return Vector(aResultT1, aResultT2);
		};
		LipschitzConstantEvaluator aLC(aDistFunction, FirstCurve.GetRange(), SecoundCurve.GetRange());

		ConjugateGradientMethod aMethod(aDistDerivedFunction, aDistFunction);

		MethodDivisionIntoThree Intersection(aDistFunction, FirstCurve.GetRange(), SecoundCurve.GetRange(),
			aLC.Evaluate(50), &(aMethod));

		return Intersection.Method();
	}
}