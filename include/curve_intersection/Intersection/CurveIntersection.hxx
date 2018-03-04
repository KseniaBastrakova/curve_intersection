#pragma once

#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {
class CurveIntersection {
public:
	std::vector<Point> Perform(const ICurve& FirstCurve, const ICurve&SecoundCurve);
};
}
