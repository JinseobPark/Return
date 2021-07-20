/******************************************************************************
\file	Option.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
 
#include "Option.h"
#include "Data.h"
#include "ParticleManager.h"

namespace
{
	struct InitData
	{
		int option;
		int fwtext;
		int shipTexture;
		int circleTexture;

		int boosterText;
		int explosionText;
		int rightText;
		int leftText;
		int rightPText;
		int leftPText;
		int backTexture;
		int backPTexture;

		Button backb;

		Button bUP;
		Button bDOWN;
		Button bRIGHT;
		Button bLEFT;
	};

	/*Create a static variable for data so it can't be used in other files.*/
	InitData initdata;
	ParticleManager *pPM;
	ReturnData returndata;
	float explode_timer;
}
void OptionLoad(void)
{
	initdata.option = WEGraphics::LoadTexture("Textures\\Option.tga");
	initdata.fwtext = WEGraphics::LoadTexture("Textures\\FullWindow.tga");
	initdata.shipTexture = WEGraphics::LoadTexture("Textures/spaceship4.tga");
	initdata.circleTexture = WEGraphics::LoadTexture("Textures/Circle.tga");
	initdata.boosterText = WEGraphics::LoadTexture("Textures\\BoosterOption.tga");
	initdata.explosionText = WEGraphics::LoadTexture("Textures\\ExplosionOption.tga");
	initdata.rightText   = WEGraphics::LoadTexture("Textures\\RightTexture.tga");
	initdata.leftText    = WEGraphics::LoadTexture("Textures\\LeftTexture.tga");
	initdata.rightPText  = WEGraphics::LoadTexture("Textures\\RightTextureT.tga");
	initdata.leftPText   = WEGraphics::LoadTexture("Textures\\LeftTextureT.tga");
	initdata.backTexture = WEGraphics::LoadTexture("Textures\\BackIcon.tga");
	initdata.backPTexture = WEGraphics::LoadTexture("Textures\\BackIconP.tga");
}

void OptionInit(void)
{
	pPM = new ParticleManager();
	Particle* pCrash = pPM->GetExplode();
	Particle* pBoost = pPM->GetBoost();
	Particle* pBG = pPM->GetBG();
	pPM->LoadBG(pBG);
	pPM->InitBG(pBG, initdata.circleTexture);
	pPM->LoadBoosting(pBoost);
	pPM->LoadCrashing(pCrash);
	SoundManager::sharedManager()->play(CLICK);
	returndata.screenWidth = (float)WEApplication::GetWidth();
	returndata.screenHeight = (float)WEApplication::GetHeight();

	explode_timer = 1;
	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);
	//View point
	WEGraphics::SetViewport(0, 0, (int)returndata.screenWidth, (int)returndata.screenHeight);


	initdata.bUP.texture = initdata.rightText;
	initdata.bUP.pos.x = 860;
	initdata.bUP.pos.y = 300;
	initdata.bUP.scale.x = MENU_BUTTON_WIDTH / 2.f;
	initdata.bUP.scale.y = MENU_BUTTON_HEIGHT / 2.f;

	initdata.bDOWN.texture = initdata.leftText;
	initdata.bDOWN.pos.x = 550;
	initdata.bDOWN.pos.y = 300;
	initdata.bDOWN.scale.x = MENU_BUTTON_WIDTH / 2.f;
	initdata.bDOWN.scale.y = MENU_BUTTON_HEIGHT / 2.f;

	initdata.bRIGHT.texture = initdata.rightText;
	initdata.bRIGHT.pos.x = 860;
	initdata.bRIGHT.pos.y = 150;
	initdata.bRIGHT.scale.x = MENU_BUTTON_WIDTH  / 2.0f;
	initdata.bRIGHT.scale.y = MENU_BUTTON_HEIGHT / 2.0f;

	initdata.bLEFT.texture = initdata.leftText;
	initdata.bLEFT.pos.x = 550;
	initdata.bLEFT.pos.y = 150;
	initdata.bLEFT.scale.x = MENU_BUTTON_WIDTH  / 2.0f;
	initdata.bLEFT.scale.y = MENU_BUTTON_HEIGHT / 2.0f;



	initdata.backb.texture = initdata.backTexture;
	initdata.backb.scale.x = 100;
	initdata.backb.scale.y = 100;
	initdata.backb.pos.x = BUTTON_WIDTH / 2 + 50;
	initdata.backb.pos.y = returndata.screenHeight - BUTTON_HEIGHT / 2 - 10;
}

void OptionUpdate(float dt)
{
	Particle* pCrash = pPM->GetExplode();
	Particle* pBooster = pPM->GetBoost();
	Particle* pBG = pPM->GetBG();

	pPM->OptionInitBoost(pBooster);

	explode_timer -= dt;
	if (explode_timer < 0)
	{
		pPM->OptionInitCrasing(pCrash);
		explode_timer = 1;
	}
	pPM->OptionPooozicBoost(pBooster, dt);
	pPM->OptionUpdateCrashing(pCrash, dt);


	WEMtx44 transform;
	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);

	if (WEInput::IsTriggered(WE_ESCAPE))
	{
		SoundManager::sharedManager()->play(CLICK);
		WEStateManager::SetNextState(DS_GAMEMENU);
	}

	if (WEInput::IsTriggered(WE_SPACE))
	{
		returndata.isFullScreen = !returndata.isFullScreen;
		WEApplication::SetFullScreen(returndata.isFullScreen);
	}
	if (WEInput::IsTriggered(WE_ARROW_LEFT) && ParticleManager::particle_option_booster > 1)
		ParticleManager::particle_option_booster -= 1;
	if (WEInput::IsTriggered(WE_ARROW_RIGHT) && ParticleManager::particle_option_booster < 7)
		ParticleManager::particle_option_booster += 1;

	if (WEInput::IsTriggered(WE_ARROW_DOWN) && ParticleManager::particle_option_explode > 1)
		ParticleManager::particle_option_explode -= 1;
	if (WEInput::IsTriggered(WE_ARROW_UP) && ParticleManager::particle_option_explode < 5)
		ParticleManager::particle_option_explode += 1;


	WEVec2 click;
	WEInput::GetMouse(click);
	if (WEIntersection::PointRect(click, initdata.bUP.pos,
		initdata.bUP.scale.x, initdata.bUP.scale.y))
	{
		initdata.bUP.texture = initdata.rightPText;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (ParticleManager::particle_option_explode < 5)
				ParticleManager::particle_option_explode += 1;
		}
	}
	else initdata.bUP.texture = initdata.rightText;

	if (WEIntersection::PointRect(click, initdata.bDOWN.pos,
		initdata.bDOWN.scale.x, initdata.bDOWN.scale.y))
	{
		initdata.bDOWN.texture = initdata.leftPText;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (ParticleManager::particle_option_explode > 1)
				ParticleManager::particle_option_explode -= 1;
		}
	}
	else initdata.bDOWN.texture = initdata.leftText;


	if (WEIntersection::PointRect(click, initdata.bRIGHT.pos,
		initdata.bRIGHT.scale.x, initdata.bRIGHT.scale.y))
	{
		initdata.bRIGHT.texture = initdata.rightPText;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (ParticleManager::particle_option_booster < 7)
				ParticleManager::particle_option_booster += 1;
		}
	}
	else initdata.bRIGHT.texture = initdata.rightText;


	if (WEIntersection::PointRect(click, initdata.bLEFT.pos,
		initdata.bLEFT.scale.x, initdata.bLEFT.scale.y))
	{
		initdata.bLEFT.texture = initdata.leftPText;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (ParticleManager::particle_option_booster > 1)
				ParticleManager::particle_option_booster -= 1;
		}
	}
	else initdata.bLEFT.texture = initdata.leftText;

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

	pPM->DrawBG(pBG);
	//perspective to z order
	WEGraphics::SetToPerspective();

	pPM->OptionDrawBoost(pBooster, initdata.circleTexture);
	pPM->OptionDrawCrasing(pCrash, initdata.circleTexture);
	/*Set the image to draw*/
	WEGraphics::SetTexture(initdata.option);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	//Once we have set the texture we can draw it with a transform
	WEMtx44::MakeTransform(transform,
		MENU_BUTTON_WIDTH,
		MENU_BUTTON_HEIGHT,
		0.0f,
		640,
		650,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.fwtext);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		512,
		32,
		0.0f,
		640,
		500,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.shipTexture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		60,
		30,
		0.0f,
		760,
		150,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.shipTexture);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		60,
		30,
		0.0f,
		710,
		300,
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

	WEGraphics::SetTexture(initdata.boosterText);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		256,
		40,
		0.0f,
		300,
		150,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.explosionText);
	WEGraphics::SetTextureColor(0xFFFFFFFF);
	WEMtx44::MakeTransform(transform,
		256,
		40,
		0.0f,
		300,
		300,
		0.0f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.bUP.texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		initdata.bUP.scale.x,
		initdata.bUP.scale.y,
		0,
		initdata.bUP.pos.x,
		initdata.bUP.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.bDOWN.texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		initdata.bDOWN.scale.x,
		initdata.bDOWN.scale.y,
		0,
		initdata.bDOWN.pos.x,
		initdata.bDOWN.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.bRIGHT.texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		initdata.bRIGHT.scale.x,
		initdata.bRIGHT.scale.y,
		0,
		initdata.bRIGHT.pos.x,
		initdata.bRIGHT.pos.y,
		0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(initdata.bLEFT.texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		initdata.bLEFT.scale.x,
		initdata.bLEFT.scale.y,
		0,
		initdata.bLEFT.pos.x,
		initdata.bLEFT.pos.y,
		0);
	WEGraphics::Draw(transform);
	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();

	WEGraphics::SetTextureColor(255, 255, 255, 255);
}

void OptionShutdown(void)
{
}

void OptionUnload(void)
{
	WEGraphics::UnloadTexture(initdata.option);
	WEGraphics::UnloadTexture(initdata.fwtext);
	WEGraphics::UnloadTexture(initdata.circleTexture);
	WEGraphics::UnloadTexture(initdata.shipTexture);
	WEGraphics::UnloadTexture(initdata.boosterText);
	WEGraphics::UnloadTexture(initdata.explosionText);
	WEGraphics::UnloadTexture(initdata.rightText);
	WEGraphics::UnloadTexture(initdata.leftText);
	WEGraphics::UnloadTexture(initdata.rightPText);
	WEGraphics::UnloadTexture(initdata.leftPText);
	WEGraphics::UnloadTexture(initdata.backTexture);
	WEGraphics::UnloadTexture(initdata.backPTexture);
}
