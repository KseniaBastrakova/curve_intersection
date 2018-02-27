#include "ConjugateGradientMethod.hxx"
#include "GoldenRatio.hxx"
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
	Point aAntiGrad = -myGradientFunction(aCurrentPoint.X, aCurrentPoint.Y);
	Point SCurrent = aAntiGrad;

	for (int i = 0; i < 2; i++) {
		std::function<double(double)> aDistFunction = [&](double alpha) {
			double t1 = aCurrentPoint.X + alpha * SCurrent.X;
			double t2 = aCurrentPoint.Y + alpha * SCurrent.Y;
			return myObjectiveFunction(t1, t2);
		};
		Range aRange = CountingRange(aCurrentPoint, SCurrent);

		double Eps = aRange.Lenght() * 1e-4;
		GoldenRatio aMethod(aDistFunction, aRange, Eps);
		double alamda = aMethod.Run();

		aCurrentPoint.X += alamda * SCurrent.X;
		aCurrentPoint.Y += alamda * SCurrent.Y;
		Point aNewAntiGrad = myGradientFunction(aCurrentPoint.X, aCurrentPoint.Y);
		double W = NormSq(aNewAntiGrad) / NormSq(aAntiGrad);
		SCurrent.X = SCurrent.X * W + aAntiGrad.X;
		SCurrent.Y = SCurrent.Y * W + aAntiGrad.Y;
		aAntiGrad = aNewAntiGrad;
	}
	return aCurrentPoint;

}
Range ConjugateGradientMethod::CountingRange(Point thePoint, Point theDirection) {

	double aMaxSize = std::numeric_limits<double>::infinity();

	if (theDirection.X > 0)
		aMaxSize = std::min(aMaxSize, (myRangeX.End - thePoint.X) / (theDirection.X));
	if (theDirection.X < 0)
		aMaxSize = std::min(aMaxSize, (myRangeX.Begin - thePoint.X) / (theDirection.X));

	if (theDirection.Y > 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.End - thePoint.Y) / (theDirection.Y));
	if (theDirection.Y < 0)
		aMaxSize = std::min(aMaxSize, (myRangeY.Begin - thePoint.Y) / (theDirection.Y));
	return Range(0.0, aMaxSize);
}
}