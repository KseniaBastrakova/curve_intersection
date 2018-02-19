#pragma once
#include "Base_Structures.hxx"
#include "ICurve.hxx"


class LineCurve : public ICurve {
public:
	LineCurve() = delete;
	LineCurve (const Point& thePoint1, const Point& thePoint2);
	virtual Range GetRange() const;
	virtual Point GetPoint (double t) const;
	Point GetDerivedPoint (double t) const;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	virtual std::string GetName() const;
	bool EqualTo (const ICurve& theOther) const;
	bool IsValid() const;
	virtual ~LineCurve() = default;
private:
	Point myDirectingVector;
	Point myStartPoint;
	Point myEndPoint;
	Range myRange;
};