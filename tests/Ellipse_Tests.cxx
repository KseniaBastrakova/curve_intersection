#include "gtest/gtest.h"
#include "curve_intersection/Curves/Ellipse.hxx"
#include "curve_intersection/Core/Vector.hxx"

using namespace CurveIntersection;

TEST(Ellipse, Constructor)
{
	Point aCenter(0., 0.);
	double aR1 = 1.;
	double aR2 = 2.;
	double aAngle = 1.;
	Ellipse aEllipse(aCenter, aR1, aR2, aAngle);
	EXPECT_EQ(aCenter, aEllipse.GetCenter());
	EXPECT_DOUBLE_EQ(aR1, aEllipse.GetMajorAxis());
	EXPECT_DOUBLE_EQ(aR2, aEllipse.GetMinorAxis());
	EXPECT_DOUBLE_EQ(aAngle, aEllipse.GetAngle());
}

TEST(Ellipse, CopyConstructor)
{
	Ellipse aEllipse(Point(2.,22.), 85., 3., 0.5);
	Ellipse aCopy = aEllipse;
	EXPECT_DOUBLE_EQ(aEllipse.GetMajorAxis(), aCopy.GetMajorAxis());
	EXPECT_DOUBLE_EQ(aEllipse.GetMinorAxis(), aCopy.GetMinorAxis());
	EXPECT_DOUBLE_EQ(aEllipse.GetAngle(), aCopy.GetAngle());
}

TEST(Ellipse, Assigment)
{
	Ellipse aEllipse(Point(55.,75.), 5., 1., 0.5);
	Ellipse aCopy(Point(0., 0.), 0., 0., 0.);
	aCopy = aEllipse;
	EXPECT_DOUBLE_EQ(aEllipse.GetMajorAxis(), aCopy.GetMajorAxis());
	EXPECT_DOUBLE_EQ(aEllipse.GetMinorAxis(), aCopy.GetMinorAxis());
	EXPECT_DOUBLE_EQ(aEllipse.GetAngle(), aCopy.GetAngle());
}

TEST(Ellipse, GetPoint)
{
	const Ellipse aEllipse(Point(2., 1.), 1., 4., PI / 4.);
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(0.),
		Point(2.7071067811865475, 1.7071067811865475)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*2.),
		Point(2.7071067811865475, 1.7071067811865475)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI / 4.), Point(0.5, 3.5)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*9. / 4.), Point(0.5, 3.5)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI), Point(1.292893218813452, 0.29289321881345287)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*5. / 4.), Point(3.5, -1.5)));
}

TEST(Ellipse, GetPoint2)
{
	const Ellipse aEllipse(Point(2., 1.), Point(2.7071067811865475, 1.7071067811865475), Point(0.5, 3.5));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(0.),
		Point(2.7071067811865475, 1.7071067811865475)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*2.),
		Point(2.7071067811865475, 1.7071067811865475)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI / 4.), Point(0.5, 3.5)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*9. / 4.), Point(0.5, 3.5)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI), Point(1.292893218813452, 0.29289321881345287)));
	EXPECT_TRUE(IsEqual(aEllipse.GetPoint(PI*5. / 4.), Point(3.5, -1.5)));
}

TEST(Ellipse, GetRange)
{
	const Ellipse aEllipse(Point(2., 1.), 1., 4., PI / 4.);
	const auto aRange = aEllipse.GetRange();
	EXPECT_DOUBLE_EQ(0., aRange.Begin);
	EXPECT_DOUBLE_EQ(PI*2., aRange.End);
}

TEST(Ellipse, GetMajorAxis)
{
	const Ellipse aEllipse(Point(2., 1.), 1., 4., PI / 4.);
	const auto aR1 = aEllipse.GetMajorAxis();
	EXPECT_DOUBLE_EQ(1., aR1);
}

TEST(Ellipse, GetMinorAxis)
{
	const Ellipse aEllipse(Point(2., 1.), 1., 4., PI / 4.);
	const auto aR2 = aEllipse.GetMinorAxis();
	EXPECT_DOUBLE_EQ(4., aR2);
}

TEST(Ellipse, GetAngle)
{
	const Ellipse aEllipse(Point(2., 1.), 1., 4., PI / 4.);
	const auto aAngle = aEllipse.GetAngle();
	EXPECT_DOUBLE_EQ(PI / 4, aAngle);
}

TEST(Ellipse, GetDerivative)
{
	const Ellipse ellipse(Point(2., 1.), 1., 4., PI / 4.);
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(0.), Vector(-2.82842712474619, 2.8284271247461903)));
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(PI*2.),
		Vector(-2.82842712474619, 2.8284271247461903)));
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(PI / 4.), Vector(-2.5, 1.5)));
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(PI*9. / 4.), Vector(-2.5, 1.5)));
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(PI),
		Vector(2.82842712474619, -2.8284271247461903)));
	EXPECT_TRUE(IsEqual(ellipse.GetDerivative(PI*5. / 4.), Vector(2.5, -1.5)));
}

TEST(Ellipse, InvalidConstructor)
{
	try {
		Ellipse aEllipse(Point(5., 5.), -1.,2, 0.);
		FAIL() << "Expected std::invalid_argument";
	}
	catch (const std::invalid_argument&) {
		GTEST_SUCCEED();
	}
	catch (...) {
		FAIL() << "Expected std::invalid_argument";
	}
}
