#include "gtest/gtest.h"
#include "Serializer/EllipseSerializer.hxx"
#include <fstream>
#include <stdio.h>

using namespace CurveIntersection;

TEST(EllipseSerializer, WriteEllipseTxt)
{
	EllipseCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	Point aCenter(8., 17.);
	double aMajorRadius = 111.;
	double aMinorRadius = 1.;
	double aAngle = 0.5;
	Ellipse aEllipse(aCenter, aMajorRadius, aMinorRadius, aAngle);
	aSerializer.Write(aOutput, aEllipse);
	aOutput.close();

	std::ifstream theInput;
	theInput.open("Test.txt");
	double aValueX = 0.;
	double aValueY = 0;
	theInput >> aValueX;
	theInput >> aValueY;
	EXPECT_DOUBLE_EQ(aValueX, 8.);
	EXPECT_DOUBLE_EQ(aValueY, 17.);

	double aValueMajorRadius = 0.;
	double aValueMinorRadius = 0.;
	aAngle = 0.;
	theInput >> aValueMajorRadius;
	theInput >> aValueMinorRadius;
	theInput >> aAngle;
	EXPECT_DOUBLE_EQ(aValueMajorRadius, 111.);
	EXPECT_DOUBLE_EQ(aValueMinorRadius, 1.);
	EXPECT_DOUBLE_EQ(aAngle, 0.5);
	remove("Test.txt");
}

TEST(EllipseSerializer, ReadEllipseTxt)
{
	EllipseCurveSerializer aSerializer(FormattedCurveSerializer::Format::Text);
	std::ofstream aOutput;
	aOutput.open("Test.txt");
	Point aCenter(8., 17.);
	double aMajorRadius = 111.;
	double aMinorRadius = 1.;
	double aAngle = 0.5;
	Ellipse aEllipse(aCenter, aMajorRadius, aMinorRadius, aAngle);
	aSerializer.Write(aOutput, aEllipse);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.txt");
	std::unique_ptr<ICurve> aEllipseRead = aSerializer.Read(aInput);
	Ellipse* aCurve = dynamic_cast<Ellipse*>(aEllipseRead.get());
	EXPECT_EQ(aCenter, aCurve->GetCenter());
	EXPECT_EQ(aMajorRadius, aCurve->GetMajorAxis());
	EXPECT_EQ(aMinorRadius, aCurve->GetMinorAxis());
	EXPECT_EQ(aAngle, aCurve->GetAngle());
	remove("Test.txt");
}

TEST(EllipseSerializer, WriteReadEllipseBin)
{
	EllipseCurveSerializer aSerializer(FormattedCurveSerializer::Format::Binary);
	std::ofstream aOutput;
	aOutput.open("Test.bin");
	Ellipse aEllipse(Point(55., 33), 7., 1., 0.5);
	aSerializer.Write(aOutput, aEllipse);
	aOutput.close();

	std::ifstream aInput;
	aInput.open("Test.bin");
	std::unique_ptr<ICurve> aEllipseRead = aSerializer.Read(aInput);
	Ellipse* aCurve = dynamic_cast<Ellipse*>(aEllipseRead.get());
	EXPECT_EQ(aEllipse.GetCenter(), aCurve->GetCenter());
	EXPECT_EQ(aEllipse.GetMajorAxis(), aCurve->GetMajorAxis());
	EXPECT_EQ(aEllipse.GetMinorAxis(), aCurve->GetMinorAxis());
	EXPECT_EQ(aEllipse.GetAngle(), aCurve->GetAngle());
	remove("Test.bin");
}
