#include "CVK_AS_MassPoint.h"
#include <iostream>
CVK::MassPoint::MassPoint(void)
{
	mMass = 1.0f;
}


CVK::MassPoint::MassPoint(glm::vec3 pos, glm::vec3 vel, float m){
	mPosition = pos;
	mVelocity = vel;
	mMass = m;
}


CVK::MassPoint::~MassPoint(void)
{
}

void CVK::MassPoint::numericIntegration(float d_t)
{	
	// TODO Aufgabe 4 (a)
	// Implementieren Sie das Euler Integrationsverfahren.
	mPosition=mPosition+mVelocity*d_t;
	mVelocity=mVelocity+(mCurrentForce/mMass)*d_t;
	zeroForce();
}
