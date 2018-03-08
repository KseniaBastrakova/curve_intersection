
#include <gtest/gtest.h>
#include "curve_intersection/Curves/Bezier.hxx"
#include "curve_intersection/Curves/LineSegment.hxx"
#include "curve_intersection/Curves/Ellipse.hxx"
#include "curve_intersection/Intersection/CurveIntersection.hxx"
#include <memory>
#include <ctime>

using namespace CurveIntersection;

template<typename T>
bool compare(std::vector<T>& v1, std::vector<T>& v2)
{
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}


TEST(Line, Intersect1Point)
{
	LineSegment line1(Point(1., 1.), Point(3., 3.));
	LineSegment line2(Point(3., 1.), Point(1., 3.));
	Intersection intersection;
	std::vector<Point> points = intersection.Perform(line1, line2);
	EXPECT_FALSE(points.empty());
	
	EXPECT_TRUE(IsEqual(Point(2., 2.), line1.GetPoint(points[0].x)));
	EXPECT_TRUE(IsEqual(Point(2., 2.), line2.GetPoint(points[0].y)));
}

TEST(Ellipse, 2Intersect)
{
	Ellipse ellipse1(Point(0., 0.), 2., 1., 0.);
	Ellipse ellipse2(Point(0.5, 0.), 2., 1., 0.);
	Intersection intersection;
	std::vector<Point> points = intersection.Perform(ellipse1, ellipse2);
	EXPECT_FALSE(points.empty());
	EXPECT_TRUE(IsEqual(ellipse1.GetPoint(points[0].x), ellipse2.GetPoint(points[0].y)));
	EXPECT_TRUE(IsEqual(ellipse1.GetPoint(points[1].x), ellipse2.GetPoint(points[1].y)));
}

TEST(Ellipse, 1Intersect)
{
	Ellipse ellipse1(Point(0., 0.), 2., 1., 0.);
	Ellipse ellipse2(Point(0., 2.), 2., 1., 0.);
	Intersection intersection;
	std::vector<CurveIntersection::Point> points = intersection.Perform(ellipse1, ellipse2);
	EXPECT_FALSE(points.empty());
	EXPECT_TRUE(IsEqual(ellipse1.GetPoint(points[0].x), ellipse2.GetPoint(points[0].y)));
}
