#pragma once
#include <vector>
#include "Base_Structures.hxx"
#include "ICurve.hxx"

class CircleCurve : public ICurve {
public:
	CircleCurve (const Point& the�enter, double theRadius) :
		my�enter (the�enter), myRadius (theRadius) {}

	virtual Range GetRange() const;
	virtual Point GetPoint (double t) const;
	Point GetDerivedPoint (double t) const;
	Point GetCenter() const;
	double GetRadius() const;

	virtual std::string GetName() const;
	virtual bool EqualTo (const ICurve& theOther) const;
private:
	double myRadius;
	Point my�enter;
	Range myRange;
};
