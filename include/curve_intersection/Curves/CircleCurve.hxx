#pragma once

#include "Point.hxx"
#include "Range.hxx"
#include "Vector.hxx"
#include "ICurve.hxx"
#include <string>

namespace CurveIntersection {

class CircleCurve : public ICurve {
public:
	CircleCurve(const Point& the—enter, double theRadius);
	virtual Range GetRange() const override;
	virtual Point GetPoint(Parameter parameter) const override;
	virtual Vector GetDerivative(Parameter parameter) const override;
	virtual std::string GetName() const override;	
	Point GetCenter() const;
	double GetRadius() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myRadius;
	Point my—enter;
	Range myRange;
};

}
