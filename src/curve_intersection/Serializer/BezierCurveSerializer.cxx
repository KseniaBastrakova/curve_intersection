#include "BezierCurveSerializer.hxx"

std::string BezierCurveSerializer::GetHeaderName() {
	return BezierCurve(std::vector<Point>()).GetName();
}

std::unique_ptr<ICurve> BezierCurveSerializer::Read(std::istream& theInput) {

	double aNumControlPoints;
	aNumControlPoints = ReadInt(theInput);
	std::vector<Point> aControlPoints;
	for (size_t i = 0; i < aNumControlPoints; i++) {
		aControlPoints.push_back(ReadPoint(theInput));
	}
	return std::make_unique<BezierCurve>(aControlPoints);

}

void BezierCurveSerializer::Write(std::ostream& theOutput, const ICurve& theCurve) {
	auto aPoints = static_cast<const BezierCurve&> (theCurve).GetControlPoints();
	WriteInt(theOutput, (int)aPoints.size());
	for (size_t i = 0; i < aPoints.size(); i++) {
		WritePoint(theOutput, aPoints[i]);
	}

}