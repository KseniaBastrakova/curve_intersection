#include "ConjugateGradientMethod.hxx"
#include "GoldenRatio.hxx"
#include "Vector.hxx"
#include <algorithm>
#include <limits>

namespace CurveIntersection {

Point ConjugateGradientMethod::FindMinimum(Box theBox, Point theStartPoint) {
	myRangeX = theBox.myRangeX;
	myRangeY = theBox.myRangeY;
	myStartPoint = theStartPoint;
	int aNumIteration = 10;
	double aObjResFuntion = myObjectiveFunction(theStartPoint.X, theStartPoint.Y);
	for (int i = 0; i < aNumIteration; i++) {
		Point aNewPoint = Run();
		double aNewObjResFuntion = myObjectiveFunction(aNewPoint.X, aNewPoint.Y);
		if (aNewObjResFuntion > aObjResFuntion)
			return myStartPoint;
		else {
			myStartPoint = aNewPoint;
			aObjResFuntion = aNewObjResFuntion;
		}
	}
	return myStartPoint;
}

Point ConjugateGradientMethod::Run() {
	Point aCurrentPoint(myStartPoint.X, myStartPoint.Y);
	Vector aAntiGrad = -myGradientFunction(aCurrentPoint.X, aCurrentPoint.Y);
	Vector SCurrent = aAntiGrad;

	for (int i = 0; i < 2; i++) {
		std::function<double(double)> aDistFunction = [&](double alpha) {
			double t1 = aCurrentPoint.X + alpha * SCurrent.x;
			double t2 = aCurrentPoint.Y + alpha * SCurrent.y;
			return myObjectiveFunction(t1, t2);
		};
		Range aRange = CountingRange(aCurrentPoint, SCurrent);

		double Eps = aRange.Lenght() * 1e-4;
		GoldenRatio aMethod(aDistFunction, aRange, Eps);
		double alamda = aMethod.Run();

		aCurrentPoint.X += alamda * SCurrent.x;
		aCurrentPoint.Y += alamda * SCurrent.y;
		Vector aNewAntiGrad = myGradientFunction(aCurrentPoint.X, aCurrentPoint.Y);
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
		aMaxSize = std::min(aMaxSize, (myRangeX.End - thePoint.X) / (theDirection.x));
	if (theDirection.x < 0)
		aMaxSize = std::min(aMaxSize, (myRangeX.Begin - thePoint.X) / (theDirection.x));

	if (theDirection.y > 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.End - thePoint.Y) / (theDirection.y));
	if (theDirection.y < 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.Begin - thePoint.Y) / (theDirection.y));
	return Range(0.0, aMaxSize);
}
}