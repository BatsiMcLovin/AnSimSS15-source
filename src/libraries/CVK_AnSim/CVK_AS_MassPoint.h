#ifndef __CVK_AS_MASS_POINT_H
#define __CVK_AS_MASS_POINT_H

#include "glm/glm.hpp"

namespace CVK
{
    
class MassPoint
{
	//---------------CONSTRUCTORS & DESTRUCTOR---------------
	public:
		MassPoint(void);
		MassPoint(glm::vec3 pos, glm::vec3 vel, float m);
		~MassPoint(void);

	//---------------MEMBER VARIABLES------------------------
	private:
		glm::vec3 mPosition;
		glm::vec3 mVelocity;
		float mMass;
		
		glm::vec3 mCurrentForce;

	//---------------MEMBER FUNCTIONS------------------------
	public:

		void numericIntegration(float d_t);

		inline void setPosition(glm::vec3 &p)	{mPosition = p;}
		inline void setVelocity(glm::vec3 &v)	{mVelocity = v;}
		inline void setMass(float m)			{mMass = m;}

		inline glm::vec3 getPosition(void)		{return mPosition;}
		inline glm::vec3 getVelocity(void)		{return mVelocity;}
		inline float getMass(void)				{return mMass;}
		inline glm::vec3 getCurrentForce(void)	{return mCurrentForce;}

		inline void applyForce(glm::vec3 f)		{mCurrentForce += f;}
		inline void zeroForce(void)				{mCurrentForce = glm::vec3(0.0f);}

};
}
#endif