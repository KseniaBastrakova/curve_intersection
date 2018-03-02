#pragma once
#include <vector>
#include "Base_Structures.hxx"
#include "ICurve.hxx"

namespace CurveIntersection {

class CircleCurve : public ICurve {
public:
	CircleCurve(const Point& the�enter, double theRadius) :
		my�enter(the�enter), myRadius(theRadius) {}

	CircleCurve(Point thePoint1, Point thePoint2);
	virtual Point GetPoint(double t) const override;
	virtual Vector GetDerivative(double t) const override;
	virtual Range GetRange() const override;
	virtual std::string GetName() const override;	
	Point GetCenter() const;
	double GetRadius() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myRadius;
	Point my�enter;
	Range myRange;
};
}
