#include "gtest/gtest.h"
#include "Curves/Bezier.hxx"
#include <memory>
#include <vector>

using namespace CurveIntersection;
class BezierCurveTest : public ::testing::Test {
};


static bool IsEqualPoints(Point p1, Point p2, double eps = NULL_TOL)
{
	return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
}


std::shared_ptr<BezierCurve> ClosedBezierCurve() {
	std::vector<Point> poles{ Point(-14., -5.), Point(-7.2, 7.), Point(-2.4, 7.), Point(3., 2.1),
	Point(9., -4.8), Point(-14., -5.) };
	return std::make_shared<BezierCurve>(poles);

}

std::shared_ptr<BezierCurve> NonClosedBezierCurve() {
	std::vector<Point> poles{ Point(0., 0.), Point(1., 2.), Point(3., 3.), Point(4., 0.) };
	return std::make_shared<BezierCurve>(poles);
}
TEST(BezierCurve, GetRange)
{
	auto bezier = ClosedBezierCurve();
	const auto range = bezier->GetRange();
	EXPECT_NEAR(range.Begin, 0., NULL_TOL);
	EXPECT_NEAR(range.End, 1., NULL_TOL);
}

TEST(BezierCurve, GetPoint)
{
	auto bezier = NonClosedBezierCurve();
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.0), Point(0., 0.)));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.2), Point(0.704, 1.056), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.4), Point(1.552, 1.728), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.6), Point(2.448, 1.872), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.8), Point(3.296, 1.344), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(1.), Point(4., 0.), 1.e-4));
}

