#pragma once
#include <vector>
#include "Base_Structures.hxx"
#include "ICurve.hxx"

namespace CurveIntersection {

class CircleCurve : public ICurve {
public:
	CircleCurve(const Point& theÑenter, double theRadius) :
		myÑenter(theÑenter), myRadius(theRadius) {}

	CircleCurve(const std::vector<Point>& points);
	virtual Range GetRange() const;
	virtual Point GetPoint(double t) const;
	Point GetDerivedPoint(double t) const;
	Point GetCenter() const;
	double GetRadius() const;
	bool IsValid() const;
	virtual std::string GetName() const;
	virtual bool EqualTo(const ICurve& theOther) const;
private:
	double myRadius;
	Point myÑenter;
	Range myRange;
};
}
