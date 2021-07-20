/******************************************************************************
\file	CustomMode.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Data.h"
#include "Hud.h"
#include "Planet.h"
#include "Objects.h"
#include "SpaceShip.h"
#include "Environment.h"
#include "ParticleManager.h"
#include "FileIO.h"
#include "EditObject.h"
#include "Trace.h"
#include "CustomMode.h"
#include "Message.h"
#include "vector"
#include "Button.h"
#include <string>
int Slot::s_slotID = 0;

namespace
{
	ReturnData returndata;
	ParticleManager *pPM;
	Trace trace;
	float timer;
	float time_planet;
	button help;
	int helpTexture;
	int helpButtonTexture;
}

//Level set on planet and asteroid

void CustomMode_Manager(void)
{
	returndata.max_planets = 50;
	returndata.max_asteroid = 100;
	returndata.max_ship = 1;
	returndata.max_fuel = 30;
	returndata.custom_max_asteroid = returndata.max_planets;
	returndata.custom_max_planet   = returndata.max_asteroid;
	returndata.custom_max_fuel     = returndata.max_fuel;
}

void CustomModeLoad(void)  //take image files
{
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEDEBUG_PRINT("adventure loaded\n");
	returndata.TextureData.markTexture = WEGraphics::LoadTexture("Textures/Mark.tga");
	returndata.TextureData.shipTexture = WEGraphics::LoadTexture("Textures/spaceship4.tga");
	returndata.TextureData.quitTexture = WEGraphics::LoadTexture("Textures/Quit.tga");
	returndata.TextureData.planetTexture = WEGraphics::LoadTexture("Textures/samplePlanet2.tga");
	returndata.TextureData.planetPTexture = WEGraphics::LoadTexture("Textures/PlanetP.tga");
	returndata.TextureData.goalTexture = WEGraphics::LoadTexture("Textures/Goal.tga");
	returndata.TextureData.replayTexture = WEGraphics::LoadTexture("Textures/Replay.tga");
	returndata.TextureData.menuTexture = WEGraphics::LoadTexture("Textures/Menu.tga");
	returndata.TextureData.launchTexture = WEGraphics::LoadTexture("Textures/LaunchHUD.tga");
	returndata.TextureData.asteroidTexture = WEGraphics::LoadTexture("Textures/Asteroid.tga");
	returndata.TextureData.asteroidPTexture = WEGraphics::LoadTexture("Textures/AsteroidP.tga");
	returndata.TextureData.edgeTexture = WEGraphics::LoadTexture("Textures/PlanetEdge.tga");
	returndata.TextureData.boostTexture = WEGraphics::LoadTexture("Textures/BoostGauge.tga");
	returndata.TextureData.DragTheSpaceship = WEGraphics::LoadTexture("Textures/DragTheSpaceship.tga");
	returndata.TextureData.BoosterText = WEGraphics::LoadTexture("Textures/BoosterText.tga");
	returndata.TextureData.RotationText = WEGraphics::LoadTexture("Textures/Rotation.tga");
	returndata.TextureData.ZoomText = WEGraphics::LoadTexture("Textures/Zoom.tga");
	returndata.TextureData.RestartText = WEGraphics::LoadTexture("Textures/RestartText.tga");
	returndata.TextureData.circleTexture = WEGraphics::LoadTexture("Textures/Circle.tga");
	returndata.TextureData.traceTexture = WEGraphics::LoadTexture("Textures/TraceTexture.tga");
	returndata.TextureData.preplay = WEGraphics::LoadTexture("Textures/Preplay.tga");
	returndata.TextureData.pmenu = WEGraphics::LoadTexture("Textures/PMenu.tga");
	returndata.TextureData.leveltext = WEGraphics::LoadTexture("Textures/LevelText.tga");
	returndata.TextureData.pausetext = WEGraphics::LoadTexture("Textures/Pause.tga");
	returndata.TextureData.saveTexture = WEGraphics::LoadTexture("Textures/Saved.tga");
	returndata.TextureData.BoostEdgeTexture = WEGraphics::LoadTexture("Textures/BoosterEdge.tga");
	returndata.TextureData.FuelTexture = WEGraphics::LoadTexture("Textures/Fuel.tga");
	returndata.TextureData.FuelPTexture = WEGraphics::LoadTexture("Textures/FuelP.tga");
	returndata.TextureData.number0Texture = WEGraphics::LoadTexture("Textures/num0.tga");
	returndata.TextureData.number1Texture = WEGraphics::LoadTexture("Textures/num1.tga");
	returndata.TextureData.number2Texture = WEGraphics::LoadTexture("Textures/num2.tga");
	returndata.TextureData.number3Texture = WEGraphics::LoadTexture("Textures/num3.tga");
	returndata.TextureData.number4Texture = WEGraphics::LoadTexture("Textures/num4.tga");
	returndata.TextureData.number5Texture = WEGraphics::LoadTexture("Textures/num5.tga");
	returndata.TextureData.number6Texture = WEGraphics::LoadTexture("Textures/num6.tga");
	returndata.TextureData.number7Texture = WEGraphics::LoadTexture("Textures/num7.tga");
	returndata.TextureData.number8Texture = WEGraphics::LoadTexture("Textures/num8.tga");
	returndata.TextureData.number9Texture = WEGraphics::LoadTexture("Textures/num9.tga");
	returndata.TextureData.EggWaitTexture = WEGraphics::LoadTexture("Textures/EggWait.tga");
	returndata.TextureData.EggPasicTexture = WEGraphics::LoadTexture("Textures/EggPasic.tga");
	returndata.TextureData.EggSleepTexture = WEGraphics::LoadTexture("Textures/EggSleep.tga");
	returndata.TextureData.EggWakeUpTexture = WEGraphics::LoadTexture("Textures/EggWakeup.tga");
	returndata.TextureData.EditOnTexture = WEGraphics::LoadTexture("Textures/EditModeOn.tga");
	returndata.TextureData.SaveIconTexture = WEGraphics::LoadTexture("Textures/Saveicon.tga");
	returndata.TextureData.SaveIconPTexture = WEGraphics::LoadTexture("Textures/SaveiconP.tga");
	returndata.TextureData.EditIconTexture = WEGraphics::LoadTexture("Textures/EditIcon.tga");
	returndata.TextureData.EditIconPTexture = WEGraphics::LoadTexture("Textures/EditIconP.tga");
	returndata.TextureData.slotText = WEGraphics::LoadTexture("Textures/Slot.tga");
	returndata.TextureData.MoveTexture = WEGraphics::LoadTexture("Textures/MoveIcon.tga");
	returndata.TextureData.MovePTexture = WEGraphics::LoadTexture("Textures/MoveIconP.tga");
	returndata.TextureData.MagicPenTexture = WEGraphics::LoadTexture("Textures/MagicPen.tga");
	returndata.TextureData.MagicPenPTexture = WEGraphics::LoadTexture("Textures/MagicPenP.tga");
	returndata.TextureData.explain1Texture = WEGraphics::LoadTexture("Textures/explain1.tga");
	returndata.TextureData.explain2Texture = WEGraphics::LoadTexture("Textures/explain2.tga");
	helpButtonTexture = WEGraphics::LoadTexture("Textures/HelpButton.tga");
	helpTexture = WEGraphics::LoadTexture("Textures/HowToPlay.tga");

	trace.SetTexture(returndata.TextureData.traceTexture);

	returndata.cameraZ = 700;
	returndata.level = 100 + Slot::s_slotID;
	SoundManager::sharedManager()->play(START);
	SoundManager::sharedManager()->play(BG);
	SoundManager::sharedManager()->stop(MAINMENU);
	SoundManager::sharedManager()->stop(SPLASH);
	returndata.life_count = 1;
	returndata.boostfire = false;
	returndata.editmode = false;
	returndata.mouseState = 1;
	returndata.explain_button = NONE;
	time_planet = 1;
	for (int i = 1; i < TRACENUMBER; i++)
		trace.Push();


	returndata.game_mode = CUSTOMMODE;
}


void CustomModeInit(void)
{
	WEDEBUG_PRINT("adventure INITIATED\n");
	if (returndata.cameraZ < 400)
		returndata.cameraZ = 500;
	CustomMode_Manager();
	//create objects
	returndata.pOM = new ObjectManager(returndata.max_ship, returndata.max_planets, returndata.max_asteroid, returndata.max_fuel);
	pPM = new ParticleManager();
	Particle* pBG = pPM->GetBG();
	Particle* pCrash = pPM->GetExplode();
	Particle* pBoost = pPM->GetBoost();
	Particle* pByebye = pPM->GetByebye();
	pPM->LoadBoosting(pBoost);
	pPM->LoadCrashing(pCrash);
	pPM->LoadBG(pBG);
	pPM->LoadByebye(pByebye);

	returndata.screenWidth = (float)WEApplication::GetWidth();
	returndata.screenHeight = (float)WEApplication::GetHeight();
	returndata.camera_time = 0;
	//View point
	WEGraphics::SetViewport(0, 0, (int)returndata.screenWidth, (int)returndata.screenHeight);

	//Init information
	InitButtons(returndata);
	InitShip(returndata);
	InitMark(returndata);
	InitLaunch(returndata);
	InitGoal(returndata);
	CT_InitAsteroid(returndata);
	CT_InitPlanet(returndata);
	CT_InitFuel(returndata);
	InitPlanetEdge(returndata);
	InitBoostHud(returndata);

	Ship* pShip = returndata.pOM->GetShip();
	trace.SetShip(pShip);
	trace.SetFalse();
	pPM->InitBG(pBG, returndata.TextureData.circleTexture);

	help.Initialize({ 288, 688 }, helpButtonTexture, helpButtonTexture);
	help.scale.x = 64;
	help.scale.y = 64;

	InitEditSave(returndata);
	InitEditMouse(returndata);
	InitEditObjects(returndata);
}

void CustomModeUpdate(float dt)
{
	//take objects
	Ship* pShip = returndata.pOM->GetShip();
	Planet* pPlanet = returndata.pOM->GetPlanet();
	Goal* pGoal = returndata.pOM->GetGoal();
	Object *pMark = returndata.pOM->GetMark();
	Object *pLaunch = returndata.pOM->GetLaunch();
	Object *pFuel = returndata.pOM->GetFuel();
	Button *pButton = returndata.pOM->GetButton();
	Button *pBoost = returndata.pOM->GetBoost();
	Asteroid *pAsteroid = returndata.pOM->GetAsteroid();
	Edge *pEdge = returndata.pOM->GetPlanetEdge();
	Particle* pBG = pPM->GetBG();
	Particle* pCrash = pPM->GetExplode();
	Particle* pBooster = pPM->GetBoost();
	Particle* pByebye = pPM->GetByebye();

	Button *pEObjects = returndata.pOM->GetEditObjects();
	Button *pEMouse = returndata.pOM->GetEditMouse();
	Button *pESave = returndata.pOM->GetEditSave();


	//mouse position
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	WEGraphics::SetBackgroundColor(0.0f, 0.0f, 0.0f);

	int planetCount = returndata.pOM->GetPlanetCount();
	int asteroidCount = returndata.pOM->GetAsteroidCount();
	int fuelCount = returndata.pOM->GetFuelCount();

	//WEDEBUG_PRINT("editmode %d\n", data.editmode);
	//camera control
	Camera_Z(returndata);
	Camera_position(pShip, returndata, dt);
	//keyboard
	KeyboardAct(returndata);
	PressEditSave(pESave, returndata, timer, pPlanet, pAsteroid, pFuel);
	std::string path = getenv("USERPROFILE");
	path += "/My Documents/Return/";

	//save
	if (WEInput::IsTriggered(WE_S))
	{
		timer = 1;
		switch (returndata.level)
		{
		case 101:
		{
			PlanetSaveFile(std::string(path + "LevelData/planet101.txt").c_str(), pPlanet, returndata);
			AsteroidSaveFile(std::string(path + "LevelData/Asteroid101.txt").c_str(), pAsteroid, returndata);
			FuelSaveFile(std::string(path + "LevelData/fuel101.txt").c_str(), pFuel, returndata);
			break;
		}
		case 102:
		{
			PlanetSaveFile(std::string(path + "LevelData/planet102.txt").c_str(), pPlanet, returndata);
			AsteroidSaveFile(std::string(path + "LevelData/Asteroid102.txt").c_str(), pAsteroid, returndata);
			FuelSaveFile(std::string(path + "LevelData/fuel102.txt").c_str(), pFuel, returndata);
			break;
		}
		case 103:
		{
			PlanetSaveFile(std::string(path + "LevelData/planet103.txt").c_str(), pPlanet, returndata);
			AsteroidSaveFile(std::string(path + "LevelData/Asteroid103.txt").c_str(), pAsteroid, returndata);
			FuelSaveFile(std::string(path + "LevelData/fuel103.txt").c_str(), pFuel, returndata);
			break;
		}
		}
	}

	//when edit mode
	if (returndata.editmode == true)
	{
		PressEditMouse(pEMouse, returndata);
		if (returndata.mouseState != 1 && returndata.mouseState != 2)
			returndata.mouseState = 1;
		if (WEInput::IsTriggered(WE_9))
			returndata.mouseState = 1;
		if (WEInput::IsTriggered(WE_0))
			returndata.mouseState = 2;
		switch (returndata.mouseState)
		{
		case 1:
		{
			EditPlanetT(pPlanet, returndata.pOM);
			EditAsteroid(pAsteroid, returndata.pOM);
			EditFuel(pFuel, returndata.pOM);
			break;
		}
		case 2:
		{
			EditPlanetSize(pPlanet, returndata.pOM);
			EditAsteroidVel(pAsteroid, returndata.pOM);
			break;
		}
		}
	}

	ObjectMovement(pAsteroid, dt, returndata.pOM);
	AsteroidDurab(pAsteroid, returndata.pOM);

	//camera move time
	if (pShip->shiptype == SHIP_SHOOTED)
	{
		returndata.camera_time += dt;
	}

	else returndata.camera_time = 0;


	//pull bullet
	if (returndata.editmode != true)
	{
		//Launch Ship by mouse
		LaunchShip(pShip);

		//Mark Update
		MarkPosition(pShip, pMark);
		//Launch HUD Update
		LaunchHudLogic(pShip, pLaunch);

		//ship Update
		ShipMovement(pShip, dt);
		Planet_Gravity_Colision(pShip, pPlanet, pEdge, returndata, pCrash, pPM, dt, time_planet);
		ArriveGoal(pShip, pGoal, returndata);
		//if(data.level >= 5)
		BoosterShip(pShip, pBooster, pPM, dt, returndata);
		Fuel_Collision(pShip, pFuel, returndata);
		AngleOfShip(pShip, pMark);
		Asteroid_Collision(pShip, pAsteroid, returndata, pCrash, pPM);

		//HUD activity
		PressButton(pButton, returndata);
		BoostGaugeUpdate(pBoost, pShip);
		ByeBteShip(pShip, returndata, pByebye, pPM);
		SoundManager::sharedManager()->update();
		pPM->UpdateBG(pBG, dt);
		pPM->UpdateCrashing(pCrash, dt);
		pPM->UpdateByebye(pByebye, dt);
		pPM->PooozicBoosting(pBooster, pShip, dt, returndata);
		trace.Update(dt);

	}
	PlanetEdgePosition(pEdge, pPlanet, returndata);


	// make objects
	if (returndata.editmode == true)
	{

		PressEditObjects(pEObjects, returndata);
		//Add Objects
		if (WEInput::IsTriggered(WE_P))
		{
			returndata.pOM->SetPlanet(mouse,// { 831.0f, 290.0f },
			{ 256,256 }, 100, 100, returndata.TextureData.planetTexture, planetCount, PLANET_LIFE);
			returndata.pOM->SetPlanetEdge(pPlanet[planetCount].pos,
				pPlanet[planetCount].scale * 2,
				returndata.TextureData.edgeTexture,
				planetCount);

			returndata.pOM->IncPlanetCount();
			returndata.max_planets++;
		}
		if (WEInput::IsTriggered(WE_A))
		{

			returndata.pOM->SetAsteroid(mouse, //{ 831.0f, 290.0f },
			{ 50,50 }, { 0,0 }, 0, returndata.TextureData.asteroidTexture, asteroidCount);

			returndata.pOM->IncAsteroidCount();
			returndata.max_asteroid++;
		}
		if (WEInput::IsTriggered(WE_F))
		{
			if (fuelCount < returndata.custom_max_fuel)
			{
				returndata.pOM->SetFuel(mouse,
				{ 75, 75 }, { 0,0 }, 0, returndata.TextureData.FuelTexture, fuelCount);

				returndata.pOM->IncFuelCount();
				returndata.max_fuel++;
			}
		}
	}

	//start draw
	WEGraphics::StartDraw();

	//perspective to z order
	WEGraphics::SetToPerspective();

	//Draw Objects
	pPM->DrawBG(pBG);
	pPM->DrawBoosting(pBooster, returndata.TextureData);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	DrawShip(pShip, returndata);
	DrawPlanet(pPlanet, returndata);
	DrawMark(pMark);
	DrawFuel(pFuel, returndata);
	DrawLaunch(pLaunch);
	DrawAsteroid(pAsteroid, returndata);
	DrawPlanetEdge(pEdge, returndata);
	DrawGoal(pGoal);
	//trace.Draw(data);

	pPM->DrawCrasing(pCrash, returndata.TextureData);
	pPM->DrawByebye(pByebye, returndata.TextureData);

	WEGraphics::SetTextureColor(255, 255, 255, 255);

	//hud
	WEGraphics::SetToOrtho();
	DrawHud(pButton);
	DrawBoostHud(pBoost);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	DrawBoostEdge(returndata);
	DrawEditOn(returndata);
	DrawBoostIcon(returndata);
	DrawEditSave(pESave);
	DrawEditMouse(pEMouse);
	DrawLevelNumber(returndata);
	DrawEditObjects(pEObjects);
	DrawLeveltext(returndata);
	DrawEditExplain(returndata);
	DrawBoostIcon(returndata);
	ShowFileSaved(returndata, dt, timer);
	help.Draw(mouse);

	WEInput::GetMouse(mouse);
	if (help.IsDetected(mouse))
	{
		WEMtx44 transform;
		WEGraphics::SetTexture(helpTexture);
		WEMtx44::MakeTransform(transform, returndata.screenWidth, returndata.screenHeight, 0,
			returndata.screenWidth / 2.f, returndata.screenHeight/2.f, 0);
		WEGraphics::Draw(transform);
	}

	//End draw
	WEGraphics::EndDraw();

}
void CustomModeShutdown(void)
{

}
void CustomModeUnload(void)
{
	//trace.Clean();
	WEDEBUG_PRINT("Trace cleaned.\n");
	WEGraphics::UnloadTexture(returndata.TextureData.markTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.shipTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.quitTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.planetTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.goalTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.menuTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.replayTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.launchTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.asteroidTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.edgeTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.boostTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.DragTheSpaceship);
	WEGraphics::UnloadTexture(returndata.TextureData.BoosterText);
	WEGraphics::UnloadTexture(returndata.TextureData.RotationText);
	WEGraphics::UnloadTexture(returndata.TextureData.ZoomText);
	WEGraphics::UnloadTexture(returndata.TextureData.RestartText);
	WEGraphics::UnloadTexture(returndata.TextureData.circleTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.traceTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.preplay);
	WEGraphics::UnloadTexture(returndata.TextureData.pmenu);
	WEGraphics::UnloadTexture(returndata.TextureData.pausetext);
	WEGraphics::UnloadTexture(returndata.TextureData.leveltext);
	WEGraphics::UnloadTexture(returndata.TextureData.saveTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.BoostEdgeTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.FuelTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.number0Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number1Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number2Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number3Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number4Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number5Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number6Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number7Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number8Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.number9Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.EggWaitTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EggPasicTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EggSleepTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EggWakeUpTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EditOnTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.planetPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.asteroidPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.FuelPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.SaveIconTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.SaveIconPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EditIconTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.EditIconPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.slotText);
	WEGraphics::UnloadTexture(returndata.TextureData.MoveTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.MovePTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.MagicPenTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.MagicPenPTexture);
	WEGraphics::UnloadTexture(returndata.TextureData.explain1Texture);
	WEGraphics::UnloadTexture(returndata.TextureData.explain2Texture);
	WEGraphics::UnloadTexture(helpButtonTexture);
	WEGraphics::UnloadTexture(helpTexture);
	//WEDEBUG_PRINT("Stage Unloaded");

}