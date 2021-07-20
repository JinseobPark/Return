/******************************************************************************
\file	Physic.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Physic.h"
#include <cmath>

#define GRACOS 10000 //constant of gravitation
//distance ball to planet
float Distance_planet(Ship *pShip, Planet *pPlanet)
{
	/*
	float dx, dy, dr;

	dx = pShip->pos.x - pPlanet->pos.x;
	dy = pShip->pos.y - pPlanet->pos.y;
	dr = sqrt(pow(dx, 2) + pow(dy, 2));

	return dr;
	*/

	return sqrt(pow(pShip->pos.x - pPlanet->pos.x, 2) + pow(pShip->pos.y - pPlanet->pos.y, 2));
}

float Distance_goal(Ship *pShip, Goal *pGoal)
{
	return sqrt(pow(pShip->pos.x - pGoal->pos.x, 2) + pow(pShip->pos.y - pGoal->pos.y, 2));
}

// force universal gravitation
float Universalgravitation(Ship *pShip, Planet *pPlanet)
{
	//f = g(m1 * m2) / r^2
	return GRACOS * pShip->mass * pPlanet->mass / pow(Distance_planet(pShip, pPlanet),2);

}

//vector ball to planet by x
float Vectorx(Ship *pShip, Planet *pPlanet)
{
	return pPlanet->pos.x - pShip->pos.x;
}

//vector ball to planet by y
float Vectory(Ship *pShip, Planet *pPlanet)
{
	return pPlanet->pos.y - pShip->pos.y;
}

//normalize vector x ball to planet
float Normalx(Ship *pShip, Planet *pPlanet)
{
	return Vectorx(pShip, pPlanet) / Distance_planet(pShip, pPlanet);
}

//normalize vector y ball to planet
float Normaly(Ship *pShip, Planet *pPlanet)
{
	return Vectory(pShip, pPlanet) / Distance_planet(pShip, pPlanet);
}

//collision of scale x with planet
float Collision_planet_x(Ship *pShip, Planet *pPlanet)
{
	return (pShip->scale.x + pPlanet->scale.x) / 2;
}

//collision of scale y with planet
float Collision_planet_y(Ship *pShip, Planet *pPlanet)
{
	return (pShip->scale.y + pPlanet->scale.y) / 2;
}

//collision of scale with planet
float Collision_planet(Ship *pShip, Planet *pPlanet)
{
	return sqrt(pow(Collision_planet_x(pShip, pPlanet),2) + pow(Collision_planet_y(pShip, pPlanet), 2));
}

//collision of scale x with goal
float Collision_goal_x(Ship *pShip, Goal *pGoal)
{
	return (pShip->scale.x + pGoal->scale.x) / 2;
}

//collision of scale y with goal
float Collision_goal_y(Ship *pShip, Goal *pGoal)
{
	return (pShip->scale.y + pGoal->scale.y) / 2;
}

//collision of scale with goal
float Collision_goal(Ship *pShip, Goal *pGoal)
{
	return sqrt(pow(Collision_goal_x(pShip, pGoal), 2) + pow(Collision_goal_y(pShip, pGoal), 2));
}
//vector ball to planet by x
float Vectormarkx(Ship *pShip, Object *pMark)
{
	return pMark->pos.x - pShip->pos.x;
}

//vector ball to planet by y
float Vectormarky(Ship *pShip, Object *pMark)
{
	return pMark->pos.y - pShip->pos.y;
}

//angle of ball x for y
void After_Launch_Angle(Ship *pShip,WEVec2 *mouse)
{
	float vecx = mouse->x - pShip->pos.x;
	float vecy = mouse->y - pShip->pos.y;
	float crossproduct = cos(pShip->angle) * vecy - sin(pShip->angle) * vecx;
	if (crossproduct > 0)
		pShip->angle += 0.06f;
	else
		pShip->angle -= 0.06f;
}
void Before_Launch_Angle(Ship *pShip, Object *pMark)
{
	//Vectormarkx, Vectormarky
	float vecx = pMark->pos.x - pShip->pos.x;
	float vecy = pMark->pos.y - pShip->pos.y;
	pShip->angle = atan2(vecy, vecx);
}

//about asteroid
float Distance_asteroid(Ship *pShip, Asteroid *pAs)
{
	return sqrt(pow(pShip->pos.x - pAs->pos.x, 2) + pow(pShip->pos.y - pAs->pos.y, 2));
}
float Collision_asteroid_x(Ship *pShip, Asteroid *pAs)
{
	return (pShip->scale.x + pAs->scale.x) / 2;
}
float Collision_asteroid_y(Ship *pShip, Asteroid *pAs)
{
	return (pShip->scale.y + pAs->scale.y) / 2;
}
float Collision_asteroid(Ship *pShip, Asteroid *pAs)
{
	return sqrt(pow(Collision_asteroid_x(pShip, pAs), 2) + pow(Collision_asteroid_y(pShip, pAs), 2));
}


//about edge of planet
float Distance_planet_edge(Ship *pShip, Edge *pEdge)
{
	return sqrt(pow(pShip->pos.x - pEdge->pos.x, 2) + pow(pShip->pos.y - pEdge->pos.y, 2));
}
float Collision_planet_edge_x(Ship *pShip, Edge *pEdge)
{
	return (pShip->scale.x + pEdge->scale.x) / 2;
}
float Collision_planet_edge_y(Ship *pShip, Edge *pEdge)
{
	return (pShip->scale.y + pEdge->scale.y) / 2;
}
float Collision_planet_edge(Ship *pShip, Edge *pEdge)
{
	return sqrt(pow(Collision_planet_edge_x(pShip, pEdge), 2) + pow(Collision_planet_edge_y(pShip, pEdge), 2));
}

//about fuel
float Distance_fuel(Ship *pShip, Object *pFuel)
{
	return sqrt(pow(pShip->pos.x - pFuel->pos.x, 2) + pow(pShip->pos.y - pFuel->pos.y, 2));
}
float Collision_fuel_x(Ship *pShip, Object *pFuel)
{
	return (pShip->scale.x + pFuel->scale.x) / 2;
}
float Collision_fuel_y(Ship *pShip, Object *pFuel)
{
	return (pShip->scale.y + pFuel->scale.y) / 2;
}
float Collision_fuel(Ship *pShip, Object *pFuel)
{
	return sqrt(pow(Collision_fuel_x(pShip, pFuel), 2) + pow(Collision_fuel_y(pShip, pFuel), 2));
}
float DistanceMouseWithShip(WEVec2 mouse, Ship *pShip)
{
	return sqrt(pow(pShip->pos.x - mouse.x, 2) + pow(pShip->pos.y - mouse.y, 2));
}

float DistanceMouseWithShip(WEVec2 mouse, Asteroid *pAsteroid)
{
	return sqrt(pow(pAsteroid->pos.x - mouse.x, 2) + pow(pAsteroid->pos.y - mouse.y, 2));
}