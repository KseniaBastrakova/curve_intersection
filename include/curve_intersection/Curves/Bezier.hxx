#pragma once

#include "curve_intersection/Core/Range.hxx"
#include "curve_intersection/Curves/ICurve.hxx"
#include <vector>

namespace CurveIntersection {
// geometric representation class of a bezier curve
class Bezier : public ICurve {
public:
	// Create an bezier from control points
	Bezier(const std::vector<Point>& theControlPoints);
	//Return the parameter bounds for the Bezier : [0, 1].
	virtual Range GetRange() const override;
	// Return the point by the parameter
	virtual Point GetPoint(Parameter parameter) const override;
	// Return the derivative of the point on the curve with respect to the parameter
	virtual Vector GetDerivative(Parameter parameter) const override;
	// Return the point on the curve with respect to the parameter theParameter
	// If the parameter does not enter the valid boundaries, an exception is thrown
	virtual Point TryGetPoint(Parameter parameter) const override;
	// Return the point on the curve with respect to the parameter theParameter
	// If the parameter does not enter the valid boundaries, an exception is thrown
	virtual Vector TryGetDerivative(Parameter parameter) const override;
	// Return the name used when writing bezier to a file
	virtual std::string GetName() const override;
	// Return control points
	std::vector<Point> GetControlPoints() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	std::vector<Point> myControlPoints;
};

}
