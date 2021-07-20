/******************************************************************************
\file	Physic
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef PHYSIC_H
#define PHYSIC_H

#include "Data.h"

float Distance_planet(Ship *pShip, Planet *pPlanet);
float Distance_goal(Ship *pShip, Goal *pGoal);
float Distance_asteroid(Ship *pShip, Asteroid *pAs);
float Distance_planet_edge(Ship *pShip, Edge *pEdge);
float Distance_fuel(Ship *pShip, Object *pFuel);

float Universalgravitation(Ship *pShip, Planet *pPlanet);

float Vectorx(Ship *pShip, Planet *pPlanet);
float Vectory(Ship *pShip, Planet *pPlanet);

float Normalx(Ship *pShip, Planet *pPlanet);
float Normaly(Ship *pShip, Planet *pPlanet);

float Collision_planet_x(Ship *pShip, Planet *pPlanet);
float Collision_planet_y(Ship *pShip, Planet *pPlanet);
float Collision_planet(Ship *pShip, Planet *pPlanet);
float Collision_planet_edge_x(Ship *pShip, Edge *pEdge);
float Collision_planet_edge_y(Ship *pShip, Edge *pEdge);
float Collision_planet_edge(Ship *pShip, Edge *pEdge);
float Collision_goal_x(Ship *pShip, Goal *pGoal);
float Collision_goal_y(Ship *pShip, Goal *pGoal);
float Collision_goal(Ship *pShip, Goal *pGoal);
float Collision_fuel_x(Ship *pShip, Object *pFuel);
float Collision_fuel_y(Ship *pShip, Object *pFuel);
float Collision_fuel(Ship *pShip,   Object *pFuel);
float Collision_asteroid_x(Ship *pShip, Asteroid *pAs);
float Collision_asteroid_y(Ship *pShip, Asteroid *pAs);
float Collision_asteroid(Ship *pShip, Asteroid *pAs);

float Vectormarkx(Ship *pShip, Object *pMark);
float Vectormarky(Ship *pShip, Object *pMark);
void After_Launch_Angle(Ship *pShip, WEVec2 *mouse);
void Before_Launch_Angle(Ship *pShip, Object *pMark);
float DistanceMouseWithShip(WEVec2 mouse, Ship *pShip);
float DistanceMouseWithShip(WEVec2 mouse, Asteroid *pAsteroid);



#endif PHYSIC_H
