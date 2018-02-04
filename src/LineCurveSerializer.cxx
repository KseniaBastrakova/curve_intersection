#include "LineCurveSerializer.hxx"
#include "LineCurve.hxx"

std::string LineCurveSerializer::GetHeaderName() {
	return LineCurve (Point(), Point()).GetName();
}

std::unique_ptr<ICurve> LineCurveSerializer::Read (std::istream& theInput) {
	Point aPoint1;
	Point aPoint2;
	aPoint1 = ReadPoint (theInput);
	aPoint2 = ReadPoint (theInput);
	return std::make_unique<LineCurve> (aPoint1, aPoint2);
}

void LineCurveSerializer::Write (std::ostream& theOutput, const ICurve& theCurve) {
	WritePoint (theOutput, dynamic_cast<const LineCurve&> (theCurve).GetStartPoint());
	WritePoint (theOutput, dynamic_cast<const LineCurve&> (theCurve).GetEndPoint());
}