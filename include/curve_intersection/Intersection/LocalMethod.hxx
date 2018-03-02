#pragma once
#include "Base_Structures.hxx"
#include "Point.hxx"

namespace CurveIntersection {

class LocalMethod {
public:
	virtual Point FindMinimum(Box theBox, Point theStartPoint) = 0;
	virtual ~LocalMethod() = default;
};
}
