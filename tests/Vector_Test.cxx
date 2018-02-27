#include "gtest/gtest.h"
#include "Vector.hxx"
#include "Base_Structures.hxx"

using namespace CurveIntersection;

TEST(Vector, DefaultConstructor)
{
	Vector aVector;
	EXPECT_EQ(0., aVector.x);
	EXPECT_EQ(0., aVector.y);
}

TEST(Vector, Constructor)
{
	Vector aVector(6, 8);
	EXPECT_EQ(6., aVector.x);
	EXPECT_EQ(8., aVector.y);
}

TEST(Vector, CopyConstructor)
{
	Vector aVector(4., 7.);
	Vector aCopy = aVector;
	EXPECT_EQ(aVector.x, aCopy.x);
	EXPECT_EQ(aVector.y, aCopy.y);
}

TEST(Vector, Assigment)
{
	Vector aVector(9., 3.);
	Vector aCopy;
	aCopy = aVector;
	EXPECT_EQ(aVector.x, aCopy.x);
	EXPECT_EQ(aVector.y, aCopy.y);
}

TEST(Vector, Lenght)
{
	Vector vector(2., 2.);
	EXPECT_DOUBLE_EQ(2.8284270999, vector.Lenght());
}

TEST(Vector, ScalarMult)
{
	Vector vector(1., 33.);
	Vector result = vector * 2.;
	EXPECT_DOUBLE_EQ(2., result.x);
	EXPECT_DOUBLE_EQ(66., result.y);
}

TEST(Vector, SumVectorPoint)
{
	Vector vector(3., 2);
	Point point(1., 3);
	Vector result = point + vector;
	EXPECT_DOUBLE_EQ(4., result.x);
	EXPECT_DOUBLE_EQ(5., result.y);
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
	EXPECT_DOUBLE_EQ(-1., result.x);
	EXPECT_DOUBLE_EQ(-1., result.y);
}

TEST(Vector, OperatorMinus)
{
	Point point(2., 2.);
	Point pointSecond(3., 3.);
	Vector result = point - pointSecond;
	EXPECT_DOUBLE_EQ(-1., result.x);
	EXPECT_DOUBLE_EQ(-1., result.y);
}

TEST(Vector, Rotate)
{
	Vector vector(2., 2.);
	Vector result = Rotate(vector, PI/2.);
	EXPECT_DOUBLE_EQ(-2., result.x);
	EXPECT_DOUBLE_EQ(2., result.y);
}