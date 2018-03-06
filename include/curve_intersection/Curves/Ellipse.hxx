#pragma once

#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class Ellipse : public ICurve {
public:
	Ellipse(Point theCenter, double theMajorAxis, double theMinorAxis, double theAngle);
	Ellipse(Point thePoint1, Point thePoint2, Point thePoint3);
	virtual Point GetPoint(Parameter parameter) const override;
	virtual Vector GetDerivative(Parameter parameter) const override;
	virtual Point TryGetPoint(Parameter parameter) const override;
	virtual Vector TryGetDerivative(Parameter parameter) const override;
	virtual Range GetRange() const override;
	virtual std::string GetName() const override;
	Point GetCenter() const;
	double GetMajorAxis() const;
	double GetMinorAxis() const;
	double GetAngle() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myMajorAxis;
	double myMinorAxis;
	Point myCenter;
	double myAngle;
};

}
