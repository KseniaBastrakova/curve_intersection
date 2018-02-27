#pragma once
#include "Base_Structures.hxx"
#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {
class CurveIntersection {
public:
	std::vector<Point> Perform(const ICurve& FirstCurve, const ICurve&SecoundCurve);
};
}
