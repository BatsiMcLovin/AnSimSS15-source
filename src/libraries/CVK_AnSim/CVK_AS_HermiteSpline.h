#ifndef __CVK_AS_HERMITE_SPLINE_H
#define __CVK_AS_HERMITE_SPLINE_H

#include "CVK_AS_HermiteSplineControlPoint.h"
#include "glm/glm.hpp"
#include <vector>

namespace CVK
{

struct ArcLengthTableEntry
{
	float u;
	int patchNumber;
	float arcLength;
};

class HermiteSpline
{
public:
	HermiteSpline();
	virtual ~HermiteSpline();
	void generateRenderVertices();
	void evaluateHermiteSpline(float u, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &point, glm::vec3 &tangent);

	//********************************************************************************
	void generateArcLengthTable(int resolution);
	void getParameterByArcLength(float length, float &u, int &patchNum);
	void calculateFrenetFrame(float u, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &tangent, glm::vec3 &binormal, glm::vec3 &normal);
	//********************************************************************************

	inline void addControlPoint(HermiteSplineControlPoint* c)				{ mControlPoints.push_back(c); }
	inline std::vector<HermiteSplineControlPoint*>* getControlPointsPtr()	{ return &mControlPoints; }
	inline std::vector<glm::vec3>* getVerticesPtr()							{ return &mVertices; }

private:
	std::vector<HermiteSplineControlPoint*> mControlPoints;
	std::vector<glm::vec3> mVertices;
	//********************************************************************************
	std::vector<ArcLengthTableEntry> mArcLengthTable;
	//********************************************************************************
	
	void deCasteljau(float t, std::vector<glm::vec3> &cp, glm::vec3 &point, glm::vec3 &tangent);
	void sampleHermiteSpline(HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, int numVerts);

};

};
#endif //__CVK_AS_HERMITE_SPLINE_H