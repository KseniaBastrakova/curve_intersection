#include "gtest/gtest.h"
#include "Serializer/BezierCurveSerializer.hxx"
#include <fstream>
#include <stdio.h>

using namespace CurveIntersection;

TEST(BezierCurveSerializer, WriteBezierTxt)
{
	BezierCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	std::vector<Point> aPoints = { Point(1., 1.), Point(5., 5.), Point(2.,1.),
	Point(7.,7.) };
	Bezier aBezier(aPoints);
	aSerializer.Write(aOutput, aBezier);
	aOutput.close();

	std::ifstream theInput;
	theInput.open("Test.txt");
	size_t aSize = 0;
	theInput >> aSize;
	for (size_t i = 0; i < aSize; i++) {
		double aValueX = 0.;
		double aValueY = 0;
		theInput >> aValueX;
		theInput >> aValueY;

		EXPECT_DOUBLE_EQ(aValueX, aPoints[i].x);
		EXPECT_DOUBLE_EQ(aValueY, aPoints[i].y);
	}

	remove("Test.txt");
}

TEST(BezierCurveSerializer, ReadBezierTxt)
{
	BezierCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	std::vector<Point> aPoints = { Point(7., 1.), Point(3., 4.), Point(5.,6.),
		Point(7.,7.) };
	Bezier aBezier(aPoints);
	aSerializer.Write(aOutput, aBezier);
	aOutput.close();
	std::ifstream aInput;
	aInput.open("Test.txt");
	std::unique_ptr<ICurve> aBezierRead = aSerializer.Read(aInput);
	Bezier* aCurve = dynamic_cast<Bezier*>(aBezierRead.get());
	for (size_t i = 0; i < aCurve->GetControlPoints().size(); i++) {
		IsEqual(aPoints[i], aCurve->GetControlPoints()[i]);
	}
	
}

TEST(BezierCurveSerializer, WriteReadBezierBin)
{
	BezierCurveSerializer aSerializer(FormattedCurveSerializer::Format::Binary);
	std::ofstream aOutput;
	aOutput.open("Test.bin");
	std::vector<Point> aPoints = { Point(6., 5.), Point(3., 3.), Point(5.,6.),
		Point(5.,7.) };
	Bezier aBezier(aPoints);
	aSerializer.Write(aOutput, aBezier);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.bin");
	std::unique_ptr<ICurve> aBezierRead = aSerializer.Read(aInput);
	Bezier* aCurve = dynamic_cast<Bezier*>(aBezierRead.get());
	for (size_t i = 0; i < aCurve->GetControlPoints().size(); i++) {
		IsEqual(aPoints[i], aCurve->GetControlPoints()[i]);
	}
}