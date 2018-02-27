
#include <gtest/gtest.h>
#include "Curves/BezierCurve.hxx"
#include "Curves/LineCurve.hxx"
#include "Curves/EllipseCurve.hxx"
#include "Intersection/CurveIntersection.hxx"
#include <memory>
#include <ctime>



template<typename T>
bool compare(std::vector<T>& v1, std::vector<T>& v2)
{
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}
namespace {
static bool IsEqualPoints(const CurveIntersection::Point & p1, const CurveIntersection::Point & p2, 
	double eps = CurveIntersection::NULL_TOL)
{
	return fabs(p1.x - p2.x) < eps && fabs(p1.y - p2.y) < eps;
}
}
// в простейшем случае точка пересечения находится верно
TEST(Line, Intersect1Point)
{
	// пересечение двух прямых
	CurveIntersection::LineSegment line1(CurveIntersection::Point(1., 1.), CurveIntersection::Point(3., 3.));
	CurveIntersection::LineSegment line2(CurveIntersection::Point(3., 1.), CurveIntersection::Point(1., 3.));
	CurveIntersection::CurveIntersection intersection;
	//std::vector<Point> points = intersection.Perform(line1, line2);
	//EXPECT_FALSE(points.empty());
//	EXPECT_TRUE(IsEqualPoints(Point(2., 2.), points[0]));
//	// начало одной прямой - конец другой прямой
//	Math::Line line3(Math::Point(3., 1.), Math::Point(5., 1.));
//	haveIntersect = Math::IntersectLines(line3, line2, point);
//EXPECT_TRUE(haveIntersect);
//	EXPECT_TRUE(Math::IsEqual(Math::Point(3., 1.), point));
	// отрезки лежат на одной прямой, начало одного - конец другого
//	Math::Line line4(Math::Point(3., 3.), Math::Point(4., 4.));
//	haveIntersect = Math::IntersectLines(line1, line4, point);
//EXPECT_TRUE(haveIntersect);
//	EXPECT_TRUE(Math::IsEqual(Math::Point(3., 3.), point));

}

TEST(Ellipse, 2Intersect)
{
	CurveIntersection::EllipseCurve ellipse1(CurveIntersection::Point(0., 0.), 2., 1., 0.);
	CurveIntersection::EllipseCurve ellipse2(CurveIntersection::Point(0.5, 0.), 2., 1., 0.);
	CurveIntersection::CurveIntersection intersection;
//	std::vector<CurveIntersection::Point> points = intersection.Perform(ellipse1, ellipse2);
//	EXPECT_FALSE(points.empty());
//	EXPECT_TRUE(IsEqualPoints(ellipse1.GetPoint(points[0].X), ellipse2.GetPoint(points[0].Y)));
//	EXPECT_TRUE(IsEqualPoints(ellipse1.GetPoint(points[1].X), ellipse2.GetPoint(points[1].Y)));
}

TEST(Ellipse, 1Intersect)
{
	CurveIntersection::EllipseCurve ellipse1(CurveIntersection::Point(0., 0.), 2., 1., 0.);
	CurveIntersection::EllipseCurve ellipse2(CurveIntersection::Point(0., 2.), 2., 1., 0.);
	CurveIntersection::CurveIntersection intersection;
	//std::vector<CurveIntersection::Point> points = intersection.Perform(ellipse1, ellipse2);
//	EXPECT_FALSE(points.empty());
//	EXPECT_TRUE(IsEqualPoints(ellipse1.GetPoint(points[0].X), ellipse2.GetPoint(points[0].Y)));
}


TEST(Ellipse, 0Intersect)
{
	CurveIntersection::EllipseCurve ellipse1(CurveIntersection::Point(0., 0.), 2., 1., 0.);
	CurveIntersection::EllipseCurve ellipse2(CurveIntersection::Point(0., 777.), 2., 1., 0.);
	CurveIntersection::CurveIntersection intersection;
//	std::vector<CurveIntersection::Point> points = intersection.Perform(ellipse1, ellipse2);
//	EXPECT_TRUE(points.empty());
}