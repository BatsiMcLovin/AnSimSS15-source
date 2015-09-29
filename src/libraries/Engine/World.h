/*
 * World.h
 *
 *  Created on: 01.09.2015
 *      Author: Daniel
 */


#ifndef WORLD_H_
#define WORLD_H_


//includes
#include <vector>
#include "RigidBody.h"
#include "Rocket.h"
#include <GL\glew.h>
#include <iostream>
#include "../designPatterns/Singleton.h"


/** \brief physics World
 *
 * class for the physics simulation world representation
 */
class World: public Singleton <World> {
	friend class Singleton<World>;

private:

	float worldSize;					/**< world size */

	float springCoeff;					/**< spring coefficient */
	float dampCoeff;					/**< damping coefficient */
	float gravity;						/**< gravity force value */

	int allBodyNum;					/**< number of bodies in the world */

	float duration;					/**< step duration */
	float terminalVeloc;				/**< terminal velocity */

public:

	RigidBody **allBodies;				/**< list of all bodies in the world */

	/** \brief constructor
	 *
	 * creates the world instance
	 * @param wsIN world size
	 * @param prIN particle radius
	 * @param scIN spring coefficient
	 * @param dcIN damping coefficient
	 * @param bNum number of bodies
	 */
	World(float wsIN, float prIN, float scIN, float dcIN, int bNum,float durIN, float tvIN);

	/** \brief default constructor
	*
	* creates the world instance
	* -not implemented-
	*/
	World();

	/** \brief destructor
	 *
	 * destroys the world instance
	 */
	~World();

	/** \brief step physics simulation
	 *
	 * ...
	 * @param duration time length of a simulation step
	 * @return void
	 */
	void stepPhysics(float duration);


	//getter + setter

		float getWorldSize() const {
			return worldSize;
		}

		void setWorldSize(float worldSize) {
			this->worldSize = worldSize;
		}

		float getSpringCoeff() const {
			return springCoeff;
		}

		void setSpringCoeff(float springCoeff) {
			this->springCoeff = springCoeff;
		}

		float getDampCoeff() const {
			return dampCoeff;
		}

		void setDampCoeff(float dampCoeff) {
			this->dampCoeff = dampCoeff;
		}

		float getGravity() const {
			return gravity;
		}

		void setGravity(float gravity) {
			this->gravity = gravity;
		}

		int getAllBodyNum() const {
			return allBodyNum;
		}

		void setAllBodyNum(int allbodyNum) {
			this->allBodyNum = allbodyNum;
		}

		 RigidBody**& getAllBodies() {
			return allBodies;
		}

		void setAllBodies( RigidBody**& allBodies) {
			this->allBodies = allBodies;
		}


		float getTerminalVeloc() const {
			return terminalVeloc;
		}

		void setTerminalVeloc(float terminalVeloc) {
			this->terminalVeloc = terminalVeloc;
		}

		float getDuration() const {
			return duration;
		}

		void setDuration(float duration) {
			this->duration = duration;
		}
};

#endif /* WORLD_H_ */
