#pragma once

#include "Point.hxx"
#include "Range.hxx"
#include "Vector.hxx"
#include "ICurve.hxx"
#include <string>

namespace CurveIntersection {
// geometric representation class of a line segment
class LineSegment : public ICurve {
public:
	// Create a segment along the start and end points of a line segment
	// If the points coincide then a line is not created and an exception throws
	LineSegment(const Point& theStart, const Point& theEnd);
	// Return parametrization to the parameterization from [0, 1]
	virtual Range GetRange() const override;
	// Return the point by the parameter
	virtual Point GetPoint(Parameter parameter) const override;
	// Return the derivative of the point on the curve with respect to the parameter
	virtual Vector GetDerivative(Parameter parameter) const override;
	// Return the point on the curve with respect to the parameter theParameter
	// If the parameter does not enter the valid boundaries, an exception is thrown
	virtual Point TryGetPoint(Parameter parameter) const override;
	// return the derivative of the point on the curve with respect to the parameter
	// if the parameter does not enter the valid boundaries, an exception is thrown
	virtual Vector TryGetDerivative(Parameter parameter) const override;
	// Return the name used when writing lineSegment to a file
	virtual std::string GetName() const override;
	// Return start point
	Point GetStart() const;
	// Return end point
	Point GetEnd() const;
private:
	bool EqualTo(const ICurve& theOther) const override;
	Vector myDirection;
	Point myStart;
	Point myEnd;
	Range myRange;
};

}
