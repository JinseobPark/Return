/******************************************************************************
\file	EditObject.h
\title  Returner
\author Minwoo Choi, Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved 

******************************************************************************/
#pragma once

#include "Data.h"
#include "FileIO.h"
#include "EditObject.h"

void EditAsteroid(Asteroid* pAsteroid, ObjectManager* pOM);
void EditPlanet(Planet* pPlanet, ObjectManager* pOM);
void EditAsteroidVel(Asteroid* pAsteroid, ObjectManager* pOM);
void EditFuel(Object* pObject, ObjectManager* pOM);