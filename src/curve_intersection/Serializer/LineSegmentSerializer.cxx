#include "LineSegmentSerializer.hxx"
#include "LineSegment.hxx"

namespace CurveIntersection {

std::string LineSegmentSerializer::GetHeaderName() {
	return LineSegment(Point(), Point()).GetName();
}

std::unique_ptr<ICurve> LineSegmentSerializer::Read(std::istream& theInput) {
	Point aPoint1;
	Point aPoint2;
	aPoint1 = ReadPoint(theInput);
	aPoint2 = ReadPoint(theInput);
	return std::make_unique<LineSegment>(aPoint1, aPoint2);
}

void LineSegmentSerializer::Write(std::ostream& theOutput, const ICurve& theCurve) {
	WritePoint(theOutput, dynamic_cast<const LineSegment&> (theCurve).GetStart());
	WritePoint(theOutput, dynamic_cast<const LineSegment&> (theCurve).GetEnd());
}
}