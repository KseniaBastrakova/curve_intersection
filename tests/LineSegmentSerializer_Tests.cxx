#include "gtest/gtest.h"
#include "Serializer/LineSegmentSerializer.hxx"
#include <fstream>
#include <stdio.h>

using namespace CurveIntersection;

TEST(LineSegmentSerializer, WriteLineSegmentTxt)
{
	LineSegmentSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	LineSegment aLineSegment(Point(1., 1.), Point(5., 5.));
	aSerializer.Write(aOutput, aLineSegment);
	aOutput.close();

	std::ifstream theInput;
	theInput.open("Test.txt");
	double aValueX = 0.;
	double aValueY = 0;
	theInput >> aValueX;
	theInput >> aValueY;
	EXPECT_DOUBLE_EQ(aValueX, 1.);
	EXPECT_DOUBLE_EQ(aValueY, 1.);

	theInput >> aValueX;
	theInput >> aValueY;
	EXPECT_DOUBLE_EQ(aValueX, 5.);
	EXPECT_DOUBLE_EQ(aValueY, 5.);
	remove("Test.txt");
}

TEST(LineSegmentSerializer, ReadLineSegmentTxt)
{
	LineSegmentSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	Point aStart(1., 1.);
	Point aEnd(5., 5);
	LineSegment aLineSegment(aStart, aEnd);
	aSerializer.Write(aOutput, aLineSegment);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.txt");
	std::unique_ptr<ICurve> aLineSegmentRead = aSerializer.Read(aInput);
	LineSegment* aCurve = dynamic_cast<LineSegment*>(aLineSegmentRead.get());
	EXPECT_EQ(aStart, aCurve->GetStart());
	EXPECT_EQ(aEnd, aCurve->GetEnd());
	remove("Test.txt");
}

TEST(LineSegmentSerializer, WriteReadLineSegmentBin)
{
	LineSegmentSerializer aSerializer(FormattedCurveSerializer::Format::Binary);
	std::ofstream aOutput;
	aOutput.open("Test.bin");
	Point aStart(1., 1.);
	Point aEnd(5., 5);
	LineSegment aLineSegment(aStart, aEnd);
	aSerializer.Write(aOutput, aLineSegment);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.bin");
	std::unique_ptr<ICurve> aLineSegmentRead = aSerializer.Read(aInput);
	LineSegment* aCurve = dynamic_cast<LineSegment*>(aLineSegmentRead.get());
	EXPECT_EQ(aStart, aCurve->GetStart());
	EXPECT_EQ(aEnd, aCurve->GetEnd());
	remove("Test.bin");
}
