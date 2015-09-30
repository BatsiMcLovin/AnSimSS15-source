/*
 * ForceActor.cpp
 *
 *  Created on: 29.09.2015
 *      Author: Batsi
 */

#include <Engine/ForceActor.h>

ForceActor::ForceActor(glm::vec3 force, glm::vec3 position) {
	this->mForce = force;
	this->mPosition = position;

}

ForceActor::~ForceActor() {
	// TODO Auto-generated destructor stub
}
