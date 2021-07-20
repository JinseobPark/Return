/******************************************************************************
\file	Thank.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/

#include "Thank.h"

#include "WEApplication.h"
#include "WEDebugTools.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEInput.h"
#include "Data.h"

#include "ReturnStates.h"

#include <cstdio>
#define LOGO_WIDTH 1024
#define LOGO_LENGTH 512

struct T_Object
{
	WEVec2 pos;
	WEVec2 scale;
	int texture;
};
/*Make a struct for my shared state data*/
namespace
{
	struct InitData
	{
		float screenWidth;
		float screenHeight;
		int quest;
		int thank;
		T_Object present;
	};


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
void ThankStateLoad(void)
{

	/*Load the only texture we need for this state*/
	data.thank = WEGraphics::LoadTexture("Textures\\Playtest.tga");
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
void ThankStateInit(void)
{
	data.screenWidth = (float)WEApplication::GetWidth();
	data.screenHeight = (float)WEApplication::GetHeight();
	data.present.texture = data.thank;
	data.present.pos.x = data.screenWidth /2;
	data.present.pos.y = data.screenHeight /2;
	SoundManager::sharedManager()->stop(MAINMENU);
	SoundManager::sharedManager()->stop(CLEAR);
	SoundManager::sharedManager()->stop(BG);
	SoundManager::sharedManager()->play(CLEAR);
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void ThankStateUpdate(float dt)
{
	dt = 0;
	WEMtx44 transform;

	SoundManager::sharedManager()->update();

	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		WEStateManager::SetNextState(DS_GAMEMENU);
	}

	/*Set position scale and rotation of what I want to draw*/

	/*This must be called before any drawing in the frame.*/
	WEGraphics::StartDraw();


	//Once we have set the texture we can draw it with a transform
	WEGraphics::Draw(transform);
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEGraphics::SetTexture(data.present.texture);
	WEMtx44::MakeTransform(transform,
		LOGO_WIDTH,
		LOGO_LENGTH,
		0,
		data.present.pos.x,
		data.present.pos.y,
		0);
	WEGraphics::Draw(transform);

	//if(10 * (unsigned char)data.timerC > 255)

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
void ThankStateShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void ThankStateUnload(void)
{

	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(data.thank);
}
