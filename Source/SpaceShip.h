/******************************************************************************
\file	SpaceShip.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Data.h" 
#include "Planet.h"
#include "Story.h"
#include "ParticleManager.h"

#define TOP_MAX 950
#define BOTTOM_MAX -230
#define RIGHT_MAX 1730
#define LEFT_MAX -450

//need adjust value
#define AD_TOP 1800
#define AD_BOTTOM -1080
#define AD_RIGHT 3200
#define AD_LEFT -1920

#define FULL_BOOST 100
#define AD_FULL_BOOST 600


	void InitShip(ReturnData &data);
	void AD_InitShip(ReturnData &data);
	void Planet_Gravity_Colision(Ship* pShip, Planet* pPlanet, Edge* pEdge, ReturnData &data, Particle *pCrash, ParticleManager *pPM, float dt, float &time);
	void MarkPosition(Ship* pShip, Object* pMark);
	void ArriveGoal(Ship* pShip, Goal * pGoal, ReturnData &data);
	void LaunchHudLogic(Ship* pShip, Object* pLaunch);
	void ShipMovement(Ship* pShip, float dt);
	void Asteroid_Collision(Ship* pShip, Asteroid *pAs, ReturnData &data, Particle *pCrash, ParticleManager *pPM);
	void LaunchShip(Ship *pShip);
	void Fuel_Collision(Ship *pShip, Object *pFuel, ReturnData &data);
	void DrawShip(Ship *pShip,ReturnData &data);
	void BoosterShip(Ship *pShip, Particle *pBooster, ParticleManager *pPM, float dt, ReturnData &data);
	void AngleOfShip(Ship* pShip, Object* pMark);
	void ByeBteShip(Ship* pShip, ReturnData &data, Particle *pByebye, ParticleManager *pPM);
	void AD_ByeBteShip(Ship* pShip, ReturnData &data, Particle *pByebye, ParticleManager *pPM);
	void Crash_Restart(ReturnData &data);
#endif