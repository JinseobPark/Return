#ifndef PLANET_H
#define PLANET_H

#include "Data.h"

void InitPlanet(ReturnData &data);
void ActionPlanet(Ship* pShip, Planet* pPlanet, float dt);


void EditPlanet(Planet* pPlanet);

void DrawPlanet(Planet *pPlanet, ReturnData &data);

#endif