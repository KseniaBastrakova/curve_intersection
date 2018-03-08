#pragma once
#include "curve_intersection/Curves/CircleCurve.hxx"
#include "curve_intersection/Serializer/FormattedCurveSerializer.hxx"
#include <ostream>

namespace CurveIntersection {

class CircleCurveSerializer :public FormattedCurveSerializer {

public:
	CircleCurveSerializer(Format theFormat) :FormattedCurveSerializer(theFormat) {}
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput);
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve);

	virtual std::string GetHeaderName();

	virtual ~CircleCurveSerializer() = default;
};
}

