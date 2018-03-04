#pragma once

#include "Point.hxx"
#include "Range.hxx"
#include "Vector.hxx"
#include "ICurve.hxx"
#include <string>

namespace CurveIntersection {

class LineSegment : public ICurve {
public:
	LineSegment(const Point& thePoint1, const Point& thePoint2);
	virtual Range GetRange() const override;
	virtual Point GetPoint(Parameter parameter) const override;
	virtual Vector GetDerivative(Parameter parameter) const override;
	virtual std::string GetName() const override;
	Point GetStart() const;
	Point GetEnd() const;
private:
	bool EqualTo(const ICurve& theOther) const override;
	Vector myDirection;
	Point myStart;
	Point myEnd;
	Range myRange;
};

}
