/******************************************************************************
\file	Adventure.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Adventure.h"
#include "Data.h"
#include "Hud.h"
#include "Planet.h"
#include "Objects.h"
#include "SpaceShip.h"
#include "Environment.h"
#include "ParticleManager.h"

namespace
{
	ReturnData data;
	ParticleManager *pPM;
	float time_planet;
}


//Level set on planet, asteroid
void AD_LevelManager(void)
{
	data.max_planets = 20;
	data.max_asteroid = 100;
	data.max_ship = 1;
	data.max_fuel = 20;
}

void AdventureLoad(void)  //take image files
{

	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEDEBUG_PRINT("adventure loaded\n");
	data.TextureData.markTexture      = WEGraphics::LoadTexture("Textures/Mark.tga");
	data.TextureData.shipTexture      = WEGraphics::LoadTexture("Textures/spaceship4.tga");
	data.TextureData.quitTexture      = WEGraphics::LoadTexture("Textures/Quit.tga");
	data.TextureData.planetTexture    = WEGraphics::LoadTexture("Textures/samplePlanet2.tga");
	data.TextureData.goalTexture      = WEGraphics::LoadTexture("Textures/Goal.tga");
	data.TextureData.replayTexture    = WEGraphics::LoadTexture("Textures/Replay.tga");
	data.TextureData.menuTexture      = WEGraphics::LoadTexture("Textures/Menu.tga");
	data.TextureData.launchTexture    = WEGraphics::LoadTexture("Textures/LaunchHUD.tga");
	data.TextureData.asteroidTexture  = WEGraphics::LoadTexture("Textures/Asteroid.tga");
	data.TextureData.edgeTexture      = WEGraphics::LoadTexture("Textures/PlanetEdge.tga");
	data.TextureData.boostTexture     = WEGraphics::LoadTexture("Textures/BoostGauge.tga");
	data.TextureData.DragTheSpaceship = WEGraphics::LoadTexture("Textures/DragTheSpaceship.tga");
	data.TextureData.BoosterText	  = WEGraphics::LoadTexture("Textures/BoosterText.tga");
	data.TextureData.RotationText	  = WEGraphics::LoadTexture("Textures/Rotation.tga");
	data.TextureData.ZoomText         = WEGraphics::LoadTexture("Textures/Zoom.tga");
	data.TextureData.RestartText      = WEGraphics::LoadTexture("Textures/RestartText.tga");
	data.TextureData.circleTexture    = WEGraphics::LoadTexture("Textures/Circle.tga");
	data.TextureData.traceTexture     = WEGraphics::LoadTexture("Textures/TraceTexture.tga");
	data.TextureData.preplay          = WEGraphics::LoadTexture("Textures/Preplay.tga");
	data.TextureData.pmenu            = WEGraphics::LoadTexture("Textures/PMenu.tga");
	data.TextureData.pausetext        = WEGraphics::LoadTexture("Textures/Pause.tga");
	data.TextureData.BoostEdgeTexture = WEGraphics::LoadTexture("Textures/BoosterEdge.tga");
	data.TextureData.EggWaitTexture = WEGraphics::LoadTexture("Textures/EggWait.tga");
	data.TextureData.EggPasicTexture = WEGraphics::LoadTexture("Textures/EggPasic.tga");
	data.TextureData.EggSleepTexture = WEGraphics::LoadTexture("Textures/EggSleep.tga");
	data.TextureData.EggWakeUpTexture = WEGraphics::LoadTexture("Textures/EggWakeup.tga");
	data.TextureData.FuelTexture = WEGraphics::LoadTexture("Textures/Fuel.tga");
	data.cameraZ = 250;
	data.level = 0;
	SoundManager::sharedManager()->play(START);
	SoundManager::sharedManager()->play(BG);
	SoundManager::sharedManager()->stop(MAINMENU);
	SoundManager::sharedManager()->stop(SPLASH);
	data.life_count = 1;
	 time_planet = 1;
	data.boostfire = false;

	data.editmode = false;
	data.game_mode = ADVENTURE;
}


void AdventureInit(void)
{ 
	WEDEBUG_PRINT("adventure INITIATED\n");
	AD_LevelManager();
	//create objects
	data.pOM = new ObjectManager(data.max_ship, data.max_planets, data.max_asteroid, data.max_fuel);
	pPM = new ParticleManager();
	Particle* pBG = pPM->GetBG();	
	Particle* pCrash = pPM->GetExplode();
	Particle* pBoost = pPM->GetBoost();
	Particle* pByebye = pPM->GetByebye();
	pPM->LoadBoosting(pBoost);
	pPM->LoadCrashing(pCrash);
	pPM->LoadBG(pBG);
	pPM->LoadByebye(pByebye);

	data.screenWidth = (float)WEApplication::GetWidth();
	data.screenHeight = (float)WEApplication::GetHeight();
	data.camera_time = 0;
	//View point
	WEGraphics::SetViewport(0, 0, (int)data.screenWidth, (int)data.screenHeight);

	//Init information
	InitButtons(data);
	AD_InitShip(data);
	InitMark(data);
	InitLaunch(data);
	AD_InitGoal(data);
	AD_InitAsteroid(data);
	AD_InitPlanet(data);
	AD_InitFuel(data);
	InitPlanetEdge(data);
	InitBoostHud(data);

	pPM->AD_InitBG(pBG, data.TextureData);
}

void AdventureUpdate(float dt)
{
	//take objects
	Ship* pShip = data.pOM->GetShip();
	Planet* pPlanet = data.pOM->GetPlanet();
	Goal* pGoal = data.pOM->GetGoal();
	Object *pMark = data.pOM->GetMark();
	Object *pLaunch = data.pOM->GetLaunch();
	Object *pFuel = data.pOM->GetFuel();
	Button *pButton = data.pOM->GetButton();
	Button *pBoost = data.pOM->GetBoost();
	Asteroid *pAsteroid = data.pOM->GetAsteroid();
	Edge *pEdge = data.pOM->GetPlanetEdge();
	Particle* pBG   = pPM->GetBG();
	Particle* pCrash = pPM->GetExplode();
	Particle* pBooster = pPM->GetBoost();
	Particle* pByebye = pPM->GetByebye();


	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);

	//camera control
	AD_Camera_position(pShip, data);
	//keyboard
	KeyboardAct(data);
	
		//camera move time
		if (pShip->shiptype == SHIP_SHOOTED)
		{
			data.camera_time += dt;
		}
		else data.camera_time = 0;
	

	//pull bullet
	if (data.editmode != true)
	{
		//Launch Ship by mouse
		LaunchShip(pShip);

		//Mark Update
		MarkPosition(pShip, pMark);
		//Launch HUD Update
		LaunchHudLogic(pShip, pLaunch);

		//ship Update
		ShipMovement(pShip, dt);
		Planet_Gravity_Colision(pShip, pPlanet, pEdge, data, pCrash, pPM,dt, time_planet);
		ArriveGoal(pShip, pGoal, data);
		//if(data.level >= 5)
		BoosterShip(pShip, pBooster, pPM, dt, data);
		AngleOfShip(pShip, pMark);
		Asteroid_Collision(pShip, pAsteroid, data, pCrash, pPM);
		Fuel_Collision(pShip, pFuel, data);
		ObjectMovement(pAsteroid, dt, data.pOM);
		AsteroidDurab(pAsteroid, data.pOM);

		//HUD activity
		PressButton(pButton, data);
		AD_BoostGaugeUpdate(pBoost, pShip);
		AD_ByeBteShip(pShip, data, pByebye, pPM);
		SoundManager::sharedManager()->update();
		pPM->UpdateBG(pBG, dt);
		pPM->UpdateCrashing(pCrash, dt);
		pPM->UpdateByebye(pByebye, dt);
		pPM->PooozicBoosting(pBooster, pShip, dt, data);
		


	}
	PlanetEdgePosition(pEdge, pPlanet, data);
			
		
		//start draw
		WEGraphics::StartDraw();

		//perspective to z order
		WEGraphics::SetToPerspective();

		//Draw Objects
		pPM->DrawBG(pBG);
		pPM->DrawBoosting(pBooster, data.TextureData);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		DrawShip(pShip,data);
		DrawPlanet(pPlanet,data);
		DrawMark(pMark);
		DrawFuel(pFuel, data);
		DrawLaunch(pLaunch);
		DrawAsteroid(pAsteroid,data);
		DrawPlanetEdge(pEdge,data);
		DrawGoal(pGoal);
		//trace.Draw(data);

		pPM->DrawCrasing(pCrash, data.TextureData);
		pPM->DrawByebye(pByebye, data.TextureData);

		WEGraphics::SetTextureColor(255, 255, 255, 255);

		//hud
		WEGraphics::SetToOrtho();
		DrawHud(pButton);
		DrawBoostHud(pBoost);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		DrawBoostIcon(data);
		DrawBoostEdge(data);
		DrawPause(data);

	//End draw
	WEGraphics::EndDraw();


	

}
void AdventureShutdown(void)
{
	
}
void AdventureUnload(void)
{
	WEDEBUG_PRINT("Trace cleaned.\n");
	WEGraphics::UnloadTexture(data.TextureData.markTexture);
	WEGraphics::UnloadTexture(data.TextureData.shipTexture);
	WEGraphics::UnloadTexture(data.TextureData.quitTexture);
	WEGraphics::UnloadTexture(data.TextureData.planetTexture);
	WEGraphics::UnloadTexture(data.TextureData.goalTexture);
	WEGraphics::UnloadTexture(data.TextureData.menuTexture);
	WEGraphics::UnloadTexture(data.TextureData.replayTexture);
	WEGraphics::UnloadTexture(data.TextureData.launchTexture);
	WEGraphics::UnloadTexture(data.TextureData.asteroidTexture);
	WEGraphics::UnloadTexture(data.TextureData.edgeTexture);
	WEGraphics::UnloadTexture(data.TextureData.boostTexture);
	WEGraphics::UnloadTexture(data.TextureData.DragTheSpaceship);
	WEGraphics::UnloadTexture(data.TextureData.BoosterText);
	WEGraphics::UnloadTexture(data.TextureData.RotationText);
	WEGraphics::UnloadTexture(data.TextureData.ZoomText);
	WEGraphics::UnloadTexture(data.TextureData.RestartText);
	WEGraphics::UnloadTexture(data.TextureData.circleTexture);
	WEGraphics::UnloadTexture(data.TextureData.traceTexture);
	WEGraphics::UnloadTexture(data.TextureData.preplay);
	WEGraphics::UnloadTexture(data.TextureData.pmenu);
	WEGraphics::UnloadTexture(data.TextureData.pausetext);
	WEGraphics::UnloadTexture(data.TextureData.BoostEdgeTexture);
	WEGraphics::UnloadTexture(data.TextureData.FuelTexture);
	WEGraphics::UnloadTexture(data.TextureData.EggWaitTexture);
	WEGraphics::UnloadTexture(data.TextureData.EggPasicTexture);
	WEGraphics::UnloadTexture(data.TextureData.EggSleepTexture);
	WEGraphics::UnloadTexture(data.TextureData.EggWakeUpTexture);

}