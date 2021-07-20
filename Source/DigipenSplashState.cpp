/******************************************************************************
\file	DigipenSplashState.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/

#include "DigipenSplashState.h"
#include "data.h"

#define LOGO_WIDTH 1024
#define LOGO_LENGTH 256

#define BLINDER_NUMBER 128
#define BULLETS_NUMBER 128

/*Make a struct for my shared state data*/
namespace
{
	struct InitData
	{
		int digiLogo;
		int bulletTexture;
		int blinderTexture;


		float textcoord;
		float timerCount;

		Object bullets[BULLETS_NUMBER];
		Object blinder[BLINDER_NUMBER];
	};

	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	/*The max time to be in this state*/
	const float SPLASH_MAX_TIME = 2.0f; 

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
void SplashStateLoad(void)
{

	/*Load the only texture we need for this state*/
	data.digiLogo  = WEGraphics::LoadTexture("Textures\\DigipenLogoSP.tga");
	data.bulletTexture = WEGraphics::LoadTexture("Textures\\SplashBuillet.tga");
	data.blinderTexture = WEGraphics::LoadTexture("Textures\\SPblinder.tga");

	WEGraphics::SetTextureColor(255, 255, 255, 255);
	SoundManager::sharedManager()->loading();
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void SplashStateInit(void)
{
	WEGraphics::SetCamera(windowWidth / 2, windowHeight / 2, 350, 0);
	SoundManager::sharedManager()->play(SPLASH);
	/*Reset the timer for this state*/
	data.timerCount = 0.0f;
	data.textcoord = 0.0f;


	for (int i = 0; i < BULLETS_NUMBER; ++i)
	{
		data.bullets[i].texture = data.bulletTexture;
		data.bullets[i].pos.x = -720;
		data.bullets[i].pos.y = windowHeight / 2 - LOGO_LENGTH / 2 + 2 * i;
		data.bullets[i].scale.x = 8;
		data.bullets[i].scale.y = 2;
		data.bullets[i].vel.x = WERandom::GetFloat(10, 25);
		data.bullets[i].vel.y = 0;
		data.bullets[i].angle = 0;
	}

	for (int i = 0; i < BLINDER_NUMBER; ++i)
	{
		data.blinder[i].texture = data.blinderTexture;
		data.blinder[i].pos.x = windowWidth / 2;
		data.blinder[i].pos.y = windowHeight / 2 - LOGO_LENGTH / 2 + 2 * i;
		data.blinder[i].scale.x = LOGO_WIDTH;
		data.blinder[i].scale.y = 2;
		data.blinder[i].vel.x = data.bullets[i].vel.x;
		data.blinder[i].vel.y = 0;
		data.blinder[i].angle = 0;
	}
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void SplashStateUpdate(float dt)
{
	SoundManager::sharedManager()->update();
	WEMtx44 transform;

	//timer
	data.timerCount += dt;

	//time over  or press space bar
	if (data.timerCount > SPLASH_MAX_TIME)
	{
		WEStateManager::SetNextState(DS_TEAMLOGO);
	}
	if (WEInput::IsTriggered(WE_R))
	{
		WEStateManager::Restart();
	}

	for (int i = 0; i < BLINDER_NUMBER; ++i)
	{
		if(data.bullets[i].pos.x > data.blinder[i].pos.x - LOGO_WIDTH/2)
		data.blinder[i].pos.x += data.blinder[i].vel.x;
	}

	for (int i = 0; i < BULLETS_NUMBER; ++i)
	{
		data.bullets[i].pos.x += data.bullets[i].vel.x;
	}
	//Set position scale and rotation of what I want to draw


	/*This must be called before any drawing in the frame.*/
	WEGraphics::StartDraw();


	WEGraphics::SetToPerspective();

	/*Set the image to draw*/
	WEGraphics::SetTexture(data.digiLogo);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		LOGO_WIDTH,
		LOGO_LENGTH,
		0.0f,
		windowWidth / 2,
		windowHeight / 2,
		0.0);
	//Once we have set the texture we can draw it with a transform
	WEGraphics::Draw(transform);

	for (int i = 0; i < BLINDER_NUMBER; ++i)
	{

		WEGraphics::SetTexture(data.blinderTexture);
		WEMtx44::MakeTransform(transform,
			data.blinder[i].scale.x,
			data.blinder[i].scale.y,
			0,
			data.blinder[i].pos.x,
			data.blinder[i].pos.y,
			0);
		WEGraphics::Draw(transform);
	}

	for (int i = 0; i < BULLETS_NUMBER; ++i)
	{
		WEGraphics::SetTexture(data.bulletTexture);
		WEMtx44::MakeTransform(transform,
			data.bullets[i].scale.x,
			data.bullets[i].scale.y,
			0,
			data.bullets[i].pos.x,
			data.bullets[i].pos.y,
			0);
		WEGraphics::Draw(transform);
	}
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
void SplashStateShutdown(void)
{
	data.timerCount = 0.0f;
	data.textcoord = 0.0f;
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void SplashStateUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(data.digiLogo);
	WEGraphics::UnloadTexture(data.bulletTexture);
	WEGraphics::UnloadTexture(data.blinderTexture);
}

