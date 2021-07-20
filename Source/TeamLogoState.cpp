/******************************************************************************
\file	TeamLogoState.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/

#include "TeamLogoState.h"

#include "WEApplication.h"
#include "WEDebugTools.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEInput.h"

#include "ReturnStates.h"

#include <cstdio>

#define LOGO_WIDTH 256
#define LOGO_LENGTH 256

/*Make a struct for my shared state data*/
namespace
{
	struct InitData
	{
		int digiLogo;
		float textcoord;
		float timerC;
	};

	/*The max time to be in this state*/
	const float SPLASH_MAX_TIME = 18.9f;
	const int   ARRAY_SIZE = 20;

	/*Create a static variable for data so it can't be used in other files.*/
	InitData data;
}



/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void TeamLogoStateLoad(void)
{

	/*Load the only texture we need for this state*/
	data.digiLogo = WEGraphics::LoadTexture("Textures\\3r.tga");

	WEGraphics::SetTextureColor(255, 255, 255, 255);
	/*All drawing in this state is in screen space*/
	WEGraphics::SetToOrtho();
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void TeamLogoStateInit(void)
{
	/*Reset the timer for this state*/
	data.timerC = 0.f;
	data.textcoord = 0.0f;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void TeamLogoStateUpdate(float dt)
{
	WEMtx44 transform;
	char timeAsText[ARRAY_SIZE];
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	/*increment timer*/
	data.timerC += dt * 5;

	//Save my time as a string.
	sprintf_s(timeAsText, "%.2f", SPLASH_MAX_TIME - data.timerC);

	/*Check for time, only be in this state for the
	set time*/
	if (data.timerC > SPLASH_MAX_TIME || WEInput::IsTriggered(WE_SPACE))
		WEStateManager::SetNextState(DS_GAMEMENU);

	/*Set position scale and rotation of what I want to draw*/
	WEMtx44::MakeTransform(transform,
		LOGO_WIDTH,
		LOGO_LENGTH,
		0.0f,
		windowWidth / 2,
		windowHeight / 2,
		0.0);

	/*This must be called before any drawing in the frame.*/
	WEGraphics::StartDraw();

	/*Set the image to draw*/
	WEGraphics::SetTexture(data.digiLogo);
	WEGraphics::SetTextureColor(255, 255, 255, 15 * (unsigned char)data.timerC);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, data.textcoord, 0.0f);
	//Once we have set the texture we can draw it with a transform
	WEGraphics::Draw(transform);


	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void TeamLogoStateShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void TeamLogoStateUnload(void)
{

	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(data.digiLogo);
}
