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
	Vector vector(3., 4.);
	EXPECT_DOUBLE_EQ(5., vector.Lenght());
}

TEST(Vector, Scaling)
{
	Vector aVector(1., 33.);
	Vector aResult = aVector * 2.;
	EXPECT_DOUBLE_EQ(2., aResult.x);
	EXPECT_DOUBLE_EQ(66., aResult.y);
}

TEST(Vector, Division)
{
	Vector vector(2., 22.);
	Vector result = vector / 2.;
	EXPECT_DOUBLE_EQ(1., result.x);
	EXPECT_DOUBLE_EQ(11., result.y);
}

TEST(Vector, SumVectorPoint)
{
	Vector aVector(3., 2);
	Point aPoint(1., 3);
	Vector result = aPoint + aVector;
	EXPECT_DOUBLE_EQ(4., result.x);
	EXPECT_DOUBLE_EQ(5., result.y);
}

TEST(Vector, IsCollinear)
{
	Vector aVector(1., 1);
	Vector aCollinearVector(2., 2);
	Vector aNonCollinearVector(7., 2);
	EXPECT_TRUE(IsCollinear(aVector, aCollinearVector));
	EXPECT_FALSE(IsCollinear(aVector,aNonCollinearVector));
}

TEST(Vector, UnaryMinus)
{
	Vector aVector(1., 1);
	Vector aResult = -aVector;
	EXPECT_DOUBLE_EQ(-1., aResult.x);
	EXPECT_DOUBLE_EQ(-1., aResult.y);
}

TEST(Vector, Difference)
{
	Point aPoint(2., 2.);
	Point aPointSecond(3., 3.);
	Vector aResult = aPoint - aPointSecond;
	EXPECT_DOUBLE_EQ(-1., aResult.x);
	EXPECT_DOUBLE_EQ(-1., aResult.y);
}

TEST(Vector, Rotate)
{
	Vector aVector(2., 2.);
	Vector aResult = Rotate(aVector, PI/2.);
	EXPECT_DOUBLE_EQ(-2., aResult.x);
	EXPECT_DOUBLE_EQ(2., aResult.y);
}
