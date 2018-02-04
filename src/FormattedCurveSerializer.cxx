#include "FormattedCurveSerializer.hxx"

FormattedCurveSerializer::Format FormattedCurveSerializer::getFormat() const {
	return myFormat;
}

void FormattedCurveSerializer::setFormat (FormattedCurveSerializer::Format theFormat) {
	myFormat = theFormat;
}

void  FormattedCurveSerializer::WriteSeparator (std::ostream& theOutput) const {
	if (myFormat == Format::Text)
		theOutput << " ";
}

Point FormattedCurveSerializer::ReadPoint (std::istream& theInput) const {
	Point aPoint;
	aPoint.X = ReadDouble(theInput);
	aPoint.Y = ReadDouble(theInput);
	return aPoint;
}

void FormattedCurveSerializer::WritePoint (std::ostream& theOutput, const Point& thePoint) const {
	WriteDouble (theOutput, thePoint.X);
	WriteDouble (theOutput, thePoint.Y);
}

double FormattedCurveSerializer::ReadDouble (std::istream& theInput) const {
	double aValue;
	if (myFormat == Format::Text) {	
		theInput >> aValue;
		return aValue;
	} else {
		theInput.read ((char*) &aValue, sizeof aValue);
		return aValue;
	}
}


double FormattedCurveSerializer::ReadInt(std::istream& theInput) const {
	if (myFormat == Format::Text) {
		int aValue;
		theInput >> aValue;
		return aValue;
	} else {
		int aValue;
		theInput.read((char*)&aValue, sizeof aValue);
		return aValue;
	}
}
void FormattedCurveSerializer::WriteDouble (std::ostream& theOutput, double theValue) const {
	if (myFormat == Format::Text)
		theOutput << theValue;
	if (myFormat == Format::Binary)
		theOutput.write ((char*)&theValue, sizeof theValue);
	WriteSeparator (theOutput);
}

void FormattedCurveSerializer::WriteInt(std::ostream& theOutput, int theValue) const {
	if (myFormat == Format::Text)
		theOutput << theValue;
	if (myFormat == Format::Binary)
		theOutput.write((char*)&theValue, sizeof theValue);
	WriteSeparator(theOutput);
}