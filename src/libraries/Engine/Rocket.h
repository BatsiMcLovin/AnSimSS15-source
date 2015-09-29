/*
 * Rocket.h
 *
 *  Created on: 11.09.2015
 *      Author: Daniel
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#include <glm/glm.hpp>
#include <vector>
#include "RigidBody.h"

class Rocket: public RigidBody {

private:
	glm::vec3 mDimensions; /**< dimensions of semi-axes "a", "b" and "c" of the elipsoid */


public:
	Rocket(float massIN, glm::vec3 posIN, glm::vec3 dimensions);

};


#endif /* ROCKET_H_ */
