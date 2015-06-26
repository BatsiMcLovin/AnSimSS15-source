#include "CVK_AS_HermiteSpline.h"
#include <iostream>

#define ONE_THIRD (1.0f / 3.0f)
#define THRESH 0.001f

CVK::HermiteSpline::HermiteSpline()
{
}

CVK::HermiteSpline::~HermiteSpline()
{
}

void CVK::HermiteSpline::generateRenderVertices()
{
	std::vector<HermiteSplineControlPoint*>::iterator cpIt = mControlPoints.begin();
	while(cpIt != mControlPoints.end() - 1){
		sampleHermiteSpline(*cpIt, *(cpIt + 1), 32); 
		cpIt++;
	}
}

void CVK::HermiteSpline::generateArcLengthTable(int resolution)
{

	//********************************************************************************
	//TODO Aufgabe 5 (a)
	//Hier muss die Erstellung der Bogenlaengentabelle programmiert werden.
	//********************************************************************************

	int numPatches = mControlPoints.size() - 1;
	int stepsPerPatch = resolution / numPatches;
	float u;
	float uStep = 1.0f / stepsPerPatch;
	float len = 0.0;

	glm::vec3 point, lastPoint;

	for(int i=0; i<numPatches; i++){

		u = 0.0f;
		for(int j=0; j<=stepsPerPatch; j++){

			if(i != 0 && j == 0){
				u += uStep;
				continue;
			}

			glm::vec3 t;
			evaluateHermiteSpline(u, mControlPoints[i], mControlPoints[i + 1], point, t);

			ArcLengthTableEntry ale;
			ale.u = u;
			ale.patchNumber = i;
			if(i == 0 && j == 0){
				ale.arcLength = 0.0f;
			}
			else{
				ale.arcLength = (point - lastPoint).length() + mArcLengthTable.back().arcLength;
			}
			
			lastPoint = point;
			mArcLengthTable.push_back(ale);
			
			u += uStep;

		}
	}

}


void CVK::HermiteSpline::getParameterByArcLength(float length, float &u, int &patchNum){

	//********************************************************************************
	//TODO Aufgabe 5 (b)
	//Hier soll der Parameter u und der entsprechende Spline fuer eine gegebene Bogenlaenge
	//in der Tabelle gesucht. Ein binaeres Suchverfahren ist zu empfehlen.
	//********************************************************************************

	if(length > mArcLengthTable.back().arcLength){ //given length exeeds path length, return -1 as error
		u = -1.0;
		patchNum = -1;
		return;
	}

	bool found = false;
	int index;
	int indexLow = 0;
	int indexHi = mArcLengthTable.size() - 1;

	while(!found){
		index = indexLow + 0.5 * (indexHi - indexLow);

		if(mArcLengthTable[index].arcLength == length){ //found
			u = mArcLengthTable[index].u;
			patchNum = mArcLengthTable[index].patchNumber;
			found = true;
		}

		if(mArcLengthTable[index].arcLength > length){
			if(index - 1 >= 0){
				if(mArcLengthTable[index-1].arcLength < length){

					float frac = (length - mArcLengthTable[index-1].arcLength) / (mArcLengthTable[index].arcLength - mArcLengthTable[index-1].arcLength);

					float interpolLow = mArcLengthTable[index - 1].u;
					/*
					Ueberpr¸fung: der kleinere Wert ist der letzte Wert des vorherigen Patch
					In der Bogenl‰ngentabelle vgl.  Vorlesungsskript fehlt der Wert f¸r u = 0
					Daher Wert f¸r u=1 des vorherigen Patches nehmen.
					*/
					
					//if(interpolLow >= 1.0f){ 
					if(interpolLow >= 1.0f - THRESH && interpolLow <= 1.0f + THRESH){ 
						interpolLow = 0.0f;
					}
					float interpolHi =  mArcLengthTable[index].u;
					u = interpolLow + frac * (interpolHi - interpolLow);
					patchNum = mArcLengthTable[index].patchNumber;

					found = true;
				}
				else{
					indexHi = index - 1;
				}
			}
		}

		if(mArcLengthTable[index].arcLength < length){
			if(index + 1 < mArcLengthTable.size()){ //bounds check
				if(mArcLengthTable[index + 1].arcLength > length){

					float frac = (length - mArcLengthTable[index].arcLength) / (mArcLengthTable[index + 1].arcLength - mArcLengthTable[index].arcLength);

					float interpolLow = mArcLengthTable[index].u;
					//if(interpolLow >= 1.0f){
					if(interpolLow >= 1.0f - THRESH && interpolLow <= 1.0f + THRESH){ 
						interpolLow = 0.0f;
					}
					float interpolHi =  mArcLengthTable[index + 1].u;
					u = interpolLow + frac * (interpolHi - interpolLow);
					patchNum = mArcLengthTable[index + 1].patchNumber;
					
					found = true;
				}
				else{
					indexLow = index + 1;
				}
			}
		}
	}
}


void CVK::HermiteSpline::calculateFrenetFrame(float u, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &tangent, glm::vec3 &binormal, glm::vec3 &normal)
{

	//********************************************************************************
	//TODO Aufgabe 5 (c)
	//Hier soll der Frenet-Frame berechnet und in den uebergebenen Funktionsargumenten gespeichert werden.
	//Tipp: Sie brauchen noch die zweite Ableitung einer Bezier-Kurve ...
	//********************************************************************************

	std::vector<glm::vec3> bez;
	bez.push_back(c0->getPosition());
	bez.push_back(c0->getPosition() + ONE_THIRD * c0->getDirection());
	bez.push_back(c1->getPosition() - ONE_THIRD * c1->getDirection());
	bez.push_back(c1->getPosition());
	
	glm::vec3 point, t;
	deCasteljau(u, bez, point, tangent);

	glm::vec3 secDer =  (6.0f - 6.0f * u) * bez[0] +
					 	(18.0f * u - 12.0f) * bez[1] +
					  	(6.0f - 18.0f * u) * bez[2] +
						6.0f * u * bez[3];

	binormal = glm::normalize(glm::cross(tangent, secDer));
	normal = glm::normalize(glm::cross(binormal, tangent));

}

void CVK::HermiteSpline::sampleHermiteSpline(HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, int numVerts)
{
	for(int i = 0; i < numVerts; i++)
	{	
		glm::vec3 position, tangent;
		evaluateHermiteSpline((float) i/(numVerts-1),c0, c1, position, tangent);
		mVertices.push_back(position);
	}
}

void CVK::HermiteSpline::evaluateHermiteSpline(float t, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, glm::vec3 &point, glm::vec3 &tangent)
{
	std::vector<glm::vec3> bp;
	bp.push_back(c0->getPosition());
	bp.push_back(c0->getPosition() + ONE_THIRD * c0->getDirection());
	bp.push_back(c1->getPosition() - ONE_THIRD * c1->getDirection());
	bp.push_back(c1->getPosition());
	deCasteljau(t, bp, point, tangent);

}

void CVK::HermiteSpline::deCasteljau(float t, std::vector<glm::vec3> &cp, glm::vec3 &point, glm::vec3 &tangent)
{
	if(cp.size() == 2)
	{
		point = (1-t) * cp.at(0) + t * cp.at(1);
		tangent = cp.at(1) - cp.at(0);
		tangent = glm::normalize(tangent);
	}
	else
	{
	std::vector<glm::vec3> ncp;
	std::vector<glm::vec3>::iterator it = cp.begin();
	while( it != cp.end()-1)
	{
		ncp.push_back((1-t) * (*it) + t * (*(it+1)));
		it ++;
	}
	deCasteljau(t, ncp, point, tangent);
	}
}
