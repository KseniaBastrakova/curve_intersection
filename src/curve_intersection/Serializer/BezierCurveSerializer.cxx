#include "curve_intersection/Serializer/BezierCurveSerializer.hxx"

namespace CurveIntersection {

std::string BezierCurveSerializer::GetHeaderName() {
	return Bezier(std::vector<Point>()).GetName();
}

std::unique_ptr<ICurve> BezierCurveSerializer::Read(std::istream& theInput) {

	double aNumControlPoints;
	aNumControlPoints = ReadInt(theInput);
	std::vector<Point> aControlPoints;
	for (size_t i = 0; i < aNumControlPoints; i++) {
		aControlPoints.push_back(ReadPoint(theInput));
	}
	return std::make_unique<Bezier>(aControlPoints);

}

void BezierCurveSerializer::Write(std::ostream& theOutput, const ICurve& theCurve) {
	auto aPoints = static_cast<const Bezier&> (theCurve).GetControlPoints();
	WriteInt(theOutput, (int)aPoints.size());
	for (size_t i = 0; i < aPoints.size(); i++) {
		WritePoint(theOutput, aPoints[i]);
	}

}
}