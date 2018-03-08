#include "curve_intersection/Intersection/CurveIntersection.hxx"
#include "curve_intersection/Intersection/ConjugateGradientMethod.hxx"
#include "curve_intersection/Intersection/MethodDivisionThree.hxx"
#include "curve_intersection/Intersection/EvaluationLipschitzConstant.hxx"
#include <functional>
#include <iostream>
namespace CurveIntersection {

namespace {

double SquaredDistance(const Point& Point1, const Point& Point2) {
	return (Point2.x - Point1.x) * (Point2.x - Point1.x) + (Point2.y - Point1.y) * (Point2.y - Point1.y);
}

std::vector<Point> RemoveEqualPoints(std::vector<Point> thePoints, const ICurve& FirstCurve, const ICurve& SecondCurve) {
	std::vector<Point> aResult;
	for (size_t i = 0; i < thePoints.size(); i++) {
		bool aIsExist = false;
		for (size_t j = 0; j < aResult.size(); j++) {
			if (IsEqual(FirstCurve.GetPoint(thePoints[i].x), FirstCurve.GetPoint(aResult[j].x), 1e-3)
					&& IsEqual(SecondCurve.GetPoint(thePoints[i].y), SecondCurve.GetPoint(aResult[j].y),1e-3)) {
				aIsExist = true;
		    }
		}
		if (!aIsExist)
			aResult.push_back(thePoints[i]);

	}
	return aResult;
}

}

std::vector<Point> Intersection::Perform(const ICurve& FirstCurve, const ICurve& SecoundCurve) {

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
	std::vector<Point> aResult = Intersection.Method();
	aResult = RemoveEqualPoints(aResult, FirstCurve, SecoundCurve);
	return aResult;
}

}
