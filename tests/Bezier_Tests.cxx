#include "gtest/gtest.h"
#include "Curves/Bezier.hxx"
#include <memory>
#include <vector>

using namespace CurveIntersection;

namespace {
std::shared_ptr<Bezier> ClosedBezierCurve() {
	std::vector<Point> poles{ Point(-14., -5.), Point(-7.2, 7.), Point(-2.4, 7.), Point(3., 2.1),
		Point(9., -4.8), Point(-14., -5.) };
	return std::make_shared<Bezier>(poles);
}

std::shared_ptr<Bezier> NonClosedBezierCurve() {
	std::vector<Point> poles{ Point(0., 0.), Point(1., 2.), Point(3., 3.), Point(4., 0.) };
	return std::make_shared<Bezier>(poles);
}

}

TEST(Bezier, Constructor)
{
	std::vector<Point> aPoles{ Point(11., 0.), Point(1., 5.), Point(7., 3.), Point(3., 8.) };
	Bezier aBezier(aPoles);
	EXPECT_EQ(aPoles, aBezier.GetControlPoints());
}

TEST(Bezier, CopyConstructor)
{
	std::vector<Point> aPoles{ Point(11., 0.), Point(1., 5.), Point(7., 3.), Point(3., 8.) };
	Bezier aBezier(aPoles);
	Bezier aCopy = aBezier;
	EXPECT_EQ(aPoles, aCopy.GetControlPoints());
}

TEST(Bezier, Assigment)
{
	std::vector<Point> aPoles{ Point(11., 0.), Point(1., 5.), Point(7., 3.), Point(3., 8.) };
	Bezier aBezier(aPoles);
	std::vector<Point> aPolesCopy{ Point(1., 0.) };
	Bezier aCopy(aPolesCopy);
	aCopy = aBezier;
	EXPECT_EQ(aPoles, aCopy.GetControlPoints());
}

TEST(Bezier, GetRange)
{
	auto bezier = ClosedBezierCurve();
	const auto range = bezier->GetRange();
	EXPECT_NEAR(range.Begin, 0., NULL_TOL);
	EXPECT_NEAR(range.End, 1., NULL_TOL);
}

TEST(Bezier, GetPoint)
{
	auto bezier = NonClosedBezierCurve();
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.0), Point(0., 0.)));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.2), Point(0.704, 1.056), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.4), Point(1.552, 1.728), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.6), Point(2.448, 1.872), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(0.8), Point(3.296, 1.344), 1.e-4));
	EXPECT_TRUE(IsEqualPoints(bezier->GetPoint(1.), Point(4., 0.), 1.e-4));
}

TEST(Bezier, GetDerivative)
{
	auto bezier = NonClosedBezierCurve();
//	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(0.0), Vector(0., 0.)));
	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(0.2), Vector(3.96, 4.44), 1.e-4));
	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(0.4), Vector(4.44, 2.16), 1.e-4));
	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(0.6), Vector(4.44, -0.84), 1.e-4));
	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(0.8), Vector(3.96, -4.56), 1.e-4));
//	EXPECT_TRUE(IsEqualVectors(bezier->GetDerivative(1.), Vector(4., 0.), 1.e-4));
}

