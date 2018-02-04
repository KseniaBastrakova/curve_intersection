#include "CurveExchanger.hxx"
#include "CurveIntersection.hxx"
#include <iostream>
#include <vector>


namespace {

	void PrintHelp() {
		std::cout << "Use of the reader :" << std::endl;
		std::cout << "First parametr - Path to file containing curves" << std::endl;
		std::cout << "The second parameter is the path to the output file for curves" << std::endl;
	}


	void RunTestTask (char* argv[]) {


		CurveIntersection aInresection;
		CurveExchanger aExchanger;
		std::vector<std::shared_ptr<ICurve>> aCurveVector = aExchanger.ReadCurves(std::string(argv[1]));
		std::vector<Point> aPoints = aInresection.Perform (*aCurveVector[0], *aCurveVector[1]);
		aExchanger.WriteCurves (aCurveVector, std::string (argv[2]));

		for (size_t i = 0; i < aPoints.size(); i++) {
			std::cout << " T1 =  " << aPoints[i].X;
			std::cout << " Point: " <<  "X = " << aCurveVector[0]->GetPoint (aPoints[i].X).X << "   " << "Y = "
				<< aCurveVector[0]->GetPoint (aPoints[i].X).Y << std::endl;
			std::cout << " T2 =  " << aPoints[i].Y;
			std::cout << " Point: " << "X = " << aCurveVector[1]->GetPoint (aPoints[i].Y).X << "   " << "Y = "
				<< aCurveVector[1]->GetPoint (aPoints[i].Y).Y << std::endl;

			double aDist = sqrt((aCurveVector[1]->GetPoint(aPoints[i].Y).X - aCurveVector[0]->GetPoint(aPoints[i].X).X) *
				(aCurveVector[1]->GetPoint(aPoints[i].Y).X - aCurveVector[0]->GetPoint(aPoints[i].X).X)

				+ (aCurveVector[1]->GetPoint(aPoints[i].Y).Y - aCurveVector[0]->GetPoint(aPoints[i].X).Y) *
				(aCurveVector[1]->GetPoint(aPoints[i].Y).Y - aCurveVector[0]->GetPoint(aPoints[i].X).Y));

			std::cout << "Distance " << aDist << std::endl;
		}
}
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "Wrong number of parameters" << std::endl;
		PrintHelp();
	} else {
		RunTestTask (argv);
	}

	return 0;
}