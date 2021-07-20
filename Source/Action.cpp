/******************************************************************************
\file	Action.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Action.h"
#include "ReturnStates.h"
#include "WEStateManager.h"


void Replay(void)
{
	WEStateManager::Restart();
}
void Go_Menu(void)
{
	WEStateManager::SetNextState(DS_GAMEMENU);
}
void Quit(void)
{
	WEStateManager::Quit();
}
