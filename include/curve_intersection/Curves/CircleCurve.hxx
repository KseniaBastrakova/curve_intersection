#pragma once

#include "curve_intersection/Core/Point.hxx"
#include "curve_intersection/Core/Range.hxx"
#include "curve_intersection/Core/Vector.hxx"
#include "curve_intersection/Curves/ICurve.hxx"
#include <string>

namespace CurveIntersection {
// geometric representation class of a circle
class CircleCurve : public ICurve {
public:
	// Create a circle in the center and radius
	CircleCurve(const Point& the—enter, double theRadius);
	// Return the parameter bounds for the circle : [0, 2 * pi].
	virtual Range GetRange() const override;
	// Return the point by the parameter
	virtual Point GetPoint(Parameter parameter) const override;
	// Return the derivative of the point on the curve with respect to the parameter
	virtual Vector GetDerivative(Parameter parameter) const override;
	// Return the point on the curve with respect to the parameter theParameter
	// If the parameter does not enter the valid boundaries, an exception is thrown
	virtual Point TryGetPoint(Parameter parameter) const override;
	// Return the derivative of the point on the curve with respect to the parameter
	// If the parameter does not enter the valid boundaries, an exception is thrown
	virtual Vector TryGetDerivative(Parameter parameter) const override;
	// Return the name used when writing circle to a file
	virtual std::string GetName() const override;	
	// Return center
	Point GetCenter() const;
	// Return radius
	double GetRadius() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myRadius;
	Point my—enter;
	Range myRange;
};

}
