#pragma once

#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {
// Class of geometric representation of an ellipse.
class Ellipse : public ICurve {
public:
	// Create an ellipse along the two radius
	// and the center point and two ulums of the slope of the axes with respect to x.
	Ellipse(Point theCenter, double theMajorAxis, double theMinorAxis, double theAngle);
	// Create an ellipse along the center, the main axis and the point on the boundary
	Ellipse(Point thePoint1, Point thePoint2, Point thePoint3);
	// Return the parameter bounds for the Ellipse : [0, 2 * pi].
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
	// Return the name used when writing ellipse to a file
	virtual std::string GetName() const override;
	// Return center
	Point GetCenter() const;
	// Return major radius
	double GetMajorAxis() const;
	// Return minor radius
	double GetMinorAxis() const;
	// Return angle between x axis and major axis
	double GetAngle() const;
private:
	virtual bool EqualTo(const ICurve& theOther) const override;
	double myMajorAxis;
	double myMinorAxis;
	Point myCenter;
	double myAngle;
};

}
