#pragma once
#include "ICurveSerializer.hxx"

namespace CurveIntersection {
	// Reading and writing a geometric primitive.
class FormattedCurveSerializer : public ICurveSerializer {
public:
	// Two types of reading and writing geometric primitive.
	enum class Format { Text, Binary };
	FormattedCurveSerializer(Format theFormat) :
		myFormat(theFormat) {}
	// Return format
	Format getFormat() const;
	// Set Format
	void setFormat(Format theFormat);
	// Name of geometric primitive
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
}
