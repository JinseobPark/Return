/******************************************************************************
\file	Credit.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
 
#include "Credit.h"
#include "Data.h"
#include "ParticleManager.h"


namespace
{
	struct InitData
	{
		int credit;
		int creditors;
		int logoText;

		int circleTexture;

		int backTexture;
		int backPTexture;

		Button backb;
	};

	InitData initdata;
	ParticleManager *pPM;

	ReturnData returndata;
}
void CreditLoad(void)
{
	initdata.credit = WEGraphics::LoadTexture("Textures\\Credit.tga");
	initdata.creditors = WEGraphics::LoadTexture("Textures\\Creditors.tga");
	initdata.logoText = WEGraphics::LoadTexture("Textures\\CreditLogo.tga");
	initdata.circleTexture = WEGraphics::LoadTexture("Textures/Circle.tga");
	initdata.backTexture = WEGraphics::LoadTexture("Textures\\BackIcon.tga");
	initdata.backPTexture = WEGraphics::LoadTexture("Textures\\BackIconP.tga");
}

void CreditInit(void)
{
	pPM = new ParticleManager();
	SoundManager::sharedManager()->play(CLICK);
	returndata.screenWidth = (float)WEApplication::GetWidth();
	returndata.screenHeight = (float)WEApplication::GetHeight();

	Particle* pBG = pPM->GetBG();
	pPM->LoadBG(pBG);
	pPM->InitBG(pBG, initdata.circleTexture);
	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);
	//View point
	WEGraphics::SetViewport(0, 0, (int)returndata.screenWidth, (int)returndata.screenHeight);


	initdata.backb.texture = initdata.backTexture;
	initdata.backb.scale.x = 100;
	initdata.backb.scale.y = 100;
	initdata.backb.pos.x = BUTTON_WIDTH / 2 + 50;
	initdata.backb.pos.y = returndata.screenHeight - BUTTON_HEIGHT / 2 - 10;
}

void CreditUpdate(float)
{

	Particle* pBG = pPM->GetBG();
	WEMtx44 transform;

	WEVec2 click;
	WEInput::GetMouse(click);
	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);

	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::SetNextState(DS_GAMEMENU);

	if (WEInput::IsAnyTriggered())
	{
		SoundManager::sharedManager()->play(CLICK);
			WEStateManager::SetNextState(DS_GAMEMENU);
	}


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

	WEMtx44::MakeTransform(transform,
		256,
		64,
		0.0f,
		returndata.screenWidth / 2,
		returndata.screenHeight / 2,
		0.0);

	WEGraphics::SetCamera(returndata.screenWidth / 2, returndata.screenHeight / 2, 350, 0);
	//start draw
	WEGraphics::StartDraw();

	//perspective to z order
	WEGraphics::SetToPerspective();

	pPM->DrawBG(pBG);

	WEGraphics::SetTexture(initdata.logoText);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		500,
		200,
		0.0f,
		1050,
		100,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.credit);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		MENU_BUTTON_WIDTH,
		MENU_BUTTON_HEIGHT,
		0.0f,
		640,
		650,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.creditors);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		1024,
		512,
		0.0f,
		640,
		320,
		0.0f);
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
	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();
}

void CreditShutdown(void)
{
}

void CreditUnload(void)
{
	WEGraphics::UnloadTexture(initdata.credit);
	WEGraphics::UnloadTexture(initdata.creditors);
	WEGraphics::UnloadTexture(initdata.logoText);
	WEGraphics::UnloadTexture(initdata.circleTexture);
	WEGraphics::UnloadTexture(initdata.backTexture);
	WEGraphics::UnloadTexture(initdata.backPTexture);
}
