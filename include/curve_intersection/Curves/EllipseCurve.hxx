#pragma once
#include "Base_Structures.hxx"
#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class EllipseCurve : public ICurve {
public:
	EllipseCurve(Point theCenter, double R1, double R2, double theAlpha);
	EllipseCurve(const std::vector<Point>& points);
	virtual Range GetRange() const;
	virtual Point GetPoint(double t) const;

	Point GetCenter() const;
	double GetR1() const;
	double GetR2() const;
	Point GetDerivedPoint(double t) const;
	double GetAlpha() const;
	bool IsValid() const;

	virtual std::string GetName() const;
	bool EqualTo(const ICurve& theOther) const;

private:

	double myR1;
	double myR2;
	Point myCenter;
	double myAlpha;
};
}
