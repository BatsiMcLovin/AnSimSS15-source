#include "CVK_AS_HermiteSplineControlPoint.h"

CVK::HermiteSplineControlPoint::HermiteSplineControlPoint()
{
}


CVK::HermiteSplineControlPoint::HermiteSplineControlPoint(glm::vec3 pos, glm::vec3 dir){
	mPosition = pos;
	mDirection = dir;
}


CVK::HermiteSplineControlPoint::~HermiteSplineControlPoint()
{
}
