#pragma once

#include "Point.hxx"
#include "Range.hxx"
#include "Vector.hxx"
#include "Base_Structures.hxx"
#include <string>

namespace CurveIntersection {

class ICurve {
public:
	typedef double Parameter;
	virtual Range GetRange() const = 0;
	virtual Point GetPoint(Parameter theParameter) const = 0;
	virtual Vector GetDerivative(Parameter theParameter) const = 0;
	virtual std::string GetName() const = 0;
	friend bool operator== (const ICurve& a, const ICurve& b);
	virtual ~ICurve() = default;
protected:
	// this is supposed to be called for the same types, e.g. from operator ==
	virtual bool EqualTo(const ICurve& theOther) const = 0;
};

}
