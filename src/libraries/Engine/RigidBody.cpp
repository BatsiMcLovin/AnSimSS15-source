/*
 * RigidBody.cpp
 *
 *  Created on: 01.09.2015
 *      Author: Daniel
 */


//includes
#include "RigidBody.h"
#include "World.h"

using namespace std;


RigidBody::RigidBody(float massIN, glm::vec3 posIN){
	mass = massIN;
	//inverseMass = ((float)1.0)/mass;

	position = posIN;

	velocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	angularVelocity = glm::vec3 (0.0f, 0.0f, 0.0f);
	angularMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	linearMomentum = glm::vec3 (0.0f, 0.0f, 0.0f);
	force = glm::vec3 (0.0f, 0.0f, 0.0f);

	//isStatic = staticIN;

	// inertiatensor diagonale berechnen
	//initInverseInertTensDiagon.x = initInverseInertTensDiagon.y = initInverseInertTensDiagon.z = 6.0f / (mass * 4 * sizeIN*sizeIN);

	//shape

	float temp1 = World::getInstance()->getTerminalVeloc();
	terminalMom = temp1 * mass;
}

RigidBody::~RigidBody(){
	//...
}

void RigidBody::iterate(float duration){
	updateInverseInertiaTensor();

	//performLinearStep
	velocity.x = linearMomentum.x / mass;
	position.x = position.x + velocity.x*duration;

	velocity.y = linearMomentum.y / mass;
	position.y = position.y + velocity.y*duration;

	velocity.z = linearMomentum.z / mass;
	position.z = position.z + velocity.z*duration;

	//performAngularStep
	{ //update angular velocity
		float a = inverseInertiaTensor[0].x;
		float b = inverseInertiaTensor[0].y;
		float c = inverseInertiaTensor[0].z;
		float d = inverseInertiaTensor[1].x;
		float e = inverseInertiaTensor[1].y;
		float f = inverseInertiaTensor[1].z;
		float g = inverseInertiaTensor[2].x;
		float h = inverseInertiaTensor[2].y;
		float i = inverseInertiaTensor[2].z;

		float u = angularMomentum.x;
		float v = angularMomentum.y;
		float w = angularMomentum.z;
		angularVelocity.x = a*u + b*v + c*w;
		angularVelocity.y = d*u + e*v + f*w;
		angularVelocity.z = g*u + h*v + i*w;
	}
	float angularVelocitySize = sqrt(angularVelocity.x*angularVelocity.x +
									 angularVelocity.y*angularVelocity.y +
									 angularVelocity.z*angularVelocity.z);

	if (angularVelocitySize > 0) {

		glm::vec3 rotationAxis = glm::vec3(	angularVelocity.x/angularVelocitySize,
											angularVelocity.y/angularVelocitySize,
											angularVelocity.z/angularVelocitySize);

		float rotationAngle = angularVelocitySize * duration;

		float ds = cos(rotationAngle/2.0f);
		float dvx = rotationAxis.x*sin(rotationAngle/2.0f);
		float dvy = rotationAxis.y*sin(rotationAngle/2.0f);
		float dvz = rotationAxis.z*sin(rotationAngle/2.0f);

		float s = rotationQuat.w;
		float vx = rotationQuat.x;
		float vy = rotationQuat.y;
		float vz = rotationQuat.z;

		rotationQuat.w = s*ds - vx*dvx - vy*dvy - vz*dvz;
		rotationQuat.x = ds*vx + s*dvx + dvy*vz - dvz*vy;
		rotationQuat.y = ds*vy + s*dvy + dvz*vx - dvx*vz;
		rotationQuat.z = ds*vz + s*dvz + dvx*vy - dvy*vx;
	}
}

void RigidBody::updateRotMatrix(){

	//normalizeQuaternion();
	glm::normalize(rotationQuat);

	float w = rotationQuat.w;
	float x = rotationQuat.x;
	float y = rotationQuat.y;
	float z = rotationQuat.z;

	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	//{ 1.0f-2.0f*(yy+zz), 2.0f*(xy-wz), 2.0f*(xz+wy),
	//  2.0f*(xy+wz), 1.0f-2.0f*(xx+zz), 2.0f*(yz-wx),
	//  2.0f*(xz-wy), 2.0f*(yz+wx), 1.0f-2.0f*(xx+yy) };
	float m1,m2,m3,m4,m5,m6,m7,m8,m9;
	m1 = 1.0f-2.0f*(yy+zz);
	m2 = 2.0f*(xy-wz);
	m3 = 2.0f*(xz+wy);
	m4 = 2.0f*(xy+wz);
	m5 = 1.0f-2.0f*(xx+zz);
	m6 = 2.0f*(yz-wx);
	m7 = 2.0f*(xz-wy);
	m8 = 2.0f*(yz+wx);
	m9 = 1.0f-2.0f*(xx+yy);

	rotationMat = glm::mat3(m1,m2,m3,m4,m5,m6,m7,m8,m9);
}

void RigidBody::updateInverseInertiaTensor(){
	float a = rotationMat[0].x;
	float b = rotationMat[0].y;
	float c = rotationMat[0].z;
	float d = rotationMat[1].x;
	float e = rotationMat[1].y;
	float f = rotationMat[1].z;
	float g = rotationMat[2].x;
	float h = rotationMat[2].y;
	float i = rotationMat[2].z;

	float u = initInverseInertTensDiagon.x;
	float v = initInverseInertTensDiagon.y;
	float w = initInverseInertTensDiagon.z;

	inverseInertiaTensor[0].x = u*a*a + b*b*v + c*c*w;
	inverseInertiaTensor[0].y = a*d*u + b*e*v + c*f*w;
	inverseInertiaTensor[0].z = a*g*u + b*h*v + c*i*w;
	inverseInertiaTensor[1].x = a*d*u + b*e*v + c*f*w;
	inverseInertiaTensor[1].y = u*d*d + e*e*v + f*f*w;
	inverseInertiaTensor[1].z = d*g*u + e*h*v + f*i*w;
	inverseInertiaTensor[2].x = a*g*u + b*h*v + c*i*w;
	inverseInertiaTensor[2].y = d*g*u + e*h*v + f*i*w;
	inverseInertiaTensor[2].z = u*g*g + h*h*v + i*i*w;
}

void RigidBody::updateMomenta(float duration){
	//...todo!
}

void RigidBody::reset(float newPosition){
	//...
}

