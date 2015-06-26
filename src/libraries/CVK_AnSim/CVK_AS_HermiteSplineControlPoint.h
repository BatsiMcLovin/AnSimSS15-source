#ifndef __CVK_AS_HERMITE_SPLINE_CONTROL_POINT_H
#define __CVK_AS_HERMITE_SPLINE_CONTROL_POINT_H

#include "glm/glm.hpp"

namespace CVK
{


class HermiteSplineControlPoint
{
	public:
		HermiteSplineControlPoint();
		HermiteSplineControlPoint(glm::vec3 pos, glm::vec3 dir);
		virtual ~HermiteSplineControlPoint();
		
		inline void setPosition(glm::vec3 p){mPosition = p;}
		inline void setDirection(glm::vec3 d){mDirection = d;}

		inline glm::vec3 getPosition(){return mPosition;}
		inline glm::vec3 getDirection(){return mDirection;}

	private:
		glm::vec3 mPosition;
		glm::vec3 mDirection;

};

};
#endif //__CVK_AS_HERMITE_SPLINE_CONTROL_POINT_H