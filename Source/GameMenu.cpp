/******************************************************************************
\file	GameMenu.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/


#include "Data.h"
#include "GameMenu.h"

#define WE_ANI_TIMER 0.5f

namespace
{
	struct InitData
	{
		float screenWidth;
		float screenHeight;
		float cameraheight;
		int mainSpace;
		int playerSprites;

		int play;
		int option;
		int credit;
		int quit;

		int pplay;
		int poption;
		int pcredit;
		int pquit;

		Button playb;
		Button optionb;
		Button creditb;
		Button quitb;
		float textcoord;
		float timerCount;
		float timerC;
	};

	/*Create a static variable for data so it can't be used in other files.*/
	InitData initdata;
	ReturnData returndata;
}

/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void MenuLoad(void)
{
	/*Load the only texture we need for this state*/
	initdata.mainSpace = WEGraphics::LoadTexture("Textures\\mainSpace.tga");
	initdata.playerSprites = WEGraphics::LoadTexture("Textures\\playerSprites.tga");;
	initdata.play = WEGraphics::LoadTexture("Textures\\Play.tga");
	initdata.option = WEGraphics::LoadTexture("Textures\\Option.tga");
	initdata.credit = WEGraphics::LoadTexture("Textures\\Credit.tga");
	initdata.quit = WEGraphics::LoadTexture("Textures\\Quit.tga");
	initdata.pplay = WEGraphics::LoadTexture("Textures\\PPlay.tga");
	initdata.poption = WEGraphics::LoadTexture("Textures\\POption.tga");
	initdata.pcredit = WEGraphics::LoadTexture("Textures\\PCredit.tga");
	initdata.pquit = WEGraphics::LoadTexture("Textures\\PQuit.tga");

	WEGraphics::SetTextureColor(255, 255, 255, 255);
	/*All drawing in this state is in screen space*/
	WEGraphics::SetToOrtho();
	returndata.game_mode = MENU;
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void MenuInit(void)
{
	WEDEBUG_PRINT("MENU INITIATED\n");
	SoundManager::sharedManager()->stop(MAINMENU);
	SoundManager::sharedManager()->stop(CLEAR);
	SoundManager::sharedManager()->stop(BG);
	SoundManager::sharedManager()->play(MAINMENU);
	returndata.screenWidth = (float)WEApplication::GetWidth();
	returndata.screenHeight = (float)WEApplication::GetHeight();
	returndata.cameraZ = 350;

	//View point
	WEGraphics::SetViewport(0, 0, (int)returndata.screenWidth, (int)returndata.screenHeight);

	/*Reset the timer for this state*/
	initdata.timerCount = 0.0f;
	initdata.textcoord = 0.0f;
	initdata.timerC = 1.0f;


	initdata.playb.texture = initdata.play;
	initdata.playb.pos.x = 1100;
	initdata.playb.pos.y = 300;
	initdata.playb.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.playb.scale.y = MENU_BUTTON_HEIGHT / 1.5f;

	initdata.optionb.texture = initdata.option;
	initdata.optionb.pos.x = 1100;
	initdata.optionb.pos.y = 236;
	initdata.optionb.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.optionb.scale.y = MENU_BUTTON_HEIGHT / 1.5f;

	initdata.creditb.texture = initdata.credit;
	initdata.creditb.pos.x = 1100;
	initdata.creditb.pos.y = 172;
	initdata.creditb.scale.x = MENU_BUTTON_WIDTH /1.5f;
	initdata.creditb.scale.y = MENU_BUTTON_HEIGHT / 1.5f;

	initdata.quitb.texture = initdata.quit;
	initdata.quitb.pos.x = 1100;
	initdata.quitb.pos.y = 108;
	initdata.quitb.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.quitb.scale.y = MENU_BUTTON_HEIGHT / 1.5f;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void MenuUpdate(float dt)
{
	SoundManager::sharedManager()->update();
	SoundManager::sharedManager()->stop(SPLASH);
	WEMtx44 transform;

	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	/*increment timer*/
	initdata.timerCount += dt;

	if (initdata.timerC < 255)
	{
		initdata.timerC += dt + WE_ANI_TIMER *5;
		if (initdata.timerC > 255)
		{
			initdata.timerC = 255;
		}
	}

	if (initdata.timerCount > WE_ANI_TIMER)
	{
		initdata.timerCount = 0.0f;
		initdata.textcoord += 0.25f; //0.0625
		WEMath::Wrap(initdata.textcoord, 0.0f, 1.0f);
	}

	/*Check for time, only be in this state for the
	set time*/
	WEVec2 click;
	WEInput::GetMouse(click);
	if (WEIntersection::PointRect(click, initdata.playb.pos,
		initdata.playb.scale.x, initdata.playb.scale.y))
	{
		initdata.playb.texture = initdata.pplay;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			WEStateManager::SetNextState(DS_LEVELSELECT);
		}
	}
	else initdata.playb.texture = initdata.play;

	if (WEIntersection::PointRect(click, initdata.optionb.pos,
		initdata.optionb.scale.x, initdata.optionb.scale.y))
	{
		initdata.optionb.texture = initdata.poption;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			WEStateManager::SetNextState(DS_OPTION);
		}
	}
	else initdata.optionb.texture = initdata.option;


	if (WEIntersection::PointRect(click, initdata.creditb.pos,
			initdata.creditb.scale.x, initdata.creditb.scale.y))
	{
		initdata.creditb.texture = initdata.pcredit;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			WEStateManager::SetNextState(DS_CREDIT);
		}
	}
	else initdata.creditb.texture = initdata.credit;


	if (WEIntersection::PointRect(click, initdata.quitb.pos,
		initdata.quitb.scale.x, initdata.quitb.scale.y))
	{
		initdata.quitb.texture = initdata.pquit;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			WEStateManager::Quit();
		}
	}
	else initdata.quitb.texture = initdata.quit;


	if (WEInput::IsTriggered(WE_L) && WEInput::IsPressed(WE_CONTROL))
	{
		WEStateManager::SetNextState(DS_LEVELEDITOR);
	}

	WEGraphics::SetCamera(returndata.screenWidth / 2, returndata.screenHeight / 2, returndata.cameraZ, 0);

	/*This must be called before any drawing in the frame.*/
	WEGraphics::StartDraw();

	WEGraphics::SetToPerspective();

	/*Set the image to draw*/
	WEGraphics::SetTexture(initdata.mainSpace);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	/*Set position scale and rotation of what I want to draw*/
	WEMtx44::MakeTransform(transform,
		windowWidth,
		windowHeight,
		0.0f,
		windowWidth/2,
		windowHeight/2,
		0.0);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	//Once we have set the texture we can draw it with a transform
	WEGraphics::Draw(transform);

	/*Set the image to draw*/
	WEGraphics::SetTexture(initdata.playerSprites);
	WEGraphics::SetTextureCoords(0.25f, 1.0f, 0.0f, initdata.textcoord, 0.0f);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	/*Set position scale and rotation of what I want to draw*/
	WEMtx44::MakeTransform(transform,
		256,
		256,
		0.0f,
		windowWidth / 6,
		windowHeight / 6,
		0.0);
	//Once we have set the texture we can draw it with a transform
	WEGraphics::Draw(transform);
	

	WEGraphics::SetToOrtho();
	//button draw
	WEGraphics::SetTexture(initdata.playb.texture);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	WEMtx44::MakeTransform(transform,
		initdata.playb.scale.x,
		initdata.playb.scale.y,
		0,
		initdata.playb.pos.x,
		initdata.playb.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.optionb.texture);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	WEMtx44::MakeTransform(transform,
		initdata.optionb.scale.x,
		initdata.optionb.scale.y,
		0,
		initdata.optionb.pos.x,
		initdata.optionb.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.creditb.texture);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	WEMtx44::MakeTransform(transform,
		initdata.creditb.scale.x,
		initdata.creditb.scale.y,
		0,
		initdata.creditb.pos.x,
		initdata.creditb.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.quitb.texture);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)initdata.timerC);
	WEMtx44::MakeTransform(transform,
		initdata.quitb.scale.x,
		initdata.quitb.scale.y,
		0,
		initdata.quitb.pos.x,
		initdata.quitb.pos.y,
		0);
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
void MenuShutdown(void)
{
	
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void MenuUnload(void)
{
	//WEDEBUG_PRINT("MENU UNLOADED\n");
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(initdata.mainSpace);
	WEGraphics::UnloadTexture(initdata.playerSprites);
	WEGraphics::UnloadTexture(initdata.play);
	WEGraphics::UnloadTexture(initdata.option);
	WEGraphics::UnloadTexture(initdata.credit);
	WEGraphics::UnloadTexture(initdata.quit);
	WEGraphics::UnloadTexture(initdata.pplay);
	WEGraphics::UnloadTexture(initdata.poption);
	WEGraphics::UnloadTexture(initdata.pcredit);
	WEGraphics::UnloadTexture(initdata.pquit);
}
