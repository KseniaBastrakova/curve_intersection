#pragma once
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

}
