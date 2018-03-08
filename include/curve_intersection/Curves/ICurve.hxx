#pragma once

#include "curve_intersection/Core/Point.hxx"
#include "curve_intersection/Core/Range.hxx"
#include "curve_intersection/Core/Vector.hxx"
#include <string>

namespace CurveIntersection {
// Abstract class for a basic geometric object.
// Representation functions for storing, obtaining a point and derivative with respect to a parameter,
//obtaining a parametric space, comparing geometric objects
class ICurve {
public:
	typedef double Parameter;
	// return permissible parameter limits
	virtual Range GetRange() const = 0;
	// return the point on the curve with respect to the parameter theParameter
	virtual Point GetPoint(Parameter theParameter) const = 0;
	// return the derivative of the point on the curve with respect to the parameter
	virtual Vector GetDerivative(Parameter theParameter) const = 0;
	// return the point on the curve with respect to the parameter theParameter
	// if the parameter does not enter the valid boundaries, an exception is thrown
	virtual Point TryGetPoint(Parameter theParameter) const = 0;
	// return the derivative of the point on the curve with respect to the parameter
	// if the parameter does not enter the valid boundaries, an exception is thrown
	virtual Vector TryGetDerivative(Parameter theParameter) const = 0;
	// return the name used when writing a primitive to a file
	virtual std::string GetName() const = 0;
	friend bool operator== (const ICurve& theFirst, const ICurve& theSecond);
	virtual ~ICurve() = default;
protected:
	// this is supposed to be called for the same types, e.g. from operator ==
	virtual bool EqualTo(const ICurve& theOther) const = 0;
};

}
