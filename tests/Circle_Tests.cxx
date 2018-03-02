#include "gtest/gtest.h"
#include "Curves/CircleCurve.hxx"
#include "Vector.hxx"

using namespace CurveIntersection;

TEST(Circle, ConstructorFromTwoCenterAndRadius)
{
	Point aCenter(0, 0);
	double aRadius = 777.;
	const CircleCurve aCircle(aCenter, aRadius);
	EXPECT_EQ(aCenter, aCircle.GetCenter());
	EXPECT_EQ(5., aCircle.GetRadius());
}

TEST(Circle, ConstructorFromTwoPoints)
{
	Point aCenter(0, 0);
	Point aPointOnCircle(5., 5.);
	const CircleCurve aCircle(aCenter, aPointOnCircle);
	EXPECT_EQ(aCenter, aCircle.GetCenter());
	EXPECT_EQ(5., aCircle.GetRadius());
}

TEST(Circle, CopyConstructor)
{
	Point aCenter(0, 0);
	Point aPointOnCircle(5., 5.);
	const CircleCurve aCircle(aCenter, aPointOnCircle);
	CircleCurve aCopy = aCircle;
	EXPECT_EQ(aCenter, aCircle.GetCenter());
	EXPECT_EQ(5., aCircle.GetRadius());
}

TEST(Circle, Assigment)
{
	Point aCenter(0, 0);
	Point aPointOnCircle(5., 5.);
	const CircleCurve aCircle(aCenter, aPointOnCircle);
	CircleCurve aCopy(Point(0., 0.), 7.);
	aCopy = aCircle;
	EXPECT_EQ(aCenter, aCircle.GetCenter());
	EXPECT_EQ(5., aCircle.GetRadius());
}


TEST(Circle, GetPoint)
{
	const CircleCurve circle(Point(1., 1.), 2.);
	EXPECT_TRUE(IsEqualPoints(circle.GetPoint(0.), Point(3., 1.)));
	EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI*2.), Point(3., 1.)));
	EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI / 4.), Point(1. + sqrt(2.), 1. + sqrt(2.))));
	EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI), Point(-1., 1.)));
	EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI*5. / 4.), Point(1. - sqrt(2.), 1. - sqrt(2.))));
}

TEST(Circle, GetRange)
{
	const CircleCurve circle(Point(1., 1.), 2.);
	const auto range = circle.GetRange();
	EXPECT_NEAR(range.Begin, 0., NULL_TOL);
	EXPECT_NEAR(range.End, PI*2., NULL_TOL);
}

TEST(Circle, GetDerivative)
{
	const CircleCurve circle(Point(1., 1.), 2.);
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(0.), Vector(0., 2.)));
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(PI*2.), Vector(0., 2.)));
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(PI / 4.), Vector(-sqrt(2.), sqrt(2.))));
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(PI*9. / 4.), Vector(-sqrt(2.), sqrt(2.))));
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(PI), Vector(0., -2.)));
	EXPECT_TRUE(IsEqualVectors(circle.GetDerivative(PI*5. / 4.), Vector(sqrt(2.), -sqrt(2.))));
}
