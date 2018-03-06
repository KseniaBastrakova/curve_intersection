#include "gtest/gtest.h"
#include "Serializer/CircleCurveSerializer.hxx"
#include <fstream>
#include <stdio.h>

using namespace CurveIntersection;

TEST(CircleSerializer, WriteCircleTxt)
{
	CircleCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	Point aCenter(7., 11.);
	double aRadius = 8.;
	CircleCurve aCircle(aCenter, aRadius);
	aSerializer.Write(aOutput, aCircle);
	aOutput.close();

	std::ifstream theInput;
	theInput.open("Test.txt");
	double aValueX = 0.;
	double aValueY = 0;
	theInput >> aValueX;
	theInput >> aValueY;
	EXPECT_DOUBLE_EQ(aValueX, 7.);
	EXPECT_DOUBLE_EQ(aValueY, 11.);

	double aValueRadius = 0.;
	theInput >> aValueRadius;
	EXPECT_DOUBLE_EQ(aValueRadius, 8.);
	remove("Test.txt");
}

TEST(CircleSerializer, ReadCircleTxt)
{
	CircleCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	Point aCenter(15., 7.);
	double aRadius = 9.;
	CircleCurve aCircle(aCenter, aRadius);
	aSerializer.Write(aOutput, aCircle);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.txt");
	std::unique_ptr<ICurve> aLineSegmentRead = aSerializer.Read(aInput);
	CircleCurve* aCurve = dynamic_cast<CircleCurve*>(aLineSegmentRead.get());
	EXPECT_EQ(aCenter, aCurve->GetCenter());
	EXPECT_EQ(aRadius, aCurve->GetRadius());
	remove("Test.txt");
}

TEST(CircleSerializer, WriteReadCircleBin)
{
	CircleCurveSerializer aSerializer(FormattedCurveSerializer::Format::Binary);
	std::ofstream aOutput;
	aOutput.open("Test.bin");
	Point aCenter(777., 888.);
	double aRadius = 11.;
	CircleCurve aCircle(aCenter, aRadius);
	aSerializer.Write(aOutput, aCircle);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.bin");
	std::unique_ptr<ICurve> aLineSegmentRead = aSerializer.Read(aInput);
	CircleCurve* aCurve = dynamic_cast<CircleCurve*>(aLineSegmentRead.get());
	EXPECT_EQ(aCenter, aCurve->GetCenter());
	EXPECT_EQ(aRadius, aCurve->GetRadius());
	remove("Test.bin");
}