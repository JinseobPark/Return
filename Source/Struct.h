/******************************************************************************
\file   struct.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef STRUCT_H
#define STRUCT_H
#include "WEVec2.h"

enum ShipType
{
	SHIP_STANDBY,
	SHIP_PULL,
	SHIP_SHOOTED
};

enum ShipLife
{
	SHIP_LIVE,
	SHIP_CRASH
};

struct Ship
{
	WEVec2 pos;
	WEVec2 scale;
	WEVec2 vel;
	float power;
	float distance;
	float angle;
	float mass;
	float boostGauge;
	int texture;
	ShipType shiptype;
	ShipLife shiplife;
	bool angleAuto;
};

struct Button
{
	WEVec2 pos;
	WEVec2 scale;
	int texture;
};

struct Object
{
	WEVec2 pos;
	WEVec2 scale;
	WEVec2 vel;
	float angle;
	int texture;
};

struct Edge
{
	WEVec2 pos;
	WEVec2 scale;
	int texture;
};

struct Planet
{
	WEVec2 pos;
	WEVec2 scale;
	float gravity;
	float mass;
	int texture;
	bool pull;
	bool count;
	int life;
};

struct Asteroid
{
	WEVec2 pos;
	WEVec2 scale;
	WEVec2 vel;
	int texture;
	float rotate;
	bool count;
	bool pull;
	bool shoot;
};


struct Goal
{
	WEVec2 pos;
	WEVec2 scale;
	int texture;
};
#endif