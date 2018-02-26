#pragma once
#include "Base_Structures.hxx"
#include <string>

class ICurve {
public:
	virtual Range GetRange() const = 0;
	virtual Point GetPoint(double t) const = 0;
	virtual Point GetDerivedPoint(double t) const = 0;
	virtual std::string GetName() const = 0;
	friend bool operator== (const ICurve& a, const ICurve& b) {
		if (a.GetName() != b.GetName())
			return false;
		else
			return a.EqualTo(b);
	}
	virtual ~ICurve() = default;
protected:
	// this is supposed to be called for the same types, e.g. from operator ==
	virtual bool EqualTo(const ICurve& theOther) const = 0;
};
