#pragma once
#include "ICurve.hxx"
#include "Range.hxx"
#include <vector>

namespace CurveIntersection {

class Bezier : public ICurve {
public:
	Bezier(const std::vector<Point>& theControlPoints);
	virtual Range GetRange() const override;
	virtual Point GetPoint(Parameter parameter) const override;
	virtual Vector GetDerivative(Parameter parameter) const override;
	virtual std::string GetName() const override;
	std::vector<Point> GetControlPoints() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	std::vector<Point> myControlPoints;
};

}
