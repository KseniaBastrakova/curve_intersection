#pragma once
#include "Base_Structures.hxx"
#include "ICurve.hxx"
#include <vector>

namespace CurveIntersection {

class LineSegment : public ICurve {
public:
	LineSegment() = delete;
	LineSegment(const std::vector<Point>& points);
	LineSegment(const Point& thePoint1, const Point& thePoint2);
	virtual Range GetRange() const;
	virtual Point GetPoint(double t) const;
	Vector GetDerivative(double t) const;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	virtual std::string GetName() const;
	bool EqualTo(const ICurve& theOther) const;
	bool IsValid() const;
	virtual ~LineSegment() = default;
private:
	Point myDirectingVector;
	Point myStartPoint;
	Point myEndPoint;
	Range myRange;
};
}