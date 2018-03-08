#include "curve_intersection/Curves/ICurve.hxx"

namespace CurveIntersection {

bool operator== (const ICurve& a, const ICurve& b) {
	if (a.GetName() != b.GetName())
		return false;
	else
		return a.EqualTo(b);
}

}
