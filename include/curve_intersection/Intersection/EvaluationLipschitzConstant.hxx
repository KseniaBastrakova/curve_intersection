#pragma once
#include "Base_Structures.hxx"
#include <functional>

namespace CurveIntersection {

class LipschitzConstantEvaluator {
public:
	LipschitzConstantEvaluator(std::function<double(double, double)> theFunction, Range theRangeX, Range theRangeY) :
		myFunction(theFunction), myRangeX(theRangeX), myRangeY(theRangeY) {}

	double Evaluate(int theResolution) const;

private:
	double myLipschitzConstant;
	std::function<double(double, double)> myFunction;
	Range myRangeX;
	Range myRangeY;
};
}
