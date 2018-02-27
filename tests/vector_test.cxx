#include "gtest/gtest.h"
#include "Vector.hxx"
#include "Base_Structures.hxx"

using namespace CurveIntersection;

TEST(Vector, Lenght)
{
	Vector vector(2., 2.);
	EXPECT_NEAR(vector.Lenght(), 2.8284271, NULL_TOL);
}

TEST(Vector, ScalarMult)
{
	Vector vector(1., 33.);
	Vector result = vector * 2.;
	EXPECT_NEAR(result.x, 2., NULL_TOL);
	EXPECT_NEAR(result.y, 66., NULL_TOL);
}

TEST(Vector, SumVectorPoint)
{
	Vector vector(3., 2);
	Point point(1., 3);
	Vector result = point + vector;
	EXPECT_NEAR(result.x, 4., NULL_TOL);
	EXPECT_NEAR(result.y, 5., NULL_TOL);
}

TEST(Vector, IsCollinear)
{
	Vector vector(1., 1);
	Vector collinearVector(2., 2);
	Vector nonCollinearVector(7., 2);
	EXPECT_TRUE(IsCollinear(vector, collinearVector));
	EXPECT_FALSE(IsCollinear(vector,nonCollinearVector));
}

TEST(Vector, ReverseOperator)
{
	Vector vector(1., 1);
	Vector result = -vector;
	EXPECT_NEAR(result.x, -1., NULL_TOL);
	EXPECT_NEAR(result.y, -1., NULL_TOL);
}
