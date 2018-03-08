#include "gtest/gtest.h"
#include "curve_intersection/Core/Point.hxx"

using namespace CurveIntersection;

TEST(Point, DefaultConstructor)
{
	Point aPoint;
	EXPECT_EQ(0., aPoint.x);
	EXPECT_EQ(0., aPoint.y);
}

TEST(Point, Constructor)
{
	Point aPoint(5, 7);
	EXPECT_EQ(5., aPoint.x);
	EXPECT_EQ(7., aPoint.y);
}

TEST(Point, CopyConstructor)
{
	Point aPoint(5., 5.);
	Point aCopy = aPoint;
	EXPECT_EQ(aPoint.x, aCopy.x);
	EXPECT_EQ(aPoint.y, aCopy.y);
}

TEST(Point, Assigment)
{
	Point aPoint(9., 3.);
	Point aCopy;
	aCopy = aPoint;
	EXPECT_EQ(aPoint.x, aCopy.x);
	EXPECT_EQ(aPoint.y, aCopy.y);
}

TEST(Point, Distance)
{
	Point aPoint(2., 2.);
	Point aSecond(5., 6.);
	EXPECT_DOUBLE_EQ(5., Distance(aPoint, aSecond));
}

TEST(Point, Equality)
{
	Point aPoint(2., 2.);
	Point aSecond(2., 2.);
	Point aThird(3., 4.);
	EXPECT_TRUE(aPoint == aSecond);
	EXPECT_FALSE(aPoint == aThird);
}

TEST(Point, Inequality)
{
	Point aPoint(2., 2.);
	Point aSecond(2., 2.);
	Point aThird(5., 5.);
	EXPECT_FALSE(aPoint != aSecond);
	EXPECT_TRUE(aPoint != aThird);
}
