#pragma once

#include "curve_intersection/Curves/Ellipse.hxx"
#include "curve_intersection/Serializer/FormattedCurveSerializer.hxx"
#include <ostream>

namespace CurveIntersection {

class EllipseCurveSerializer :public FormattedCurveSerializer {
public:
	EllipseCurveSerializer(Format theFormat) :FormattedCurveSerializer(theFormat) {}
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput);
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve);

	virtual std::string GetHeaderName();

	virtual ~EllipseCurveSerializer() = default;
};
}


