#pragma once
#include <functional>
#include <vector>
#include "Base_Structures.hxx"
#include "LocalMethod.hxx"

namespace CurveIntersection {

class MethodDivisionIntoThree {
public:
	MethodDivisionIntoThree(std::function<double(double, double)> theFunction, Range theRangeX, Range theRangeY,
		double theLipschitzC, LocalMethod* theLocalMethod) :
		myFunction(theFunction), myRangeX(theRangeX), myRangeY(theRangeY), myLipConstant(theLipschitzC),
		myLocalMethod(theLocalMethod) {
		myEps = 0.00000001;
	};
	std::vector<Point> Method();
private:
	double MinRCrit(std::function<double(double, double)> FunctionX, Box CurrentBox);

	void DividedThree(Box aDivedBox, std::vector<Box>& CurrentBoxex);
	double CountingFunction(std::function<double(double, double)> Function, Point thePoint, Range theRange);
	double MinObjective(std::function<double(double, double)> Function, Box CurrentBoxes, double theCurrent);
	bool BreakCriterion(double CurrentR, double CurrentObjectFunction);
	double LipschitzConstant();
	std::function<double(double, double)> myFunction;
	std::function<Point(double, double)> myGradFuncion;
	LocalMethod* myLocalMethod;
	double myLipConstant;
	double myEps;
	double myNumInerations;
	Range myRangeX;
	Range myRangeY;
};
}
