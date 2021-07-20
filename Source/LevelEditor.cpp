/******************************************************************************
\file	LevelEditor.cpp
\title  Returner
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "LevelEditor.h"
#include "Data.h"
#include "ParticleManager.h"
#include "Trace.h"

#include "Hud.h"
#include "LevelEditor.h"
#include "Planet.h"
#include "Objects.h"
#include "SpaceShip.h"
#include "Environment.h"
#include "FileIO.h"
#include "EditObject.h"

namespace
{
	ReturnData data;
	ParticleManager *pPM;
	Trace trace;
	float timer;
	float time_planet;
}




void LevelEditorLoad(void)  //take image files
{
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	data.TextureData.playerTexture   = WEGraphics::LoadTexture("Textures/Player.tga");
	data.TextureData.markTexture     = WEGraphics::LoadTexture("Textures/Mark.tga");
	data.TextureData.shipTexture     = WEGraphics::LoadTexture("Textures/spaceship.tga");
	data.TextureData.quitTexture     = WEGraphics::LoadTexture("Textures/Quit.tga");
	data.TextureData.planetTexture   = WEGraphics::LoadTexture("Textures/samplePlanet.tga");
	data.TextureData.goalTexture     = WEGraphics::LoadTexture("Textures/Goal.tga");
	data.TextureData.replayTexture   = WEGraphics::LoadTexture("Textures/Replay.tga");
	data.TextureData.menuTexture     = WEGraphics::LoadTexture("Textures/Menu.tga");
	data.TextureData.launchTexture   = WEGraphics::LoadTexture("Textures/LaunchHUD.tga");
	data.TextureData.asteroidTexture = WEGraphics::LoadTexture("Textures/Asteroid.tga");
	data.TextureData.edgeTexture     = WEGraphics::LoadTexture("Textures/PlanetEdge.tga");
	data.TextureData.boostTexture    = WEGraphics::LoadTexture("Textures/BoostGauge.tga");
	data.TextureData.saveTexture	 = WEGraphics::LoadTexture("Textures/Saved.tga");
	data.TextureData.BoostEdgeTexture = WEGraphics::LoadTexture("Textures/BoosterEdge.tga");
	data.TextureData.FuelTexture = WEGraphics::LoadTexture("Textures/Fuel.tga");
	data.TextureData.circleTexture = WEGraphics::LoadTexture("Textures/Circle.tga");
	data.TextureData.traceTexture = WEGraphics::LoadTexture("Textures/TraceTexture.tga");
	data.TextureData.preplay = WEGraphics::LoadTexture("Textures/Preplay.tga");
	data.TextureData.pmenu = WEGraphics::LoadTexture("Textures/PMenu.tga");
	data.TextureData.leveltext = WEGraphics::LoadTexture("Textures/LevelText.tga");
	data.TextureData.pausetext = WEGraphics::LoadTexture("Textures/Pause.tga");
	data.TextureData.number0Texture = WEGraphics::LoadTexture("Textures/num0.tga");
	data.TextureData.number1Texture = WEGraphics::LoadTexture("Textures/num1.tga");
	data.TextureData.number2Texture = WEGraphics::LoadTexture("Textures/num2.tga");
	data.TextureData.number3Texture = WEGraphics::LoadTexture("Textures/num3.tga");
	data.TextureData.number4Texture = WEGraphics::LoadTexture("Textures/num4.tga");
	data.TextureData.number5Texture = WEGraphics::LoadTexture("Textures/num5.tga");
	data.TextureData.number6Texture = WEGraphics::LoadTexture("Textures/num6.tga");
	data.TextureData.number7Texture = WEGraphics::LoadTexture("Textures/num7.tga");
	data.TextureData.number8Texture = WEGraphics::LoadTexture("Textures/num8.tga");
	data.TextureData.number9Texture = WEGraphics::LoadTexture("Textures/num9.tga");
	data.cameraZ = 700;
	data.level = 1;
	data.editmode = true;
	data.mouseState = 1;
	time_planet = 1;
	for (int i = 1; i < TRACENUMBER; i++)
		trace.Push();
	SoundManager::sharedManager()->play(START);
	SoundManager::sharedManager()->play(BG);
	SoundManager::sharedManager()->stop(MAINMENU);
	SoundManager::sharedManager()->stop(SPLASH);
	data.game_mode = STORY;
}


void LevelEditorInit(void)
{

	//LevelManager();
	data.max_planets = 200;
	data.max_asteroid = 200;
	data.max_ship = 1;
	data.max_fuel = 20;
	data.custom_max_asteroid = data.max_planets;
	data.custom_max_planet = data.max_asteroid;
	data.custom_max_fuel = data.max_fuel;
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
	InitPlanet(data);
	InitShip(data);
	InitMark(data);
	InitLaunch(data);
	InitGoal(data);
	InitAsteroid(data);
	InitFuel(data);
	InitPlanetEdge(data);	
	InitBoostHud(data);

	Ship* pShip = data.pOM->GetShip();
	trace.SetShip(pShip);
	trace.SetFalse();
	pPM->InitBG(pBG, data.TextureData.circleTexture);
	InitEditMouse(data);
	InitEditObjects(data);
}

void LevelEditorUpdate(float dt)
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
	Particle* pBG = pPM->GetBG();
	Particle* pCrash = pPM->GetExplode();
	Particle* pBooster = pPM->GetBoost();
	Particle* pByebye = pPM->GetByebye();

	Button *pEObjects = data.pOM->GetEditObjects();
	Button *pEMouse   = data.pOM->GetEditMouse();

	//mouse position
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);
	
	
	int planetCount = data.pOM->GetPlanetCount();
	int asteroidCount = data.pOM->GetAsteroidCount();
	int fuelCount = data.pOM->GetFuelCount();


	//keyboard
	KeyboardAct( data);

	//save
	if (WEInput::IsTriggered(WE_S))
	{
		//SaveFile(saveName, pPlanet);
		//WEGraphics::WriteText("File Saved", 200, 700);
		timer = 1;  
		switch (data.level)
		{
			case 1:
			{
				PlanetSaveFile("LevelData/planet1.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid1.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel1.txt", pFuel, data);
				break;
			}
			case 2:
			{
				PlanetSaveFile("LevelData/planet2.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid2.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel2.txt", pFuel, data);
				break;
			}
			case 3:
			{
				PlanetSaveFile("LevelData/planet3.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid3.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel3.txt", pFuel, data);
				break;
			}
			case 4:
			{
				PlanetSaveFile("LevelData/planet4.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid4.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel4.txt", pFuel, data);
				break;
			}
			case 5:
			{
				PlanetSaveFile("LevelData/planet5.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid5.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel5.txt", pFuel, data);
				break;
			}
			case 6:
			{
				PlanetSaveFile("LevelData/planet6.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid6.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel6.txt", pFuel, data);
				break;
			}
			case 7:
			{
				PlanetSaveFile("LevelData/planet7.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid7.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel7.txt", pFuel, data);
				break;
			}
			case 8:
			{
				PlanetSaveFile("LevelData/planet8.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid8.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel8.txt", pFuel, data);
				break;
			}
			case 9:
			{
				PlanetSaveFile("LevelData/planet9.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid9.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel9.txt", pFuel, data);
				break;
			}
			case 10:
			{
				PlanetSaveFile("LevelData/planet10.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid10.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel10.txt", pFuel, data);
				break;
			}
			case 11:
			{
				PlanetSaveFile("LevelData/planet11.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid11.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel11.txt", pFuel, data);
				break;
			}
			case 12:
			{
				PlanetSaveFile("LevelData/planet12.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid12.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel12.txt", pFuel, data);
				break;
			}
			case 13:
			{
				PlanetSaveFile("LevelData/planet13.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid13.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel13.txt", pFuel, data);
				break;
			}
			case 14:
			{
				PlanetSaveFile("LevelData/planet14.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid14.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel14.txt", pFuel, data);
				break;
			}
			case 15:
			{
				PlanetSaveFile("LevelData/planet15.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid15.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel15.txt", pFuel, data);
				break;
			}

		}
	}


	//when edit mode
	if (data.editmode == true)
	{
		if(data.mouseState != 1 && data.mouseState != 2)
			data.mouseState = 1;
		if (WEInput::IsTriggered(WE_9))
			data.mouseState = 1;
		if (WEInput::IsTriggered(WE_0))
			data.mouseState = 2;
		switch (data.mouseState)
		{
		case 1:
		{
			EditPlanetT(pPlanet, data.pOM);
			EditAsteroid(pAsteroid, data.pOM);
			EditFuel(pFuel, data.pOM);
			break;
		}
		case 2:
		{
			EditPlanetSize(pPlanet, data.pOM);
			EditAsteroidVel(pAsteroid, data.pOM);
			break;
		}
		}
	}

	ObjectMovement(pAsteroid, dt, data.pOM);
	AsteroidDurab(pAsteroid, data.pOM);

	//camera move time
	if (pShip->shiptype == SHIP_SHOOTED)
	{
		data.camera_time += dt;
	}

	//pull bullet
	if (data.editmode != true)
	{
		//data.mouseState = 0;
		//Launch Ship by mouse
		LaunchShip(pShip);

		//Mark Update
		MarkPosition(pShip, pMark);
		//Launch HUD Update
		LaunchHudLogic(pShip, pLaunch);

		//ship Update
		ShipMovement(pShip, dt);
		Planet_Gravity_Colision(pShip, pPlanet, pEdge, data, pCrash, pPM, dt, time_planet);
		ArriveGoal(pShip, pGoal, data);
		BoosterShip(pShip, pBooster, pPM, dt, data);
		AngleOfShip(pShip, pMark);
		Asteroid_Collision(pShip, pAsteroid, data, pCrash, pPM);

		//HUD activity
		PressButton(pButton, data);
		BoostGaugeUpdate(pBoost, pShip);
		ByeBteShip(pShip, data, pByebye, pPM);
		SoundManager::sharedManager()->update();
		pPM->UpdateBG(pBG, dt);
		pPM->UpdateCrashing(pCrash, dt);
		pPM->UpdateByebye(pByebye, dt);
		pPM->PooozicBoosting(pBooster, pShip, dt, data);
		trace.Update(dt);
	}

	PlanetEdgePosition(pEdge, pPlanet, data);

	//Camera position
	WEGraphics::SetCamera(data.screenWidth / 2, data.screenHeight / 2, data.cameraZ, 0);

	//Planet planet;
	if (data.editmode == true)
	{
		PressEditObjects(pEObjects, data);
		//Add Objects
		if (WEInput::IsTriggered(WE_P))
		{
			/*pPlanet[planetCount].pos.x = 831.0f;
			pPlanet[planetCount].pos.y = 290.0f;
			pPlanet[planetCount].scale.x = 256;
			pPlanet[planetCount].scale.y = 256;
			pPlanet[planetCount].gravity = 100;
			pPlanet[planetCount].mass = 100;
			pPlanet[planetCount].pull = true;
			pPlanet[planetCount].count = true;
			pPlanet[planetCount].texture = data.TextureData.planetTexture;*/
			data.pOM->SetPlanet(mouse,// { 831.0f, 290.0f },
			{ 256,256 }, 100, 100, data.TextureData.planetTexture, planetCount, PLANET_LIFE);
			data.pOM->SetPlanetEdge(pPlanet[planetCount].pos,
				pPlanet[planetCount].scale * 2,
				data.TextureData.edgeTexture,
				planetCount);

			data.pOM->IncPlanetCount();
			data.max_planets++;
		}
		if (WEInput::IsTriggered(WE_A))
		{

			data.pOM->SetAsteroid(mouse, //{ 831.0f, 290.0f },
			{ 50,50 }, { 0,0 }, 0, data.TextureData.asteroidTexture, asteroidCount);

			data.pOM->IncAsteroidCount();
			data.max_asteroid++;
		}
		if (WEInput::IsTriggered(WE_F))
		{
			if (fuelCount < data.custom_max_fuel)
			{
				data.pOM->SetFuel(mouse,
				{ 75, 75 }, { 0,0 }, 0, data.TextureData.FuelTexture, fuelCount);

				data.pOM->IncFuelCount();
				data.max_fuel++;
			}
		}
	}
	//save level control
	//if (WEInput::IsTriggered(WE_ARROW_UP))
	//	data.level++;
	//if (WEInput::IsTriggered(WE_ARROW_DOWN))
	//	data.level--;

	//start draw
	WEGraphics::StartDraw();

	//perspective to z order
	WEGraphics::SetToPerspective();

	//Draw Objects
	pPM->DrawBG(pBG);
	pPM->DrawBoosting(pBooster, data.TextureData);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	DrawShip(pShip, data);
	DrawPlanet(pPlanet, data);
	DrawMark(pMark);
	DrawFuel(pFuel, data);
	DrawLaunch(pLaunch);
	DrawAsteroid(pAsteroid, data);
	DrawPlanetEdge(pEdge, data);
	DrawGoal(pGoal);


	pPM->DrawCrasing(pCrash, data.TextureData);
	pPM->DrawByebye(pByebye, data.TextureData);



	WEGraphics::SetTextureColor(255, 255, 255, 255);
	//hud
	WEGraphics::SetToOrtho();

	DrawHud(pButton);
	DrawHud(pButton);
	DrawBoostHud(pBoost);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	DrawBoostEdge(data);
	DrawPause(data);
	DrawBoostIcon(data);
	DrawEditMouse(pEMouse);
	DrawEditObjects(pEObjects);
	DrawLeveltext(data);
	ShowFileSaved(data, dt, timer);


	//End draw
	WEGraphics::EndDraw();

}
void LevelEditorShutdown(void)
{

}
void LevelEditorUnload(void)
{
	WEGraphics::UnloadTexture(data.TextureData.playerTexture);
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
	WEGraphics::UnloadTexture(data.TextureData.saveTexture);
	WEGraphics::UnloadTexture(data.TextureData.BoostEdgeTexture);
	WEGraphics::UnloadTexture(data.TextureData.FuelTexture);
	WEGraphics::UnloadTexture(data.TextureData.number0Texture);
	WEGraphics::UnloadTexture(data.TextureData.number1Texture);
	WEGraphics::UnloadTexture(data.TextureData.number2Texture);
	WEGraphics::UnloadTexture(data.TextureData.number3Texture);
	WEGraphics::UnloadTexture(data.TextureData.number4Texture);
	WEGraphics::UnloadTexture(data.TextureData.number5Texture);
	WEGraphics::UnloadTexture(data.TextureData.number6Texture);
	WEGraphics::UnloadTexture(data.TextureData.number7Texture);
	WEGraphics::UnloadTexture(data.TextureData.number8Texture);
	WEGraphics::UnloadTexture(data.TextureData.number9Texture);
	WEGraphics::UnloadTexture(data.TextureData.circleTexture);
	WEGraphics::UnloadTexture(data.TextureData.traceTexture);
	WEGraphics::UnloadTexture(data.TextureData.preplay);
	WEGraphics::UnloadTexture(data.TextureData.pmenu);
	WEGraphics::UnloadTexture(data.TextureData.pausetext);
	WEGraphics::UnloadTexture(data.TextureData.leveltext);
}