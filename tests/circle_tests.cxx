#include "gtest/gtest.h"
#include "Curves/CircleCurve.hxx"
#include "Vector.hxx"

using namespace CurveIntersection;

class CircleTest : public ::testing::Test {
};

namespace {
static bool IsEqualPoints(Point p1, Point p2, double eps = NULL_TOL)
{
	return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
}

static bool IsEqualVectors(const Vector & v1, const Vector & v2, double eps = NULL_TOL)
{
	return fabs(v1.x - v2.x) < eps && fabs(v1.y - v2.y) < eps;
}
}

TEST(Circle, Construct0Point)
{
  std::vector<Point> wrongNumberPoints;
  const CircleCurve circle( wrongNumberPoints );
  EXPECT_FALSE( circle.IsValid() );
}

TEST(Circle, Construct1Point)
{
  std::vector<Point> wrongNumberPoints {Point(0., 0.)};
  const CircleCurve circle( wrongNumberPoints );
  EXPECT_FALSE( circle.IsValid() );
}

TEST(Circle, Construct2SamePoints)
{
  Point samePoint(0.0, 0.0);
  std::vector<Point> samePoints{samePoint, samePoint};
  const CircleCurve circle( samePoints );
  EXPECT_FALSE( circle.IsValid() );
}

TEST(Circle, Construct3Points)
{
  Point samePoint(0.0, 0.0);
  std::vector<Point> samePoints{samePoint, Point(2.2, 3.7), samePoint};
  const CircleCurve circle( samePoints );
  EXPECT_FALSE( circle.IsValid() );
}

TEST(Circle, GetPoint)
{
  const CircleCurve circle( Point(1., 1.), 2.);
  EXPECT_TRUE(IsEqualPoints(circle.GetPoint(0.), Point(3., 1.)));
  EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI*2.), Point(3., 1.)));
  EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI/4.), Point(1.+sqrt(2.), 1.+sqrt(2.))));
  EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI), Point(-1., 1.)));
  EXPECT_TRUE(IsEqualPoints(circle.GetPoint(PI*5./4.), Point(1.-sqrt(2.), 1.-sqrt(2.))) );
}

TEST(Circle, GetRange)
{
  const CircleCurve circle( Point(1., 1.), 2.);
  const auto range = circle.GetRange();
  EXPECT_NEAR( range.Begin, 0., NULL_TOL );
  EXPECT_NEAR( range.End, PI*2., NULL_TOL );
}

TEST(Circle, GetDerivative)
{
  const CircleCurve circle( Point(1., 1.), 2.);
  EXPECT_TRUE( IsEqualVectors(circle.GetDerivedPoint(0.), Vector(0., 2.)) );
  EXPECT_TRUE( IsEqualVectors(circle.GetDerivedPoint(PI*2.), Vector(0., 2.)) );
  EXPECT_TRUE( IsEqualVectors(circle.GetDerivedPoint(PI/4.), Vector(-sqrt(2.), sqrt(2.))) );
  EXPECT_TRUE(IsEqualVectors(circle.GetDerivedPoint(PI*9./4.), Vector(-sqrt(2.), sqrt(2.))));
  EXPECT_TRUE( IsEqualVectors(circle.GetDerivedPoint(PI), Vector(0., -2.)) );
  EXPECT_TRUE( IsEqualVectors(circle.GetDerivedPoint(PI*5./4.), Vector(sqrt(2.), -sqrt(2.))) );
}
