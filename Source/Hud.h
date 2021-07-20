/******************************************************************************
\file	Hud.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef HUD_H
#define HUD_H

#include "Data.h"

#define EDITOBJECTS_BUTTONS 3
#define EDITMOUSE_BUTTONS 2

//inits
void InitButtons(ReturnData &data);
void InitBoostHud(ReturnData &data);
//for edit mode
void InitEditMouse(ReturnData &data);
void InitEditObjects(ReturnData &data);
void InitEditSave(ReturnData &data);


//in update
void PressButton(Button *pButton,ReturnData &data);
void BoostGaugeUpdate(Button *pBoost, Ship *pShip);
void AD_BoostGaugeUpdate(Button *pBoost, Ship *pShip);
void PressEditMouse(Button *pButton, ReturnData &data);
void PressEditObjects(Button *pButton, ReturnData &data);
void PressEditSave(Button *pButton, ReturnData &data, float &timer, Planet *pPlanet, Asteroid *pAsteroid, Object *pFuel);


//Draws
void DrawHud(Button *pButton);
void DrawBoostHud(Button *pBoost);
void DrawLeveltext(ReturnData &data);
void DrawTrytext(ReturnData &data);
void DrawTryNumber(ReturnData &data);
void DrawLevelNumber(ReturnData &data);
void DrawPause(ReturnData &data);
void DrawHelpHud(ReturnData &data, float dt, float &timer, Ship *pShip);
void DrawBoostEdge(ReturnData &data);
void DrawEditOn(ReturnData &data);
void DrawBoostIcon(ReturnData &data);
void DrawLevelSel(int texture);
//for edit mode
void DrawEditMouse(Button *pButton);
void DrawEditObjects(Button *pButton);
void DrawEditSave(Button *pButton);
void DrawEditExplain(ReturnData &data);
void DrawIntroNumber(ReturnData &returndata);
#endif