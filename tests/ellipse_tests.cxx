#include "gtest/gtest.h"
#include "Curves/EllipseCurve.hxx"
#include "Vector.hxx"

using namespace CurveIntersection;

namespace {
static bool IsEqualPoints(const Point & p1, const Point & p2, double eps = NULL_TOL)
{
	return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
}

static bool IsEqualVectors(const Vector & v1, const Vector & v2, double eps = NULL_TOL)
{
	return fabs(v1.x - v2.x) < eps && fabs(v1.y - v2.y) < eps;
}

}
class EllipseTest : public ::testing::Test {
};

TEST(Ellipse, Construct3PointsOnLine)
{
  std::vector<Point> PointsOnLine { Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0) };
  const EllipseCurve ellipse( PointsOnLine );
  EXPECT_FALSE( ellipse.IsValid() );
}

TEST(Ellipse, Construct3SamePoints)
{
  Point samePoint( 0.0, 0.0 );
  std::vector<Point> samePoints { samePoint, samePoint, samePoint };
  const EllipseCurve ellipse( samePoints );
  EXPECT_FALSE( ellipse.IsValid() );
}

TEST(Ellipse, Construct3Points)
{
  std::vector<Point> points { Point(0., 0.), Point(1.2, 2.5), Point(0.5, 1.7) };
  const EllipseCurve ellipse( points );
  EXPECT_TRUE( ellipse.IsValid() );
}

TEST(Ellipse, Construct5SamePoints)
{
  Point samePoint( 0.0, 0.0 );
  std::vector<Point> samePoints { samePoint, samePoint, samePoint, samePoint, samePoint };
  const EllipseCurve ellipse( samePoints );
  EXPECT_FALSE( ellipse.IsValid() );
}


TEST(Ellipse, GetPoint)
{
	const EllipseCurve ellipse( Point(2., 1.), 1., 4., PI/4. );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(0.),
                             Point(2.7071067811865475, 1.7071067811865475)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI*2.),
	  Point(2.7071067811865475, 1.7071067811865475)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI/4.), Point(0.5, 3.5)) );
  EXPECT_TRUE(IsEqualPoints(ellipse.GetPoint(PI*9. / 4.), Point(0.5, 3.5)));
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI), Point(1.292893218813452, 0.29289321881345287)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI*5./4.), Point(3.5, -1.5)) );
}

TEST(Ellipse, GetPoint2)
{
  std::vector<Point> points = { Point(2., 1.), Point(2.7071067811865475, 1.7071067811865475), Point(0.5, 3.5) };
  const EllipseCurve ellipse( points );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(0.),
                             Point(2.7071067811865475, 1.7071067811865475)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI*2.),
                             Point(2.7071067811865475, 1.7071067811865475)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI/4.), Point(0.5, 3.5)) );
  EXPECT_TRUE(IsEqualPoints(ellipse.GetPoint(PI*9. / 4.), Point(0.5, 3.5)));
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI), Point(1.292893218813452, 0.29289321881345287)) );
  EXPECT_TRUE( IsEqualPoints(ellipse.GetPoint(PI*5./4.), Point(3.5, -1.5)) );
}

TEST(Ellipse, GetRange)
{
	const EllipseCurve ellipse(Point(2., 1.), 1., 4., PI / 4.);
	const auto range = ellipse.GetRange();
	EXPECT_NEAR(range.Begin, 0., NULL_TOL);
	EXPECT_NEAR(range.End, PI*2., NULL_TOL);
}

TEST(Ellipse, Construct5PointsOnLine)
{
  std::vector<Point> points { Point(0.0, 0.0), Point(1.0, 1.0), Point(4.0, 4.0), Point(3.0, 3.0), Point(1.1, 2.4) };
  const EllipseCurve ellipse( points );
  EXPECT_FALSE( ellipse.IsValid() );
}

TEST(Ellipse, ConstructCRRA)
{
  const EllipseCurve ellipse( Point(1., 1.), 0, 1., PI/4. );
  EXPECT_FALSE( ellipse.IsValid() );
}

TEST(Ellipse, ConstructCRRA2)
{
  const EllipseCurve ellipse( Point(1., 1.), 2., 3., 0. );
  EXPECT_TRUE( ellipse.IsValid() );
}

TEST(Ellipse, GetDerivative)
{
  const EllipseCurve ellipse( Point(2., 1.), 1., 4., PI/4. );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(0.), Vector(-2.82842712474619, 2.8284271247461903)) );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(PI*2.),
                             Vector(-2.82842712474619, 2.8284271247461903)) );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(PI/4.), Vector(-2.5, 1.5)) );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(PI*9./4.), Vector(-2.5, 1.5)) );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(PI),
                             Vector(2.82842712474619, -2.8284271247461903)) );
  EXPECT_TRUE( IsEqualVectors(ellipse.GetDerivedPoint(PI*5./4.), Vector(2.5, -1.5)) );
}

