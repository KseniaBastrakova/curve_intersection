#include "curve_intersection/Intersection/GoldenRatio.hxx"

namespace CurveIntersection {

double GoldenRatio::Run() {
	double aGRConstant = 1.6180339887;
	double aBegin = myRange.Begin;
	double aEnd = myRange.End;
	double X1 = aEnd - (aEnd - aBegin) / aGRConstant;
	double X2 = aBegin + (aEnd - aBegin) / aGRConstant;
	double Y1 = myFunction(X1);
	double Y2 = myFunction(X2);
	while ((aEnd - aBegin) > myEps) {
		X1 = aEnd - (aEnd - aBegin) / aGRConstant;
		X2 = aBegin + (aEnd - aBegin) / aGRConstant;
		Y1 = myFunction(X1);
		Y2 = myFunction(X2);
		if (Y1 > Y2) {
			aBegin = X1;
		}
		else {
			aEnd = X2;
		}

	}
	return (aEnd + aBegin) / 2.;
}
}
