#pragma once
#include "Base_Structures.hxx"
#include "LocalMethod.hxx"
#include <functional>
class ConjugateGradientMethod: public LocalMethod {
public:
	ConjugateGradientMethod (std::function<Point(double, double)> theGradientFunction,
		std::function<double(double, double)> theObjectiveFunction): 
		myGradientFunction (theGradientFunction), myObjectiveFunction (theObjectiveFunction){}

	virtual Point FindMinimum (Box theBox, Point theStartPoint);

private:
	Point Run();
	Range CountingRange(Point thePoint, Point theDirection);
	std::function<Point (double, double)> myGradientFunction;
	std::function<double (double, double)> myObjectiveFunction;
	Range myRangeX;
	Range myRangeY;
	Point myStartPoint;

};
