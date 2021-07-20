/******************************************************************************
\file	CustomMode.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#pragma once
#ifndef CUSTOMMODE_H
#define CUSTOMMODE_H


void CustomModeLoad(void);
void CustomModeInit(void);
void CustomModeUpdate(float dt);
void CustomModeShutdown(void);
void CustomModeUnload(void);

class Slot {
public:
	static int s_slotID;
};

#endif