#pragma once

#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class Ellipse : public ICurve {
public:
	Ellipse(Point theCenter, double R1, double R2, double theAlpha);
	Ellipse(Point thePoint1, Point thePoint2, Point thePoint3);
	virtual Point GetPoint(Parameter parameter) const override;
	virtual Vector GetDerivative(Parameter parameter) const;
	virtual Range GetRange() const override;
	virtual std::string GetName() const override;
	Point GetCenter() const;
	double GetR1() const;
	double GetR2() const;
	double GetAngle() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myR1;
	double myR2;
	Point myCenter;
	double myAngle;
};

}
