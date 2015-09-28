/*
 * RigidBody.h
 *
 *  Created on: 01.09.2015
 *      Author: Daniel
 */


#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_


//includes
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>


/** \brief RigidBody
 *
 * class for rigid body representation
 */
class RigidBody {

private:

	float mMass;							/**< body mass */
	//float inverseMass;					/**< body inverse mass */	//ka ob nötig

	glm::vec3 mPosition;					/**< body position */
	glm::vec3 mVelocity;					/**< body velocity */
	//glm::vec3 lastFrameVeloc;				/**< body last frame velocity */	//ka ob nötig
	glm::quat mRotationQuat;					/**< body rotation quaternion */
	glm::mat3 mRotationMat;					/**< body rotation matrix */
	glm::mat3 mInertiaTensor;				/**< body inertia tensor */
	glm::vec3 mInitInverseInertTensDiagon;		/**< initial inverse inertia tensor diagonal */
	glm::mat3 mInverseInertiaTensor;			/**< inverse inertia tensor */

	glm::vec3 mAngularVelocity;				/**< angular velocity */
	glm::vec3 mAngularMomentum;				/**< angular momentum */
	glm::vec3 mLinearMomentum;				/**< linear momentum */
	float mTerminalMom;						/**< terminal momentum */	//?

	glm::vec3 mForce;						/**< body force */
	bool mIsStatic;						/**< true if object is static, false if object is dynamic */
	glm::mat4 mTransformMatrix;				/**< transformation matrix */

public:

	/** \brief constructor
	 *
	 * creates a rigid body instance with given parameters
	 * @param massIN mass
	 * @param posIN position
	 * @param rotIN rotation
	 */
	RigidBody(float massIN, glm::vec3 posIN);

	/** \brief standard constructor
	*
	* creates a rigidBody instance
	*/
	RigidBody();

	/** \brief destructor
	 *
	 * destroys a rigid body instance
	 */
	~RigidBody();

	/** \brief iterate
	 *
	 * perform linear and angular step to update velocity, position and rotation
	 * @param duration time length of a simulation step
	 * @return void
	 */
	void iterate(float duration);

	/** \brief update rotations matrix
	 *
	 * update rotation matrix with new rotation quaternion
	 * @return void
	 */
	void updateRotMatrix();

	/** \brief update inverse inertia tensor
	 *
	 * update inertia tensor with new rotation matrix
	 * @return void
	 */
	void updateInverseInertiaTensor();

	/** \brief update momenta
	 *
	 * apply gravity and update linear and angular momenta
	 * @param duration time length of a simulation step
	 * @return void
	 */
	void updateMomenta(float duration);

	//
	void reset(float newPosition);


	/** \brief calculate forces
	 *
	 * calculate forces with colliding neighbor particles and grid boundries
	 * @return current calculated force
	 */
	glm::vec3 calculateForces(bool wgIN);


	//getter + settter
	const glm::vec3& getPosition() const {
		return mPosition;
	}

	void setPosition(const glm::vec3& position) {
		this->mPosition = position;
	}

	const glm::mat3& getRotationMat() const {
		return mRotationMat;
	}

	void setRotationMat(const glm::mat3& rotationMat) {
		this->mRotationMat = rotationMat;
	}

	const glm::quat& getRotationQuat() const {
		return mRotationQuat;
	}

	void setRotationQuat(const glm::quat& rotationQuat) {
		this->mRotationQuat = rotationQuat;
	}

	void setInertiaTensor(const glm::mat3& inertia){
		this->mInertiaTensor = inertia;
	}

};


#endif /* RIGIDBODY_H_ */
