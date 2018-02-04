#include "EvaluationLipschitzConstant.hxx"
#include <algorithm>
#include <iostream>
#include <vector>
double GridResult (std::vector<std::vector<double>> theGridValues, int i, int j, int i_, int j_,
	double theStepX, double theStepY) {
	if (i == i_ || j == j_) return 0;
	return abs(theGridValues[i][j] - theGridValues[i_][j_]) /
		sqrt((i * theStepX - i_ * theStepX) * (i * theStepX - i_ * theStepX) + 
		(j * theStepY - j_* theStepY) * (j * theStepY - j_* theStepY));
}
double LipschitzConstantEvaluator::Evaluate(int theResolution) const {

	double aStepX = (myRangeX.End - myRangeX.Begin) / theResolution;
	double aStepY = (myRangeY.End - myRangeY.Begin) / theResolution;
	double aLipschitzConstant = -1;
	std::vector<std::vector<double>> aLipschitzConstantGridValues;

	aLipschitzConstantGridValues.resize (theResolution);
	for (int i = 0; i < theResolution; i++)
		aLipschitzConstantGridValues[i].resize (theResolution);

	for (int i = 0; i < theResolution; i++)
		for (int j = 0; j < theResolution; j++) {
			aLipschitzConstantGridValues[i][j] = myFunction (i * aStepX, j * aStepY);
 		}
	for (int i = 0; i < theResolution; i++)
		for (int j = 0; j < theResolution; j++) {
			int ip = std::min (i + 1, theResolution - 1);
			int im = std::max (i - 1, 0);
			int jp = std::min (j + 1, theResolution - 1);
			int jm = std::max (j - 1, 0);
			std::vector<double> aGridValues;
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, im, jm, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, im, j, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, im, jp, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, i, jp, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, ip, jp, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, i, jp, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, ip, jm, aStepX, aStepY));
			aGridValues.push_back (GridResult (aLipschitzConstantGridValues, i, j, i, jm, aStepX, aStepY));
			aLipschitzConstant = std::max (aLipschitzConstant, *std::max_element (aGridValues.begin(), aGridValues.end()));
		}
	return aLipschitzConstant * 1.2;
}