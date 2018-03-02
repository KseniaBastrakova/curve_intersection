#pragma once
#include "Base_Structures.hxx"
#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class Bezier : public ICurve {
public:
	Bezier(const std::vector<Point>& theControlPoints);
	virtual Point GetPoint(Parameter parameter) const override;
	Vector GetDerivative(Parameter parameter) const override;
	virtual Range GetRange() const override;
	virtual std::string GetName() const;
	std::vector<Point> GetControlPoints() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	std::vector<Point> myControlPoints;
};

}

