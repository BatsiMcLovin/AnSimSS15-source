/*
 * World.cpp
 *
 *  Created on: 01.09.2015
 *      Author: Daniel
 */


//include
#include "World.h"
#include "RigidBody.h"

using namespace std;


World::World(float wsIN, float prIN, float scIN, float dcIN, int bNum,float durIN, float tvIN){

	worldSize = wsIN;

	springCoeff = scIN;
	dampCoeff = dcIN;
	gravity = 9.81f;
	allBodyNum = bNum;
	allBodies = new RigidBody*[allBodyNum];

	duration = durIN;
	terminalVeloc = tvIN;
}

World::~World(){
	//...
}

void World::stepPhysics(float duration){

	//ausführung auf cpu


	//update momenta
	for (int i = 0; i < allBodyNum; i++){

		allBodies[i]->updateMomenta(duration);
	}

	//iterate
	for (int i = 0; i < allBodyNum; i++){

		allBodies[i]->iterate(duration);
	}

}
