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


RigidBody::RigidBody(float massIN, bool staticIN, glm::vec3 posIN, glm::quat rotIN){
	this->mMass = massIN;
	this->mIsStatic = staticIN;
	this->mPosition = posIN;
	this->mRotationQuat = rotIN;
}

RigidBody::~RigidBody(){
	//...
}

void RigidBody::iterate(float duration){
	//...
}

void RigidBody::updateRotMatrix(){
	//...
}

void RigidBody::updateInverseInertiaTensor(){
	//...
}

void RigidBody::updateMomenta(float duration){
	//...
}

void RigidBody::reset(float newPosition){
	//...
}

