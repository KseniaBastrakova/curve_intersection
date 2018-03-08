#include "curve_intersection/Intersection/MethodDivisionThree.hxx"

#include "curve_intersection/Intersection/ConjugateGradientMethod.hxx"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>  
#include <vector>

namespace CurveIntersection {

namespace {

bool CheckMinimumFunction(Box & aCurrentBox, std::vector<Point>& theCurrentPoints,
	Point theCurrent, double& theCurrentFunction, double& theMinimumFunction, double theEps) {
	if (fabs(theCurrentFunction - theMinimumFunction) < theEps) {
		theCurrentPoints.push_back(theCurrent);
		aCurrentBox.RCharacteristic = std::numeric_limits<double>::infinity();
		return true;
	}
	else if (fabs(theCurrentFunction) < (theMinimumFunction)) {
		theCurrentPoints.resize(0);
		theCurrentPoints.push_back(theCurrent);
		theMinimumFunction = theCurrentFunction;
		aCurrentBox.RCharacteristic = std::numeric_limits<double>::infinity();
		return true;
	}
	return false;
}

std::vector<Point> RemoveEqualPoints(std::vector<Point> thePoints) {
	std::vector<Point> aResult;
	for (size_t i = 0; i < thePoints.size(); i++) {
		bool aIsExist = false;
		for (size_t j = 0; j < aResult.size(); j++) {
			if (IsEqual(thePoints[i], aResult[j], 1e-3))
				aIsExist = true;
		}
		if (!aIsExist)
			aResult.push_back(thePoints[i]);

	}
	return aResult;
}
}

std::vector<Point> MethodDivisionIntoThree::Method() {
	int NumIteration = 10000;
	int CurrentIteration = 0;
	Box aStartBox(myRangeX, myRangeY);
	std::vector<Point> aResult;

	auto comp = [](const Box& e1, const Box& e2)
	{ return e1.RCharacteristic > e2.RCharacteristic; };

	std::priority_queue<Box, std::vector<Box>, decltype(comp)> aBoxRQ(comp);
	aStartBox.RCharacteristic = MinRCrit(myFunction, aStartBox);
	aBoxRQ.push(aStartBox);
	double aMinObjFunction = myFunction(aStartBox.Center().x, aStartBox.Center().y);
	double aMinFunction = std::numeric_limits<double>::infinity();
	double aMaxSizeBox = 1e-4;
	while (CurrentIteration < NumIteration && !aBoxRQ.empty()) {
		Box aCurrentBox = aBoxRQ.top();
		aBoxRQ.pop();
		if (BreakCriterion(aCurrentBox.RCharacteristic, aMinObjFunction)) {
			double aCurrentFunction = myFunction(aCurrentBox.Center().x, aCurrentBox.Center().y);
			if (CheckMinimumFunction(aCurrentBox, aResult, aCurrentBox.Center(), aCurrentFunction, aMinFunction, myEps))
				continue;

		}
		if (aCurrentBox.myRangeX.Lenght() * aCurrentBox.myRangeY.Lenght() < aMaxSizeBox) {
			Point aPoint = myLocalMethod->FindMinimum(aCurrentBox, aCurrentBox.Center());

			double aCurrentFunction = myFunction(aPoint.x, aPoint.y);
			if (CheckMinimumFunction(aCurrentBox, aResult, aPoint, aCurrentFunction, aMinFunction, myEps))
				continue;
		}
		std::vector<Box> CurrentBoxes;
		DividedThree(aCurrentBox, CurrentBoxes);
		for (int i = 0; i < 3; i++) {
			CurrentBoxes[i].RCharacteristic = MinRCrit(myFunction, CurrentBoxes[i]);
			aBoxRQ.push(CurrentBoxes[i]);
			aMinObjFunction = MinObjective(myFunction, CurrentBoxes[i], aMinObjFunction);
		}
		CurrentIteration++;
	}
	if (aResult.empty()) {
		Point aCenter = aBoxRQ.top().Center();
		double aBestInterval = myFunction(aCenter.x, aCenter.y);
		aResult.push_back(aCenter);
		aBoxRQ.pop();
		while (!aBoxRQ.empty()) {
			Point aCurrentCenter = aBoxRQ.top().Center();
			double aInterval = myFunction(aCurrentCenter.x, aCurrentCenter.y);
			if (aBestInterval > aInterval - myEps)
				aResult.push_back(aCurrentCenter);
			else
				break;
			aBoxRQ.pop();
		}
	}

	aResult = RemoveEqualPoints(aResult);

	return aResult;
}

double MethodDivisionIntoThree::LipschitzConstant() {
	return myLipConstant;

}

double MethodDivisionIntoThree::CountingFunction(std::function<double(double, double)> Function, Point thePoint,
	Range theRange) {
	double F = Function(thePoint.x, thePoint.y) - LipschitzConstant() * theRange.Lenght() / 2;
	return F;
}

double MethodDivisionIntoThree::MinRCrit(std::function<double(double, double)> Function,
	Box CurrentBox) {
	return Function(CurrentBox.Center().x, CurrentBox.Center().y) - LipschitzConstant() *
		0.5 * sqrt(CurrentBox.myRangeX.Lenght() * CurrentBox.myRangeX.Lenght() +
			CurrentBox.myRangeY.Lenght() * CurrentBox.myRangeY.Lenght());

}

void MethodDivisionIntoThree::DividedThree(Box aDivedBox, std::vector<Box>& CurrentBoxex) {
	if (aDivedBox.IsMaxX()) {
		double Path = fabs(aDivedBox.myRangeX.End - aDivedBox.myRangeX.Begin) / 3.0;
		CurrentBoxex.push_back(Box(Range(aDivedBox.myRangeX.Begin, aDivedBox.myRangeX.Begin + Path), aDivedBox.myRangeY));
		CurrentBoxex.push_back(Box(Range(aDivedBox.myRangeX.Begin + Path, aDivedBox.myRangeX.Begin + 2 * Path), aDivedBox.myRangeY));
		CurrentBoxex.push_back(Box(Range(aDivedBox.myRangeX.Begin + 2 * Path, aDivedBox.myRangeX.Begin + 3 * Path), aDivedBox.myRangeY));
	}
	else {
		double Path = fabs(aDivedBox.myRangeY.End - aDivedBox.myRangeY.Begin) / 3.0;
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin, aDivedBox.myRangeY.Begin + Path)));
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin + Path, aDivedBox.myRangeY.Begin + 2. * Path)));
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin + 2 * Path, aDivedBox.myRangeY.Begin + 3 * Path)));

	}

}

double MethodDivisionIntoThree::MinObjective(std::function<double(double, double)> Function,
	Box CurrentBox, double theCurrentFunction) {


	return std::min(Function(CurrentBox.Center().x, CurrentBox.Center().y), theCurrentFunction);
}

bool MethodDivisionIntoThree::BreakCriterion(double CurrentR, double CurrentObjectFunction) {
	return (CurrentR > CurrentObjectFunction - myEps);
}
}
