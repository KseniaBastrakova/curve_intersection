#pragma once

#include "curve_intersection/Core/Point.hxx"

namespace CurveIntersection {

class LocalMethod {
public:
	virtual Point FindMinimum(Box theBox, Point theStartPoint) = 0;
	virtual ~LocalMethod() = default;
};
}
