#pragma once

#include "curve_intersection/Curves/ICurve.hxx"
#include <vector>

namespace CurveIntersection {
class CurveIntersection {
public:
	std::vector<Point> Perform(const ICurve& FirstCurve, const ICurve&SecoundCurve);
};
}
