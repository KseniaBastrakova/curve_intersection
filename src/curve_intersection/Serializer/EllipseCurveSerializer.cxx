#include "EllipseCurveSerializer.hxx"

namespace CurveIntersection {

std::string EllipseCurveSerializer::GetHeaderName() {
	return EllipseCurve(Point(), 0.0, 0.0, 0.0).GetName();
}

std::unique_ptr<ICurve> EllipseCurveSerializer::Read(std::istream& theInput) {
	Point aCenter = ReadPoint(theInput);
	double aRadius1 = ReadDouble(theInput);
	double aRadius2 = ReadDouble(theInput);
	double aAlpha = ReadDouble(theInput);
	return std::make_unique<EllipseCurve>(aCenter, aRadius1, aRadius2, aAlpha);

}

void EllipseCurveSerializer::Write(std::ostream& theOutput, const ICurve& theCurve) {
	WritePoint(theOutput, dynamic_cast<const EllipseCurve&> (theCurve).GetCenter());
	WriteDouble(theOutput, dynamic_cast<const EllipseCurve&> (theCurve).GetR1());
	WriteDouble(theOutput, dynamic_cast<const EllipseCurve&> (theCurve).GetR2());
	WriteDouble(theOutput, dynamic_cast<const EllipseCurve&> (theCurve).GetAlpha());
}
}