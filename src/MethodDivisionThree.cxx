#include "MethodDivisionThree.hxx"
#include "Base_Structures.hxx"
#include "ConjugateGradientMethod.hxx"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>  
#include <vector>

namespace {
	bool CheckMinimumFunction (Box & aCurrentBox, std::vector<Point>& theCurrentPoints, 
		Point theCurrent, double& theCurrentFunction, double& theMinimumFunction, double theEps) {
		if (abs(theCurrentFunction - theMinimumFunction) < theEps) {
			theCurrentPoints.push_back (theCurrent);
			aCurrentBox.RCharacteristic = std::numeric_limits<double>::infinity();
			return true;
		}
		else if (abs(theCurrentFunction) < (theMinimumFunction)) { 
			theCurrentPoints.resize(0); 
			theCurrentPoints.push_back (theCurrent);
			theMinimumFunction = theCurrentFunction;
			aCurrentBox.RCharacteristic = std::numeric_limits<double>::infinity();
			return true;
		}
		return false;
	}
}

std::vector<Point> MethodDivisionIntoThree::Method() {
	int NumIteration = 100000;
	int CurrentIteration = 0;
	Box aStartBox (myRangeX, myRangeY);
	std::vector<Point> aResult;

	auto comp = [](const Box& e1, const Box& e2)
	{ return e1.RCharacteristic  > e2.RCharacteristic; };

	std::priority_queue<Box, std::vector<Box>, decltype(comp)> aBoxRQ(comp);
	aStartBox.RCharacteristic = MinRCrit (myFunction, aStartBox);
	aBoxRQ.push(aStartBox);
	double aMinObjFunction = myFunction (aStartBox.Center().X, aStartBox.Center().Y);
	double aMinFunction = std::numeric_limits<double>::infinity();
	double aMaxSizeBox = 1e-4;
	while (CurrentIteration < NumIteration) {
		
		Box aCurrentBox = aBoxRQ.top();
		aBoxRQ.pop();
			
		if (BreakCriterion (aCurrentBox.RCharacteristic, aMinObjFunction)) {
			double aCurrentFunction = myFunction (aCurrentBox.Center().X, aCurrentBox.Center().Y);
			if (CheckMinimumFunction (aCurrentBox, aResult, aCurrentBox.Center(), aCurrentFunction, aMinFunction, myEps))
			  continue;
		}
		if (aCurrentBox.myRangeX.Lenght() * aCurrentBox.myRangeY.Lenght() < aMaxSizeBox) {
			Point aPoint = myLocalMethod->FindMinimum (aCurrentBox, aCurrentBox.Center());
	
			double aCurrentFunction = myFunction (aPoint.X, aPoint.Y);
			if (CheckMinimumFunction (aCurrentBox, aResult, aPoint, aCurrentFunction, aMinFunction, myEps))
				continue;		
		}
		std::vector<Box> CurrentBoxes;
		DividedThree (aCurrentBox, CurrentBoxes);
		for (int i = 0; i < 3; i++) {
			CurrentBoxes[i].RCharacteristic = MinRCrit (myFunction, CurrentBoxes[i]);
			aBoxRQ.push (CurrentBoxes[i]);
			aMinObjFunction = MinObjective (myFunction, CurrentBoxes[i], aMinObjFunction);
		}
		CurrentIteration++;
	}
	return aResult;
}


double MethodDivisionIntoThree::LipschitzConstant() {
	return myLipConstant;

}

double MethodDivisionIntoThree::CountingFunction (std::function<double(double,double)> Function, Point thePoint,
	Range theRange) {
	double F = Function(thePoint.X, thePoint.Y) - LipschitzConstant() * theRange.Lenght() / 2;
	return F;
}

double MethodDivisionIntoThree::MinRCrit (std::function<double(double,double)> Function,
	Box CurrentBox) {
	return Function(CurrentBox.Center().X, CurrentBox.Center().Y) - LipschitzConstant() *
		0.5 * sqrt(CurrentBox.myRangeX.Lenght() * CurrentBox.myRangeX.Lenght() + 
			CurrentBox.myRangeY.Lenght() * CurrentBox.myRangeY.Lenght());

}

void MethodDivisionIntoThree::DividedThree (Box aDivedBox, std::vector<Box>& CurrentBoxex) {
	if (aDivedBox.IsMaxX()) {
		double Path = abs(aDivedBox.myRangeX.End - aDivedBox.myRangeX.Begin) / 3.0;
		CurrentBoxex.push_back(Box (Range(aDivedBox.myRangeX.Begin, aDivedBox.myRangeX.Begin + Path), aDivedBox.myRangeY));
		CurrentBoxex.push_back(Box(Range(aDivedBox.myRangeX.Begin + Path, aDivedBox.myRangeX.Begin + 2 * Path), aDivedBox.myRangeY));
		CurrentBoxex.push_back(Box(Range(aDivedBox.myRangeX.Begin + 2 * Path, aDivedBox.myRangeX.Begin + 3 * Path), aDivedBox.myRangeY));
	}
	else {
		double Path = abs(aDivedBox.myRangeY.End - aDivedBox.myRangeY.Begin) / 3.0;
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin, aDivedBox.myRangeY.Begin + Path)));
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin + Path, aDivedBox.myRangeY.Begin + 2 * Path)));
		CurrentBoxex.push_back(Box(aDivedBox.myRangeX, Range(aDivedBox.myRangeY.Begin + 2 * Path, aDivedBox.myRangeY.Begin + 3 * Path)));

	}

}

double MethodDivisionIntoThree::MinObjective (std::function<double(double, double)> Function,
	Box CurrentBox, double theCurrentFunction) {
	
	
	return std::min (Function (CurrentBox.Center().X,CurrentBox.Center().Y),theCurrentFunction);
}

bool MethodDivisionIntoThree::BreakCriterion (double CurrentR, double CurrentObjectFunction) {
	return (CurrentR > CurrentObjectFunction - myEps);
}
