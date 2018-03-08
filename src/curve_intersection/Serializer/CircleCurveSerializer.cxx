#include "curve_intersection/Serializer/CircleCurveSerializer.hxx"

namespace CurveIntersection {

std::string CircleCurveSerializer::GetHeaderName() {
	return CircleCurve(Point(), 0.0).GetName();
}

std::unique_ptr<ICurve> CircleCurveSerializer::Read(std::istream& theInput) {
	Point aCenter = ReadPoint(theInput);
	double aRadius = ReadDouble(theInput);
	return std::make_unique<CircleCurve>(aCenter, aRadius);
}

void CircleCurveSerializer::Write(std::ostream& theOutput, const ICurve& theCurve) {
	WritePoint(theOutput, dynamic_cast<const CircleCurve&>(theCurve).GetCenter());
	WriteDouble(theOutput, dynamic_cast<const CircleCurve&>(theCurve).GetRadius());
}
}

