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

public:

	glm::vec3 origin;				/**< origin of the shape = position of RigidBody */
	//float size						/**< scale/size of the shape */
	glm::vec3 powerUnit1force;		/**< force of power unit 1 */
	glm::vec3 powerUnit2force;		/**< force of power unit 2 */

	//.......

};


#endif /* ROCKET_H_ */
