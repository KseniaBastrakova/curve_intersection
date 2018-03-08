#pragma once

#include "curve_intersection/Core/Point.hxx"
#include "curve_intersection/Core/Range.hxx"

namespace CurveIntersection {
	
struct Box {
	Range myRangeX;
	Range myRangeY;
	Box(Range theRangeX, Range theRangeY) :
		myRangeX(theRangeX), myRangeY(theRangeY) {}
	Point Center() const {
		return Point(myRangeX.Begin + (myRangeX.Lenght()) / 2.0, myRangeY.Begin + myRangeY.Lenght() / 2.0);
	}
	bool IsMaxX() {
		return ((myRangeX.Lenght()) > (myRangeY.Lenght()));
	}
	double RCharacteristic;
};

}
