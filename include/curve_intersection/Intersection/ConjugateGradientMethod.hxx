#pragma once
#include "Base_Structures.hxx"
#include "LocalMethod.hxx"
#include "Vector.hxx"
#include <functional>

namespace CurveIntersection {

class ConjugateGradientMethod : public LocalMethod {
public:
	ConjugateGradientMethod(std::function<Vector(double, double)> theGradientFunction,
		std::function<double(double, double)> theObjectiveFunction) :
		myGradientFunction(theGradientFunction), myObjectiveFunction(theObjectiveFunction) {}

	virtual Point FindMinimum(Box theBox, Point theStartPoint);

private:
	Point Run();
	Range CountingRange(Point thePoint, Vector theDirection);
	std::function<Vector(double, double)> myGradientFunction;
	std::function<double(double, double)> myObjectiveFunction;
	Range myRangeX;
	Range myRangeY;
	Point myStartPoint;
};
}
