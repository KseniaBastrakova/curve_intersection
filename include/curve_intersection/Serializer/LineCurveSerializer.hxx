#pragma once
#include "FormattedCurveSerializer.hxx"
#include "LineCurve.hxx"


class LineCurveSerializer :public FormattedCurveSerializer {
public:
	LineCurveSerializer(Format theFormat) : FormattedCurveSerializer(theFormat) {}
	virtual std::unique_ptr<ICurve> Read(std::istream& theInput);
	virtual void Write(std::ostream& theOutput, const ICurve& theCurve);
	virtual std::string GetHeaderName();
	virtual ~LineCurveSerializer() = default;
};
