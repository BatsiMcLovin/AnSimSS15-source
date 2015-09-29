/*
 * ForceActor.h
 *
 *  Created on: 29.09.2015
 *      Author: Batsi
 */

#ifndef FORCEACTOR_H_
#define FORCEACTOR_H_

#include <glm/glm.hpp>

class ForceActor {

private:
	glm::vec3 mForce;
	glm::vec3 mPosition;

public:
	ForceActor(glm::vec3 force, glm::vec3 position);
	virtual ~ForceActor();

	const glm::vec3& getForce() const {
		return mForce;
	}

	void setForce(const glm::vec3& force) {
		mForce = force;
	}

	const glm::vec3& getPosition() const {
		return mPosition;
	}

	void setPosition(const glm::vec3& position) {
		mPosition = position;
	}

};

#endif /* FORCEACTOR_H_ */
