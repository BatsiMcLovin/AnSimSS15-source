/*
 * RigidBody.cpp
 *
 *  Created on: 01.09.2015
 *      Author: Daniel
 */


//includes
#include "RigidBody.h"
#include "Engine/World.h"

using namespace std;

RigidBody::RigidBody(float massIN, glm::vec3 posIN){
	mMass = massIN;
	mInverseMass = ((float)1.0)/mMass;

	mPosition = posIN;

	mVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	mAngularVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	mAngularMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	mLinearMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	mForce = glm::vec3 (0.0f, 0.0f, 0.0f);
	mStartingDirection = glm::vec3(glm::radians(0.f), glm::radians(0.f), glm::radians(90.f));
	mRotationQuat=glm::quat(mStartingDirection);
}

RigidBody::~RigidBody(){

}

void RigidBody::iterate(float duration, float gravityFac){
	calculateTorque();
	calculateForce();
	updateMomenta(duration, gravityFac);
	updateRotMatrix();
	updateInverseInertiaTensor();

	//performLinearStep
	mVelocity.x = mLinearMomentum.x / mMass;
	mPosition.x = mPosition.x + mVelocity.x*duration;

	mVelocity.y = mLinearMomentum.y / mMass;
	mPosition.y = mPosition.y + mVelocity.y*duration;

	mVelocity.z = mLinearMomentum.z / mMass;
	mPosition.z = mPosition.z + mVelocity.z*duration;

	//performAngularStep
	//update angular velocity
	float a = mInverseInertiaTensor[0].x;
	float b = mInverseInertiaTensor[0].y;
	float c = mInverseInertiaTensor[0].z;
	float d = mInverseInertiaTensor[1].x;
	float e = mInverseInertiaTensor[1].y;
	float f = mInverseInertiaTensor[1].z;
	float g = mInverseInertiaTensor[2].x;
	float h = mInverseInertiaTensor[2].y;
	float i = mInverseInertiaTensor[2].z;

	float u = mAngularMomentum.x;
	float v = mAngularMomentum.y;
	float w = mAngularMomentum.z;
	mAngularVelocity.x = a*u + b*v + c*w;
	mAngularVelocity.y = d*u + e*v + f*w;
	mAngularVelocity.z = g*u + h*v + i*w;

	float mAngularVelocitySize = glm::length(mAngularVelocity);

	if (mAngularVelocitySize > 0) {

		glm::vec3 mRotationAxis = glm::vec3(mAngularVelocity.x/mAngularVelocitySize,
									mAngularVelocity.y/mAngularVelocitySize,
									mAngularVelocity.z/mAngularVelocitySize);

		float rotationAngle = mAngularVelocitySize * duration;

		float ds = cos(rotationAngle/2.0f);
		float dvx = mRotationAxis.x*sin(rotationAngle/2.0f);
		float dvy = mRotationAxis.y*sin(rotationAngle/2.0f);
		float dvz = mRotationAxis.z*sin(rotationAngle/2.0f);

		float s = mRotationQuat.w;
		float vx = mRotationQuat.x;
		float vy = mRotationQuat.y;
		float vz = mRotationQuat.z;

		mRotationQuat.w = s*ds - vx*dvx - vy*dvy - vz*dvz;
		mRotationQuat.x = ds*vx + s*dvx + dvy*vz - dvz*vy;
		mRotationQuat.y = ds*vy + s*dvy + dvz*vx - dvx*vz;
		mRotationQuat.z = ds*vz + s*dvz + dvx*vy - dvy*vx;
	}


}

void RigidBody::updateRotMatrix(){

	glm::normalize(mRotationQuat);
	mRotationMat = glm::mat3_cast(mRotationQuat);
}

void RigidBody::updateInverseInertiaTensor(){
	mInverseInertiaTensor= mRotationMat*glm::inverse(mInertiaTensor)*glm::transpose(mRotationMat);
}


//in world space
void RigidBody::updateMomenta(float duration, float gravity){
	glm::vec3 rotatedForce= getRotationMat() * mForce;
	rotatedForce.y = rotatedForce.y + mMass * -gravity; //force of gravity
	mLinearMomentum = mLinearMomentum + duration * rotatedForce;
	mAngularMomentum = mAngularMomentum + duration * getRotationMat() * mTorque;
}

//in model space
void RigidBody::calculateTorque(){
	mTorque = glm::vec3(0,0,0);

	for(ForceActor* fA : mForces){
		mTorque += glm::cross(fA->getPosition(), fA->getForce());
	}
}

//in model space
void RigidBody::calculateForce(){
	mForce = glm::vec3(0,0,0);
	glm::vec3 currentForce;
	glm::vec3 currentTorque;
	for(ForceActor* fA : mForces){
		currentForce = fA->getForce();
		currentTorque = glm::cross(fA->getPosition(), fA->getForce());

		if((glm::length(currentForce) > glm::length(currentTorque))){
			if(glm::length(mTorque)!=0){
				currentForce = currentForce * ((glm::length(currentForce) - glm::length(currentTorque)) / glm::length(currentForce));
				mForce+=currentForce;
			}
			else mForce+=currentForce;
		}
		else{
			if(glm::length(mTorque)==0){
				mForce+=currentForce;
			}
		}
	}
}

void RigidBody::addForce(ForceActor* force){
	mForces.push_back(force);
}

void RigidBody::printInfo(){
	std::cout<< "Position: x="<< mPosition.x << "|| y="<<mPosition.y <<"|| z="<<mPosition.z<<endl;
	std::cout<< "Force: x="<< mForce.x << "|| y="<<mForce.y <<"|| z="<<mForce.z<< endl;
	std::cout<< "Torque: x="<< mTorque.x << "|| y="<<mTorque.y <<"|| z="<<mTorque.z<< endl;
	std::cout<< "LinearMomentum: x="<< mLinearMomentum.x << "|| y="<<mLinearMomentum.y <<"|| z="<<mLinearMomentum.z<< endl;
	std::cout<< "AngularMomentum: x="<< mAngularMomentum.x << "|| y="<<mAngularMomentum.y <<"|| z="<<mAngularMomentum.z<< endl;
}

void RigidBody::reset(glm::vec3 newPosition, glm::quat rotQuat){
	mPosition = newPosition;
	mVelocity = glm::vec3(0,0,0);
	mAngularVelocity = glm::vec3(0,0,0);
	mAngularMomentum = glm::vec3(0,0,0);
	mLinearMomentum = glm::vec3(0,0,0);
	mRotationQuat=rotQuat;
}

