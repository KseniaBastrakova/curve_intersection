#pragma once

#include "Base_Structures.hxx"
#include "Curves/ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class LineSegment : public ICurve {
public:
	LineSegment(const Point& thePoint1, const Point& thePoint2);
	virtual Range GetRange() const override;
	virtual Point GetPoint(Parameter parameter) const override;
	virtual std::string GetName() const override;
	virtual Vector GetDerivative(Parameter parameter) const;
	Point GetStart() const;
	Point GetEnd() const;
private:
	bool EqualTo(const ICurve& theOther) const override;
	Point myDirection;
	Point myStart;
	Point myEnd;
	Range myRange;
};
}