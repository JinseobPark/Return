/******************************************************************************
\file	Planet.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef PLANET_H
#define PLANET_H

#include "Data.h"
#include "FileIO.h"

void InitPlanet(ReturnData &data);
void InitPlanetEdge(ReturnData &data); 
void AD_InitPlanet(ReturnData &data);
void CT_InitPlanet(ReturnData &data);
void ActionPlanet(Ship* pShip, Planet* pPlanet, float dt);
void changePlanetTexture(Planet *pPlanet, ReturnData &data, float &time);

void EditPlanetT(Planet* pPlanet , ObjectManager* pOM);

void PlanetEdgePosition(Edge *pEdge, Planet *pPlanet, ReturnData &data);
void DrawPlanet(Planet *pPlanet, ReturnData &data);
void DrawPlanetEdge(Edge *pEdge, ReturnData &data);
void EditPlanetSize(Planet* pPlanet, ObjectManager* pOM);
#endif