#pragma once

#include "curve_intersection/Curves/ICurve.hxx"
#include <istream>
#include <memory>

namespace CurveIntersection {

class ICurveSerializer {
public:
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput) = 0;
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve) = 0;
	virtual ~ICurveSerializer() = default;

};

}


