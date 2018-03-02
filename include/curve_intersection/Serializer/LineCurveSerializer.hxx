#pragma once
#include "FormattedCurveSerializer.hxx"
#include "LineSegment.hxx"

namespace CurveIntersection {

class LineSegmentSerializer :public FormattedCurveSerializer {
public:
	LineSegmentSerializer(Format theFormat) : FormattedCurveSerializer(theFormat) {}
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput);
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve);
	virtual std::string GetHeaderName();
	virtual ~LineSegmentSerializer() = default;
};
}
