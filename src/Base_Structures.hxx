#pragma once

struct Range {
	Range(){}
	Range (double theBegin, double theEnd):
		Begin (theBegin), End (theEnd) {}
	double Begin;
	double End;
	double Lenght() const {
		return (End - Begin);
	}
};

struct Point {
	Point(){}
	Point (double theX, double theY) :
		X (theX), Y (theY) {}
	  Point (const Point& thePoint) {
		  X = thePoint.X;
		  Y = thePoint.Y; 
	  }
	double X;
	double Y;
};

inline double Distance (Point theFirst, Point theSecond) {
	return (theFirst.X - theSecond.X) + (theFirst.Y - theSecond.Y);
}

inline bool operator == (Point theFirst, Point theSecond) {
	return (theFirst.X == theSecond.X && theFirst.Y == theSecond.Y);
}

inline Point operator - (Point thePoint) {
	return Point (-thePoint.X, -thePoint.Y);
}

inline Point operator * (Point thePoint, double aParam) {
	return Point(thePoint.X * aParam, thePoint.Y * aParam);
}

inline Point operator - (Point thePointLeft, Point thePointRight) {
	return Point (thePointLeft.X - thePointRight.X, thePointLeft.Y - thePointRight.Y);
}

inline double NormSq (Point thePoint) {
	return (thePoint.X *thePoint.X + thePoint.Y * thePoint.Y);
}

struct Box {
	Range myRangeX;
	Range myRangeY;
	Box (Range theRangeX, Range theRangeY) :
		myRangeX (theRangeX), myRangeY (theRangeY) {}
	Point Center() {
		return Point (myRangeX.Begin + (myRangeX.Lenght()) / 2.0, myRangeY.Begin + myRangeY.Lenght() / 2.0);
	}
	bool IsMaxX() {
		return ((myRangeX.Lenght()) > (myRangeY.Lenght()));
	}
	double RCharacteristic;
};

const double PI = 3.1421;