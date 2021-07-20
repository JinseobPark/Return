/******************************************************************************
\file	Environment.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Data.h"

void Camera_Z(ReturnData &data);
void Camera_position(Ship *pShip, ReturnData data, float dt);
void KeyboardAct(ReturnData &data);
void AD_Camera_position(Ship *pShip, ReturnData data);
#endif