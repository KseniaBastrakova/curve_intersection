#include "gtest/gtest.h"
#include "Curves/LineSegment.hxx"

using namespace CurveIntersection;

TEST(LineSegment, Constructor)
{
	Point aStart(2., 3.);
	Point aEnd(3., 6.);
	LineSegment aLineSegment(aStart, aEnd);
	EXPECT_EQ(aStart, aLineSegment.GetStart());
	EXPECT_EQ(aEnd, aLineSegment.GetEnd());
}

TEST(LineSegment, CopyConstructor)
{
	LineSegment aLineSegment(Point(5.,5), Point(7.,8.));
	LineSegment aCopy = aLineSegment;
	EXPECT_EQ(aLineSegment.GetStart(), aCopy.GetStart());
	EXPECT_EQ(aLineSegment.GetEnd(), aCopy.GetEnd());
}

TEST(LineSegment, Assigment)
{
	LineSegment aLineSegment(Point(5.,5.), Point(7.,8));
	LineSegment aCopy(Point(0., 0.), Point(11., 0.));
	aCopy = aLineSegment;
	EXPECT_EQ(aLineSegment.GetStart(), aCopy.GetStart());
	EXPECT_EQ(aLineSegment.GetEnd(), aCopy.GetEnd());
}

TEST(LineSegment, InvalidConstructor)
{
	try {
		LineSegment aLineSegment(Point(5., 5.), Point(5., 5));
		FAIL() << "Expected std::invalid_argument";
	}
	catch (const std::invalid_argument&) {
		GTEST_SUCCEED();
	}
	catch (...) {
		FAIL() << "Expected std::invalid_argument";
	}
}

TEST(LineSegment, GetPoint)
{
  const LineSegment line( Point(0., 0.), Point(5., 5.) );
  auto point = line.GetPoint( 0.0 );
  EXPECT_NEAR( point.x, 0., 1.e-7 );
  EXPECT_NEAR( point.y, 0., 1.e-7 );

  point = line.GetPoint( 1. );
  EXPECT_NEAR( point.x, 5., 1.e-7 );
  EXPECT_NEAR( point.y, 5., 1.e-7 );

  point = line.GetPoint( 0.5 );
  EXPECT_NEAR( point.x, 2.5, 1.e-7 );
  EXPECT_NEAR( point.y, 2.5, 1.e-7 );
}

TEST(LineSegment, GetDerivative)
{
  const LineSegment line( Point(0., 0.), Point(5., 5.) );
  auto der = line.GetDerivative( 0.0 );
  EXPECT_NEAR( der.x, 5., 1.e-7 );
  EXPECT_NEAR( der.y, 5., 1.e-7 );

  der = line.GetDerivative( 0.25 );
  EXPECT_NEAR( der.x, 5., 1.e-7 );
  EXPECT_NEAR( der.y, 5., 1.e-7 );

}

TEST(LineSegment, GetRange)
{
  const LineSegment line( Point(0., 0.), Point(5., 5.) );
  const auto range = line.GetRange();
  EXPECT_NEAR( range.Begin, 0., 1.e-7 );
  EXPECT_NEAR( range.End, 1., 1.e-7 );
}



