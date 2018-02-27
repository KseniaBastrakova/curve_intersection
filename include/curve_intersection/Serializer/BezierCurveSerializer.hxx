#pragma once
#include "BezierCurve.hxx"
#include "FormattedCurveSerializer.hxx"

namespace CurveIntersection {

class BezierCurveSerializer :public FormattedCurveSerializer {
public:
	BezierCurveSerializer(Format theFormat) : FormattedCurveSerializer(theFormat) {}
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput);
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve);

	virtual std::string GetHeaderName();

	virtual ~BezierCurveSerializer() = default;
};
}
