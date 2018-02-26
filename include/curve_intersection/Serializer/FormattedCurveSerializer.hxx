#pragma once
#include "ICurveSerializer.hxx"
class FormattedCurveSerializer : public ICurveSerializer {
public:
	enum class Format { Text, Binary };
	FormattedCurveSerializer(Format theFormat) :
		myFormat(theFormat) {}

	Format getFormat() const;
	void setFormat(Format theFormat);
	virtual std::string GetHeaderName() = 0;

private:
	Format myFormat;
protected:

	void WriteSeparator(std::ostream& theOutput) const;
	Point ReadPoint(std::istream& theInput) const;
	void WritePoint(std::ostream& theOutput, const Point& thePoint) const;
	double ReadDouble(std::istream& theInput) const;
	void WriteDouble(std::ostream& theOutput, double theValue) const;
	double ReadInt(std::istream& theInput) const;
	void WriteInt(std::ostream& theOutput, int theValue) const;

};
