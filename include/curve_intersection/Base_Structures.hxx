#pragma once
#include <cmath>
#include "Point.hxx"

namespace CurveIntersection {

struct Range {
	Range() {}
	Range(double theBegin, double theEnd) :
		Begin(theBegin), End(theEnd) {}
	double Begin;
	double End;
	double Lenght() const {
		return (End - Begin);
	}
};


inline bool operator == (Range theFirst, Range theSecond) {
	return (theFirst.Begin == theSecond.Begin && theFirst.End == theSecond.End);
}

struct Box {
	Range myRangeX;
	Range myRangeY;
	Box(Range theRangeX, Range theRangeY) :
		myRangeX(theRangeX), myRangeY(theRangeY) {}
	Point Center() {
		return Point(myRangeX.Begin + (myRangeX.Lenght()) / 2.0, myRangeY.Begin + myRangeY.Lenght() / 2.0);
	}
	bool IsMaxX() {
		return ((myRangeX.Lenght()) > (myRangeY.Lenght()));
	}
	double RCharacteristic;
};

const double PI = 3.14159265358979323846;
const double NULL_TOL = 1e-4;
}
