#include "stdafx.h"
#include "gtest/gtest.h"
#include "Curves/LineCurve.hxx"

TEST(Line, ConstructSamePoints)
{
	Point samePoint(0.0, 0.0);
	std::vector<Point> samePoints{ samePoint, samePoint };
	const LineSegment line(samePoints);
	EXPECT_FALSE(line.IsValid());
}

TEST(Line, ConstructOnePoint)
{
	Point samePoint(0.0, 0.0);
	std::vector<Point> samePoints{ samePoint };
	const LineSegment line(samePoints);
	EXPECT_FALSE(line.IsValid());
}

TEST(Line, Construct0Points)
{
	std::vector<Point> samePoints;
	const LineSegment line(samePoints);
	EXPECT_FALSE(line.IsValid());
}


TEST(Line, Construct4Point)
{
	Point samePoint(0.0, 0.0);
	std::vector<Point> samePoints{ samePoint, Point(1.0, 0), samePoint, samePoint };
	const LineSegment line(samePoints);
	EXPECT_TRUE(line.IsValid());
}

TEST(Line, GetPoint)
{
	const LineSegment line(Point(0., 0.), Point(5., 5.));
	auto point = line.GetPoint(0.0);
	EXPECT_NEAR(point.X, 0., 1.e-7);
	EXPECT_NEAR(point.Y, 0., 1.e-7);

	point = line.GetPoint(1.);
	EXPECT_NEAR(point.X, 5., 1.e-7);
	EXPECT_NEAR(point.Y, 5., 1.e-7);

	point = line.GetPoint(0.5);
	EXPECT_NEAR(point.X, 2.5, 1.e-7);
	EXPECT_NEAR(point.Y, 2.5, 1.e-7);
}

TEST(Line, GetDerivative)
{
	const LineSegment line(Point(0., 0.), Point(5., 5.));
	auto der = line.GetDerivative(0.0);
	EXPECT_NEAR(der.X, 5., 1.e-7);
	EXPECT_NEAR(der.Y, 5., 1.e-7);

	der = line.GetDerivative(0.25);
	EXPECT_NEAR(der.X, 5., 1.e-7);
	EXPECT_NEAR(der.Y, 5., 1.e-7);

}

TEST(Line, GetRange)
{
	const LineSegment line(Point(0., 0.), Point(5., 5.));
	const auto range = line.GetRange();
	EXPECT_NEAR(range.Begin, 0., 1.e-7);
	EXPECT_NEAR(range.End, 1., 1.e-7);
}


TEST(Line, IsValid2)
{
	LineSegment line1(Point(2., 1.), Point(2., 1.));
	EXPECT_FALSE(line1.IsValid());

	LineSegment line2(Point(2., 1.), Point(3., 1.));
	EXPECT_TRUE(line2.IsValid());
}
