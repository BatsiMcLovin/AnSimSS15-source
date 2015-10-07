/*
 * Rocket.cpp
 *
 *  Created on: 11.09.2015
 *      Author: Daniel
 */


//includes
#include"Rocket.h"
#include "World.h"

	Rocket::Rocket(float massIN, glm::vec3 posIN, glm::vec3 dimensions) : RigidBody(massIN, posIN){

		this->mDimensions = dimensions;

		mVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
		mAngularVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
		mAngularMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
		mLinearMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
		mForce = glm::vec3 (0.0f, 0.0f, 0.0f);

		//calculate inertia tensor for the rocket as ellipsoid
		this->mInertiaTensor = glm::mat3(glm::vec3((mMass/5)*(mDimensions.y*mDimensions.y + mDimensions.z*mDimensions.z), 0, 0),
								glm::vec3(0, (mMass/5)*(mDimensions.x*mDimensions.x + mDimensions.z*mDimensions.z), 0),
								glm::vec3(0, 0, (mMass/5)*(mDimensions.x*mDimensions.x + mDimensions.y*mDimensions.y)));

		this->mInverseInertiaTensor = glm::inverse(mInertiaTensor);
	}
