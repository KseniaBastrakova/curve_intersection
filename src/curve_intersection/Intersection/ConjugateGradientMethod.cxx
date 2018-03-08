#include "curve_intersection/Intersection/ConjugateGradientMethod.hxx"
#include "curve_intersection/Intersection/GoldenRatio.hxx"
#include "curve_intersection/Core/Vector.hxx"
#include "curve_intersection/Core/Range.hxx"
#include <algorithm>
#include <limits>

namespace CurveIntersection {

Point ConjugateGradientMethod::FindMinimum(Box theBox, Point theStartPoint) {
	myRangeX = theBox.myRangeX;
	myRangeY = theBox.myRangeY;
	myStart = theStartPoint;
	int aNumIteration = 10;
	double aObjResFuntion = myObjectiveFunction(theStartPoint.x, theStartPoint.y);
	for (int i = 0; i < aNumIteration; i++) {
		Point aNewPoint = Run();
		double aNewObjResFuntion = myObjectiveFunction(aNewPoint.x, aNewPoint.y);
		if (aNewObjResFuntion > aObjResFuntion)
			return myStart;
		else {
			myStart = aNewPoint;
			aObjResFuntion = aNewObjResFuntion;
		}
	}
	return myStart;
}

Point ConjugateGradientMethod::Run() {
	Point aCurrentPoint(myStart.x, myStart.y);
	Vector aAntiGrad = -myGradientFunction(aCurrentPoint.x, aCurrentPoint.y);
	Vector SCurrent = aAntiGrad;

	for (int i = 0; i < 2; i++) {
		std::function<double(double)> aDistFunction = [&](double alpha) {
			double t1 = aCurrentPoint.x + alpha * SCurrent.x;
			double t2 = aCurrentPoint.y + alpha * SCurrent.y;
			return myObjectiveFunction(t1, t2);
		};
		Range aRange = CountingRange(aCurrentPoint, SCurrent);

		double Eps = aRange.Lenght() * 1e-4;
		GoldenRatio aMethod(aDistFunction, aRange, Eps);
		double alamda = aMethod.Run();

		aCurrentPoint.x += alamda * SCurrent.x;
		aCurrentPoint.y += alamda * SCurrent.y;
		Vector aNewAntiGrad = myGradientFunction(aCurrentPoint.x, aCurrentPoint.y);
		double W = aNewAntiGrad.Lenght() / aAntiGrad.Lenght();
		SCurrent.x = SCurrent.x * W + aAntiGrad.x;
		SCurrent.y = SCurrent.y * W + aAntiGrad.y;
		aAntiGrad = aNewAntiGrad;
	}
	return aCurrentPoint;

}
Range ConjugateGradientMethod::CountingRange(Point thePoint, Vector theDirection) {

	double aMaxSize = std::numeric_limits<double>::infinity();

	if (theDirection.x > 0)
		aMaxSize = std::min(aMaxSize, (myRangeX.End - thePoint.x) / (theDirection.x));
	if (theDirection.x < 0)
		aMaxSize = std::min(aMaxSize, (myRangeX.Begin - thePoint.x) / (theDirection.x));

	if (theDirection.y > 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.End - thePoint.y) / (theDirection.y));
	if (theDirection.y < 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.Begin - thePoint.y) / (theDirection.y));
	return Range(0.0, aMaxSize);
}
}