/******************************************************************************
\file	Object.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef OBJECTS_H
#define OBJECTS_H

#define FUEL_BOOST 30
#define AD_FUEL_BOOST 300

#define BOOL_FUEL 100

#include "Data.h"
#include "FileIO.h"

void InitMark(ReturnData &data);
void InitLaunch(ReturnData &data);
void InitGoal(ReturnData &data);
void InitAsteroid(ReturnData &data);
void InitFuel(ReturnData &data);

void AD_InitGoal(ReturnData &data);
void AD_InitAsteroid(ReturnData &data);
void AD_InitFuel(ReturnData &data);
void CT_InitAsteroid(ReturnData &data);
void CT_InitFuel(ReturnData &data);

void ObjectMovement(Asteroid* pAsteroid, float dt, ObjectManager* pOM);
void AsteroidDurab(Asteroid* pAsteroid, ObjectManager* pOM);
void FillFuel(Object *pFuel, Ship *pShip);
void AD_FillFuel(Object *pFuel, Ship *pShip);
void Have_Fuel(Object *pFuel);

void DrawMark(Object *pMark);
void DrawLaunch(Object *pLaunch);
void DrawGoal(Goal *pGoal);
void DrawAsteroid(Asteroid *pAsteroid, ReturnData &data);
void DrawFuel(Object *pFuel, ReturnData &data);
#endif