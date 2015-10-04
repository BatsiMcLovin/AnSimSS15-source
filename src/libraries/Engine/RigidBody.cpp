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

//World *world = World::getInstance();


RigidBody::RigidBody(float massIN, glm::vec3 posIN){
	mMass = massIN;
	mInverseMass = ((float)1.0)/mMass;

	mPosition = posIN;

	mVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	mAngularVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	mAngularMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	mLinearMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	mForce = glm::vec3 (0.0f, 0.0f, 0.0f);
	mStartingDirection = glm::vec3(glm::radians(0.f), glm::radians(0.f), glm::radians(-90.f));
	mRotationQuat=glm::quat(mStartingDirection);

	//isStatic = staticIN;

	// inertiatensor diagonale berechnen
	//initInverseInertTensDiagon.x = initInverseInertTensDiagon.y = initInverseInertTensDiagon.z = 6.0f / (mass * 4 * sizeIN*sizeIN);

	//shape

//	float temp1 = World::getInstance()->getTerminalVeloc();
//	mTerminalMom = temp1 * mMass;
}

RigidBody::~RigidBody(){
	//...
}

void RigidBody::iterate(float duration){
	calculateForce();
	calculateTorque();
	updateMomenta(duration);
	updateRotMatrix();
	updateInverseInertiaTensor();

	//performLinearStep
	mVelocity.x = mLinearMomentum.x / mMass;
	mPosition.x = mPosition.x + mVelocity.x*duration;

	mVelocity.y = mLinearMomentum.y / mMass;
	mPosition.y = mPosition.y + mVelocity.y*duration;
	cout<<"Position in Y is: "<< mPosition.y << endl;

	mVelocity.z = mLinearMomentum.z / mMass;
	mPosition.z = mPosition.z + mVelocity.z*duration;

	//performAngularStep
	{ //update angular velocity
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
	}
	float mAngularVelocitySize = sqrt(mAngularVelocity.x*mAngularVelocity.x +
									 mAngularVelocity.y*mAngularVelocity.y +
									 mAngularVelocity.z*mAngularVelocity.z);

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

	//normalizeQuaternion();
	glm::normalize(mRotationQuat);

//	float w = mRotationQuat.w;
//	float x = mRotationQuat.x;
//	float y = mRotationQuat.y;
//	float z = mRotationQuat.z;
//
//	float xx = x * x;
//	float yy = y * y;
//	float zz = z * z;
//	float xy = x * y;
//	float xz = x * z;
//	float yz = y * z;
//	float wx = w * x;
//	float wy = w * y;
//	float wz = w * z;
//
//	//{ 1.0f-2.0f*(yy+zz), 2.0f*(xy-wz), 2.0f*(xz+wy),
//	//  2.0f*(xy+wz), 1.0f-2.0f*(xx+zz), 2.0f*(yz-wx),
//	//  2.0f*(xz-wy), 2.0f*(yz+wx), 1.0f-2.0f*(xx+yy) };
//	float m1,m2,m3,m4,m5,m6,m7,m8,m9;
//	m1 = 1.0f-2.0f*(yy+zz);
//	m2 = 2.0f*(xy-wz);
//	m3 = 2.0f*(xz+wy);
//	m4 = 2.0f*(xy+wz);
//	m5 = 1.0f-2.0f*(xx+zz);
//	m6 = 2.0f*(yz-wx);
//	m7 = 2.0f*(xz-wy);
//	m8 = 2.0f*(yz+wx);
//	m9 = 1.0f-2.0f*(xx+yy);
//
//	mRotationMat = glm::mat3(m1,m2,m3,m4,m5,m6,m7,m8,m9);

	mRotationMat = glm::mat3_cast(mRotationQuat);
}

void RigidBody::updateInverseInertiaTensor(){
//	float a = mRotationMat[0].x;
//	float b = mRotationMat[0].y;
//	float c = mRotationMat[0].z;
//	float d = mRotationMat[1].x;
//	float e = mRotationMat[1].y;
//	float f = mRotationMat[1].z;
//	float g = mRotationMat[2].x;
//	float h = mRotationMat[2].y;
//	float i = mRotationMat[2].z;
//
//	float u = mInitInverseInertTensDiagon.x;
//	float v = mInitInverseInertTensDiagon.y;
//	float w = mInitInverseInertTensDiagon.z;
//
//	mInverseInertiaTensor[0].x = u*a*a + b*b*v + c*c*w;
//	mInverseInertiaTensor[0].y = a*d*u + b*e*v + c*f*w;
//	mInverseInertiaTensor[0].z = a*g*u + b*h*v + c*i*w;
//	mInverseInertiaTensor[1].x = a*d*u + b*e*v + c*f*w;
//	mInverseInertiaTensor[1].y = u*d*d + e*e*v + f*f*w;
//	mInverseInertiaTensor[1].z = d*g*u + e*h*v + f*i*w;
//	mInverseInertiaTensor[2].x = a*g*u + b*h*v + c*i*w;
//	mInverseInertiaTensor[2].y = d*g*u + e*h*v + f*i*w;
//	mInverseInertiaTensor[2].z = u*g*g + h*h*v + i*i*w;

	mInverseInertiaTensor= mRotationMat*glm::inverse(mInertiaTensor)*glm::transpose(mRotationMat);

}
//in world space
void RigidBody::updateMomenta(float duration){

	//Die restliche Force wird in Abhängigkeit der verrechneten Torque bestimmt, da für die Drehung ja Kraft aufgewendet wird.
	//Formel (selbst erdacht): restForce = gesamtForce * ((|gesamtForce| - |Torque|)/|gesamtForce|)

	if(glm::length(mForce)!=0){
		glm::vec3 rotatedForce = getRotationMat() * mForce * ((glm::length(mForce) - glm::length(mTorque)) / glm::length(mForce));
		rotatedForce.y = rotatedForce.y + mMass * - 0.0981; //force of gravity
	mLinearMomentum = mLinearMomentum + duration * rotatedForce;
	}
	std::cout<< "LinearMomentumX is: "<< mLinearMomentum.x << "|| LinearMomentumY is: "<<mLinearMomentum.y <<"|| LinearMomentumZ is: "<<mLinearMomentum.z<< endl;
	mAngularMomentum = mAngularMomentum + duration * getRotationMat() * mTorque;
	std::cout<< "AngularMomentumX is: "<< mAngularMomentum.x << "|| AngularMomentumY is: "<<mAngularMomentum.y <<"|| AngularMomentumZ is: "<<mAngularMomentum.z<< endl;
}

//in model space
void RigidBody::calculateTorque(){
	mTorque = glm::vec3(0,0,0);

	for(ForceActor* fA : mForces){
		mTorque += glm::cross(fA->getPosition(), fA->getForce());
	}
		std::cout<< "TorqueX is: "<< mTorque.x << "|| TorqueY is: "<<mTorque.y <<"|| TorqueZ is: "<<mTorque.z<< endl;
}

//in model space
void RigidBody::calculateForce(){
	mForce = glm::vec3(0,0,0);
	for(ForceActor* fA : mForces){
		mForce += fA->getForce();
	}
		mForce= getRotationMat()* mForce;
		std::cout<< "ForceX is: "<< mForce.x << "|| ForceY is: "<<mForce.y <<"|| ForceZ is: "<<mForce.z<< endl;
		mForce= glm::inverse(getRotationMat()) * mForce;
}

void RigidBody::addForce(ForceActor* force){
	mForces.push_back(force);
}

void RigidBody::reset(glm::vec3 newPosition){
	mPosition = newPosition;
	mVelocity = glm::vec3(0,0,0);
	mAngularVelocity = glm::vec3(0,0,0);
	mAngularMomentum = glm::vec3(0,0,0);
	mLinearMomentum = glm::vec3(0,0,0);
	mRotationQuat=glm::quat(mStartingDirection);
}

