#pragma once

#include "curve_intersection/Intersection/Box.hxx"
#include "curve_intersection/Intersection/LocalMethod.hxx"
#include "curve_intersection/Core/Vector.hxx"
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
	Point myStart;
};
}
