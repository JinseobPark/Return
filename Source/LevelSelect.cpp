/******************************************************************************
\file	LevelSelect.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "data.h"
#include "LevelSelect.h"
#include "Message.h"
#include "ParticleManager.h"

namespace
{
	struct Initdata
	{
		float screenWidth;
		float screenHeight;
		float cameraheight;

		int storyb;
		int adventureb;
		int customplayb;
		int customeditb;

		int pstoryb;
		int padventureb;
		int pcustomplayb;
		int pcustomeditb;

		int expStory;
		int expAdventure;
		int expCustom;
		int expNone;
		int expTexture;

		int circleTexture;


		int backTexture;
		int backPTexture;

		Button backb;
		Button story;
		Button adventure;
		Button customplay;

	};

	/*Create a static variable for initdata so it can't be used in other files.*/
	Initdata initdata;

	ParticleManager *pPM;
	ReturnData returndata;
}
void LSLoad(void)
{
	initdata.storyb      = WEGraphics::LoadTexture("Textures\\Story.tga");
	initdata.adventureb  = WEGraphics::LoadTexture("Textures\\Adventure.tga");
	initdata.customplayb = WEGraphics::LoadTexture("Textures\\CustomPlay.tga");
	initdata.customeditb = WEGraphics::LoadTexture("Textures\\CustomEditor.tga");
	initdata.pstoryb     = WEGraphics::LoadTexture("Textures\\PStory.tga");
	initdata.padventureb = WEGraphics::LoadTexture("Textures\\PAdventure.tga");
	initdata.pcustomplayb = WEGraphics::LoadTexture("Textures\\PCustomPlay.tga");
	initdata.pcustomeditb = WEGraphics::LoadTexture("Textures\\PCustomEditor.tga");
	initdata.expStory = WEGraphics::LoadTexture("Textures\\exp_story.tga");
	initdata.expAdventure = WEGraphics::LoadTexture("Textures\\exp_adven.tga");
	initdata.expCustom = WEGraphics::LoadTexture("Textures\\exp_custom.tga");
	initdata.expNone = WEGraphics::LoadTexture("Textures\\SPblinder.tga");
	initdata.circleTexture = WEGraphics::LoadTexture("Textures/Circle.tga");
	initdata.backTexture = WEGraphics::LoadTexture("Textures\\BackIcon.tga");
	initdata.backPTexture = WEGraphics::LoadTexture("Textures\\BackIconP.tga");

	returndata.cameraZ = 350;
}

void LSInit(void)
{
	pPM = new ParticleManager();
	returndata.level = 0;
	returndata.screenWidth = (float)WEApplication::GetWidth();
	returndata.screenHeight = (float)WEApplication::GetHeight();

	Particle* pBG = pPM->GetBG();
	pPM->LoadBG(pBG);
	pPM->InitBG(pBG, initdata.circleTexture);
	initdata.expTexture = initdata.expNone;
	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);
	//View point
	WEGraphics::SetViewport(0, 0, (int)returndata.screenWidth, (int)returndata.screenHeight);
	
	initdata.story.texture = initdata.storyb;
	initdata.story.pos.x = 340;
	initdata.story.pos.y = 560.f;
	initdata.story.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.story.scale.y = MENU_BUTTON_HEIGHT / 1.5f;

	initdata.adventure.texture = initdata.adventureb;
	initdata.adventure.pos.x = 640;
	initdata.adventure.pos.y = 560.f;
	initdata.adventure.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.adventure.scale.y = MENU_BUTTON_HEIGHT / 1.5f;
	
	initdata.customplay.texture = initdata.customplayb;
	initdata.customplay.pos.x = 940;
	initdata.customplay.pos.y = 560.f;
	initdata.customplay.scale.x = MENU_BUTTON_WIDTH / 1.5f;
	initdata.customplay.scale.y = 2 * MENU_BUTTON_HEIGHT / 1.5f;


	initdata.backb.texture = initdata.backTexture;
	initdata.backb.scale.x = 100;
	initdata.backb.scale.y = 100;
	initdata.backb.pos.x = BUTTON_WIDTH / 2 + 50;
	initdata.backb.pos.y = returndata.screenHeight - BUTTON_HEIGHT / 2 - 10;

}

void LSUpdate(float dt)
{
	dt = 0;
	Particle* pBG = pPM->GetBG();

	WEMtx44 transform;

	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);


	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::SetNextState(DS_GAMEMENU);

		WEVec2 click;
		WEInput::GetMouse(click);
		if (WEIntersection::PointRect(click, initdata.story.pos,
			initdata.story.scale.x, initdata.story.scale.y))
		{
			initdata.expTexture = initdata.expStory;
			initdata.story.texture = initdata.pstoryb;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				WEStateManager::SetNextState(DS_STROYINTRO);
			}
		}
		else
		{
			initdata.story.texture = initdata.storyb;
		}

		if (WEIntersection::PointRect(click, initdata.adventure.pos,
			initdata.adventure.scale.x, initdata.adventure.scale.y))
		{
			initdata.expTexture = initdata.expAdventure;
			initdata.adventure.texture = initdata.padventureb;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				WEStateManager::SetNextState(DS_ADVENTURE);
			}
		}
		else 
		{
			initdata.adventure.texture = initdata.adventureb;
		}

		if (WEIntersection::PointRect(click, initdata.customplay.pos,
			initdata.customplay.scale.x, initdata.customplay.scale.y))
		{
			initdata.expTexture = initdata.expCustom;
			initdata.customplay.texture = initdata.pcustomplayb;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				WEStateManager::SetNextState(DS_CUSTOMINTRO);
			}
		}
		else
		{
			initdata.customplay.texture = initdata.customplayb;
		}


		if (WEIntersection::PointRect(click, initdata.story.pos,
			initdata.story.scale.x, initdata.story.scale.y) ||
			WEIntersection::PointRect(click, initdata.adventure.pos,
				initdata.adventure.scale.x, initdata.adventure.scale.y) ||
			WEIntersection::PointRect(click, initdata.customplay.pos,
				initdata.customplay.scale.x, initdata.customplay.scale.y))
		{
		}
		else
			initdata.expTexture = initdata.expNone;



		if (WEIntersection::PointRect(click, initdata.backb.pos,
			initdata.backb.scale.x, initdata.backb.scale.y))
		{
			initdata.backb.texture = initdata.backPTexture;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				WEStateManager::SetNextState(DS_GAMEMENU);
			}
		}
		else initdata.backb.texture = initdata.backTexture;

	//Camera position
	WEGraphics::SetCamera(returndata.screenWidth / 2, returndata.screenHeight / 2, returndata.cameraZ, 0);
	//start draw
	WEGraphics::StartDraw();

	pPM->DrawBG(pBG);
	//perspective to z order
	WEGraphics::SetToPerspective();

	/*Set the image to draw*/
	WEGraphics::SetTexture(initdata.story.texture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	//Once we have set the texture we can draw it with a transform
	WEMtx44::MakeTransform(transform,
		initdata.story.scale.x,
		initdata.story.scale.y,
		0,
		initdata.story.pos.x,
		initdata.story.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.adventure.texture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	//Once we have set the texture we can draw it with a transform
	WEMtx44::MakeTransform(transform,
		initdata.adventure.scale.x,
		initdata.adventure.scale.y,
		0,
		initdata.adventure.pos.x,
		initdata.adventure.pos.y,
		0);
	WEGraphics::Draw(transform);

	
	WEGraphics::SetTexture(initdata.customplay.texture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	//Once we have set the texture we can draw it with a transform
	WEMtx44::MakeTransform(transform,
		initdata.customplay.scale.x,
		initdata.customplay.scale.y,
		0,
		initdata.customplay.pos.x,
		initdata.customplay.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.backb.texture);
	WEMtx44::MakeTransform(transform,
		initdata.backb.scale.x,
		initdata.backb.scale.y,
		0,
		initdata.backb.pos.x,
		initdata.backb.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.expTexture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	//Once we have set the texture we can draw it with a transform
	WEMtx44::MakeTransform(transform,
		1024,
		128,
		0,
		returndata.screenWidth / 2,
		returndata.screenHeight / 2,
		0);
	WEGraphics::Draw(transform);
	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();
}

void LSShutdown(void)
{
}

void LSUnload(void)
{
	WEGraphics::UnloadTexture(initdata.storyb);
	WEGraphics::UnloadTexture(initdata.adventureb);
	WEGraphics::UnloadTexture(initdata.customplayb);
	WEGraphics::UnloadTexture(initdata.customeditb);
	WEGraphics::UnloadTexture(initdata.pstoryb);
	WEGraphics::UnloadTexture(initdata.padventureb);
	WEGraphics::UnloadTexture(initdata.pcustomplayb);
	WEGraphics::UnloadTexture(initdata.pcustomeditb);
	WEGraphics::UnloadTexture(initdata.expStory);
	WEGraphics::UnloadTexture(initdata.expAdventure);
	WEGraphics::UnloadTexture(initdata.expCustom);
	WEGraphics::UnloadTexture(initdata.expNone);
	WEGraphics::UnloadTexture(initdata.circleTexture);
	WEGraphics::UnloadTexture(initdata.backTexture);
	WEGraphics::UnloadTexture(initdata.backPTexture);
}