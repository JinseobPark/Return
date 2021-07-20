/******************************************************************************
\file	Hud.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Hud.h"
#include "FileIO.h"

void InitButtons(ReturnData &data)
{

	data.pOM->GetButton();

	WEVec2 pos;
	WEVec2 scale;
	int texture = 0;

	//button options
	int menutexture = data.TextureData.menuTexture;
	int replaytexture = data.TextureData.replayTexture;
	
	for (int button_count = 0; button_count < BUTTON_COUNT; button_count++)
	{
		pos.x = BUTTON_WIDTH / 2 + BUTTON_WIDTH * (float)button_count;
		pos.y = data.screenHeight - BUTTON_HEIGHT / 2;
		scale.x = BUTTON_WIDTH;
		scale.y = BUTTON_HEIGHT;
		switch (button_count) {
		case 0: {texture = menutexture; break; }
		case 1: {texture = replaytexture; break; }
		}

		data.pOM->SetButton(pos, scale, button_count, texture);
	}
	
}

void InitEditObjects(ReturnData &data)
{
	data.pOM->GetEditObjects();

	WEVec2 pos;
	WEVec2 scale;
	int texture = 0;

	//button options
	int planetTexture = data.TextureData.planetTexture;
	int asteroidTexrue = data.TextureData.asteroidTexture;
	int fuelTexture = data.TextureData.FuelTexture;

	for (int button_count = 0; button_count < EDITOBJECTS_BUTTONS; button_count++)
	{
		pos.x = data.screenWidth - BUTTON_WIDTH * ((float)button_count + 0.5f);
		pos.y = BUTTON_HEIGHT / 2;
		scale.x = BUTTON_WIDTH;
		scale.y = BUTTON_HEIGHT;
		switch (button_count) {
		case 0: {texture = planetTexture; break; }
		case 1: {texture = asteroidTexrue; break; }
		case 2: {texture = fuelTexture; break; }
		}

		data.pOM->SetEditObjects(pos, scale, button_count, texture);
	}

}


void InitEditSave(ReturnData &data)
{
	data.pOM->GetEditSave();

	WEVec2 pos;
	WEVec2 scale;
	int texture = 0;

	//button options
	int savetexture = data.TextureData.SaveIconTexture;
	int edittexture = data.TextureData.EditIconTexture;

	for (int button_count = 0; button_count < BUTTON_COUNT; button_count++)
	{
		pos.x = BUTTON_WIDTH / 2 + BUTTON_WIDTH * ((float)button_count + 2);
		pos.y = data.screenHeight - BUTTON_HEIGHT / 2;
		scale.x = BUTTON_WIDTH;
		scale.y = BUTTON_HEIGHT;
		switch (button_count) {
		case 0: {texture = savetexture; break; }
		case 1: {texture = edittexture; break; }
		}

		data.pOM->SetEditSave(pos, scale, button_count, texture);
	}
}
void InitEditMouse(ReturnData &data)
{

	data.pOM->GetEditMouse();

	WEVec2 pos;
	WEVec2 scale;
	int texture = 0;

	//button options
	int movetexture = data.TextureData.MoveTexture;
	int magictexture = data.TextureData.MagicPenTexture;

	for (int button_count = 0; button_count < BUTTON_COUNT; button_count++)
	{
		pos.x = data.screenWidth - BUTTON_WIDTH * ((float)button_count + 0.5f);
		pos.y = data.screenHeight - BUTTON_HEIGHT / 2;
		scale.x = BUTTON_WIDTH;
		scale.y = BUTTON_HEIGHT;
		switch (button_count) {
		case 0: {texture = magictexture; break; }
		case 1: {texture = movetexture; break; }
		}

		data.pOM->SetEditMouse(pos, scale, button_count, texture);
	}

}
void InitBoostHud(ReturnData &data)
{
	WEVec2 pos;
	WEVec2 scale;
	int texture = data.TextureData.boostTexture;

	scale.x = 50;
	scale.y = 1200;
	pos.x = scale.x / 2;
	pos.y = 0;

	data.pOM->SetBoost(pos, scale, texture);
}



void PressEditMouse(Button *pButton, ReturnData &data)
{
	WEVec2 click;
	WEInput::GetMouse(click);

	//magic pen
	if (WEIntersection::PointRect(click, pButton[0].pos,
		pButton[0].scale.x, pButton[0].scale.y))
	{
		data.explain_button = MAGIC;
		pButton[0].texture = data.TextureData.MagicPenPTexture;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			data.mouseState = 2;
		}
	}
	else
	{
		pButton[0].texture = data.TextureData.MagicPenTexture;
	}

	//move pen
	if (WEIntersection::PointRect(click, pButton[1].pos,
		pButton[1].scale.x, pButton[1].scale.y))
	{
		data.explain_button = MOVE;
		pButton[1].texture = data.TextureData.MovePTexture;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			data.mouseState = 1;
		}
	}
	else
	{
		pButton[1].texture = data.TextureData.MoveTexture;
	}
	if (WEIntersection::PointRect(click, pButton[1].pos,
		pButton[1].scale.x, pButton[1].scale.y) ||
		WEIntersection::PointRect(click, pButton[0].pos,
			pButton[0].scale.x, pButton[0].scale.y))
	{
	}
	else
		data.explain_button = NONE;

}


void PressEditObjects(Button *pButton, ReturnData &data)
{
	int planetCount = data.pOM->GetPlanetCount();
	int asteroidCount = data.pOM->GetAsteroidCount();
	int fuelCount = data.pOM->GetFuelCount();
	WEVec2 click;
	WEInput::GetMouse(click);


	if (WEIntersection::PointRect(click, pButton[0].pos,
		pButton[0].scale.x, pButton[0].scale.y))
	{
		pButton[0].texture = data.TextureData.planetPTexture;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (planetCount < data.custom_max_planet)
			{
				data.pOM->SetPlanet(click,// { 831.0f, 290.0f },
				{ DEFAULT_SIZE_PLANET,DEFAULT_SIZE_PLANET }, 100, 100, data.TextureData.planetTexture, planetCount, PLANET_LIFE);
				data.pOM->SetPlanetEdge(click,
				{ 100,100 },
					data.TextureData.edgeTexture,
					planetCount);

				data.pOM->IncPlanetCount();
				data.max_planets++;
			}
		}
	}
	else
		pButton[0].texture = data.TextureData.planetTexture;

	if (WEIntersection::PointRect(click, pButton[1].pos,
		pButton[1].scale.x, pButton[1].scale.y))
	{
			pButton[1].texture = data.TextureData.asteroidPTexture;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				if (asteroidCount < data.custom_max_asteroid)
				{
				data.pOM->SetAsteroid(click, //{ 831.0f, 290.0f },
				{ DEFAULT_SIZE_ASTEROID,DEFAULT_SIZE_ASTEROID }, { 0,0 }, 0, data.TextureData.asteroidTexture, asteroidCount);

				data.pOM->IncAsteroidCount();
				data.max_asteroid++;
				}
			}
	}
	else
		pButton[1].texture = data.TextureData.asteroidTexture;


	if (WEIntersection::PointRect(click, pButton[2].pos,
		pButton[2].scale.x, pButton[2].scale.y))
	{
			pButton[2].texture = data.TextureData.FuelPTexture;
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				if (fuelCount < data.custom_max_fuel)
				{
				data.pOM->SetFuel(click,
				{ DEFAULT_SIZE_FUEL, DEFAULT_SIZE_FUEL }, { 0,0 }, 0, data.TextureData.FuelTexture, fuelCount);

				data.pOM->IncFuelCount();
				data.max_fuel++;
				}
			}
	}
	else
		pButton[2].texture = data.TextureData.FuelTexture;
}


void PressEditSave(Button *pButton, ReturnData &data, float &timer, Planet *pPlanet, Asteroid *pAsteroid, Object *pFuel)
{

	WEVec2 click;
	WEInput::GetMouse(click);


	if (WEIntersection::PointRect(click, pButton[0].pos,
		pButton[0].scale.x, pButton[0].scale.y))
	{
		pButton[0].texture = data.TextureData.SaveIconPTexture;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			//save action
			timer = 1;
			switch (data.level)
			{
			case 101:
			{
				PlanetSaveFile("LevelData/planet101.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid101.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel101.txt", pFuel, data);
				break;
			}
			case 102:
			{
				PlanetSaveFile("LevelData/planet102.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid102.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel102.txt", pFuel, data);
				break;
			}
			case 103:
			{
				PlanetSaveFile("LevelData/planet103.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroid103.txt", pAsteroid, data);
				FuelSaveFile("LevelData/fuel103.txt", pFuel, data);
				break;
			}
			default:
			{
				PlanetSaveFile("LevelData/planetdefault.txt", pPlanet, data);
				AsteroidSaveFile("LevelData/Asteroiddefault.txt", pAsteroid, data);
			}
			}
		}
	}
	else
		pButton[0].texture = data.TextureData.SaveIconTexture;



	if (WEIntersection::PointRect(click, pButton[1].pos,
		pButton[1].scale.x, pButton[1].scale.y))
	{
		pButton[1].texture = data.TextureData.EditIconPTexture;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (data.editmode == false)	data.editmode = true;
			else data.editmode = false;
		}
	}
	else
		pButton[1].texture = data.TextureData.EditIconTexture;

}

//hud action
void PressButton(Button *pButton, ReturnData &data)
{

	WEVec2 click;
	WEInput::GetMouse(click);
	if (WEIntersection::PointRect(click, pButton[0].pos,
		pButton[0].scale.x, pButton[0].scale.y))
	{
		pButton[0].texture = data.TextureData.pmenu;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			if (data.game_mode == CUSTOMMODE)
				WEStateManager::SetNextState(DS_CUSTOMINTRO);
			else if (data.game_mode == STORY)
				WEStateManager::SetNextState(DS_STROYINTRO);
			else Go_Menu();
		}
	}
	else
		pButton[0].texture = data.TextureData.menuTexture;
	//Replay
	if (WEIntersection::PointRect(click, pButton[1].pos,
		pButton[1].scale.x, pButton[1].scale.y))
	{
		pButton[1].texture = data.TextureData.preplay;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			data.life_count += 1;
			Replay();
		}
	}
	else
		pButton[1].texture = data.TextureData.replayTexture;

}

void BoostGaugeUpdate(Button *pBoost, Ship *pShip)
{
	pBoost[ONLY].scale.y = (pShip[ONLY].boostGauge * 12.f);
}
void AD_BoostGaugeUpdate(Button *pBoost, Ship *pShip)
{
	pBoost[ONLY].scale.y = (pShip[ONLY].boostGauge * 2.f);
}

void DrawHud(Button *pButton)
{
	WEMtx44 tranform;
	//button draw
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		WEGraphics::SetTexture(pButton[i].texture);
		WEMtx44::MakeTransform(tranform,
			pButton[i].scale.x,
			pButton[i].scale.y,
			0,
			pButton[i].pos.x,
			pButton[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}
void DrawEditObjects(Button *pButton)
{
	WEMtx44 tranform;
	//button draw
	for (int i = 0; i < EDITOBJECTS_BUTTONS; i++)
	{
		WEGraphics::SetTexture(pButton[i].texture);
		WEMtx44::MakeTransform(tranform,
			pButton[i].scale.x,
			pButton[i].scale.y,
			0,
			pButton[i].pos.x,
			pButton[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}


void DrawEditSave(Button *pButton)
{
	WEMtx44 tranform;
	//button draw
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		WEGraphics::SetTexture(pButton[i].texture);
		WEMtx44::MakeTransform(tranform,
			pButton[i].scale.x,
			pButton[i].scale.y,
			0,
			pButton[i].pos.x,
			pButton[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

void DrawEditMouse(Button *pButton)
{
	WEMtx44 tranform;
	//button draw
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		WEGraphics::SetTexture(pButton[i].texture);
		WEMtx44::MakeTransform(tranform,
			pButton[i].scale.x,
			pButton[i].scale.y,
			0,
			pButton[i].pos.x,
			pButton[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

void DrawBoostHud(Button *pBoost)
{
	WEMtx44 tranform;
	WEGraphics::SetTexture(pBoost[ONLY].texture);
	WEGraphics::SetTextureColor((unsigned char)255, (unsigned char)(pBoost[ONLY].scale.y/5), (unsigned char)10, (unsigned char)242);
	WEMtx44::MakeTransform(tranform,
		pBoost[ONLY].scale.x,
		pBoost[ONLY].scale.y,
		0,
		pBoost[ONLY].pos.x,
		pBoost[ONLY].pos.y,
		0);
	WEGraphics::Draw(tranform);
}

void DrawHelpHud(ReturnData &data, float dt, float &timer, Ship *pShip)
{
	WEMtx44 tranform;
	if (data.level ==1)
	   WEGraphics::SetTexture(data.TextureData.DragTheSpaceship);
	if (data.level == 2)
		WEGraphics::SetTexture(data.TextureData.ZoomText);
	if (data.level == 3)
		WEGraphics::SetTexture(data.TextureData.RestartText);
	if (data.level == 5)
		WEGraphics::SetTexture(data.TextureData.BoosterText);
	if (data.level == 6)
		WEGraphics::SetTexture(data.TextureData.RotationText);
	

	WEMtx44::MakeTransform(tranform, 256, 64, 0, 200, 500, 0);
	if (data.level == 1 || data.level == 2 || data.level == 3 || data.level == 5)
	{
		if (timer > 0)
		{
			WEGraphics::Draw(tranform);
			timer -= dt;
		}
	}
	if (data.level == 6)
	{
		if (timer > 0 && pShip->shiptype == SHIP_SHOOTED)
		{
			WEGraphics::Draw(tranform);
			timer -= dt;
		}
	}
}


void DrawBoostEdge(ReturnData &data)
{
	WEMtx44 transform;
	WEGraphics::SetTexture(data.TextureData.BoostEdgeTexture);
	WEMtx44::MakeTransform(transform,
		64.f,
		620.f,
		0.0f,
		22.f,
		290.f,
		0.0f);
	WEGraphics::Draw(transform);
}

void DrawBoostIcon(ReturnData &data)
{
	WEMtx44 transform;
	WEGraphics::SetTexture(data.TextureData.FuelTexture);
	WEMtx44::MakeTransform(transform,
		64.f,
		64.f,
		30.0f,
		30.f,
		630.f,
		0.0f);
	WEGraphics::Draw(transform);
}

void DrawLeveltext(ReturnData &data)
{
	WEMtx44 transform;
	if(data.game_mode == CUSTOMMODE)
		WEGraphics::SetTexture(data.TextureData.slotText);
	else
	WEGraphics::SetTexture(data.TextureData.leveltext);
	WEMtx44::MakeTransform(transform,
		64.f,
		20.f,
		0.0f,
		600.f,
		680.f,
		0.0f);
	WEGraphics::Draw(transform);
}
void DrawTrytext(ReturnData &data)
{
	WEMtx44 transform;
	WEGraphics::SetTexture(data.TextureData.trytext);
	WEMtx44::MakeTransform(transform,
		64.f,
		20.f,
		0.0f,
		600,
		640.f,
		0.0f);
	WEGraphics::Draw(transform);
}

void DrawPause(ReturnData &data)
{
	if (data.editmode == true)
	{
		WEMtx44 transform;
		WEGraphics::SetTexture(data.TextureData.pausetext);
		WEMtx44::MakeTransform(transform,
			128.f,
			32.f,
			0.0f,
			640.f,
			600.f,
			0.0f);
		WEGraphics::Draw(transform);
	}
}

void DrawEditOn(ReturnData &data)
{
	if (data.editmode == true)
	{
		WEMtx44 transform;
		WEGraphics::SetTexture(data.TextureData.EditOnTexture);
		WEMtx44::MakeTransform(transform,
			128.f,
			32.f,
			0.0f,
			640.f,
			600.f,
			0.0f);
		WEGraphics::Draw(transform);
	}
}

void DrawLevelNumber(ReturnData &data)
{
	//decimal
	int decimal_number = (data.level % 100) / 10;
	int decimal_texture = 0;

	if (decimal_number == 0)
		decimal_texture = data.TextureData.number0Texture;
	else if (decimal_number == 1)
		decimal_texture = data.TextureData.number1Texture;
	else if (decimal_number == 2)
		decimal_texture = data.TextureData.number2Texture;
	else if (decimal_number == 3)
		decimal_texture = data.TextureData.number3Texture;
	else if (decimal_number == 4)
		decimal_texture = data.TextureData.number4Texture;
	else if (decimal_number == 5)
		decimal_texture = data.TextureData.number5Texture;
	else if (decimal_number == 6)
		decimal_texture = data.TextureData.number6Texture;
	else if (decimal_number == 7)
		decimal_texture = data.TextureData.number7Texture;
	else if (decimal_number == 8)
		decimal_texture = data.TextureData.number8Texture;
	else if (decimal_number == 9)
		decimal_texture = data.TextureData.number9Texture;

	//digit
	int digit_number = data.level % 10;
	int digit_texture = 0;


	if (digit_number == 0)
		digit_texture = data.TextureData.number0Texture;
	else if (digit_number == 1)
		digit_texture = data.TextureData.number1Texture;
	else if (digit_number == 2)
		digit_texture = data.TextureData.number2Texture;
	else if (digit_number == 3)
		digit_texture = data.TextureData.number3Texture;
	else if (digit_number == 4)
		digit_texture = data.TextureData.number4Texture;
	else if (digit_number == 5)
		digit_texture = data.TextureData.number5Texture;
	else if (digit_number == 6)
		digit_texture = data.TextureData.number6Texture;
	else if (digit_number == 7)
		digit_texture = data.TextureData.number7Texture;
	else if (digit_number == 8)
		digit_texture = data.TextureData.number8Texture;
	else if (digit_number == 9)
		digit_texture = data.TextureData.number9Texture;
	WEMtx44 transform;

	//decimal
	WEGraphics::SetTexture(decimal_texture);
	WEMtx44::MakeTransform(transform,
		20.f,
		20.f,
		0.0f,
		680.f,
		680.f,
		0.0f);
	WEGraphics::Draw(transform);

	//digit
	WEGraphics::SetTexture(digit_texture);
	WEMtx44::MakeTransform(transform,
		20.f,
		20.f,
		0.0f,
		700.f,
		680.f,
		0.0f);
	WEGraphics::Draw(transform);

}


void DrawTryNumber(ReturnData &data)
{

	//centesimal
	int centesimal_number = (data.life_count % 1000) / 100;
	int centesimal_texture = 0;
	
	if (centesimal_number == 0)
		centesimal_texture = data.TextureData.number0Texture;
	else if (centesimal_number == 1)
		centesimal_texture = data.TextureData.number1Texture;
	else if (centesimal_number == 2)
		centesimal_texture = data.TextureData.number2Texture;
	else if (centesimal_number == 3)
		centesimal_texture = data.TextureData.number3Texture;
	else if (centesimal_number == 4)
		centesimal_texture = data.TextureData.number4Texture;
	else if (centesimal_number == 5)
		centesimal_texture = data.TextureData.number5Texture;
	else if (centesimal_number == 6)
		centesimal_texture = data.TextureData.number6Texture;
	else if (centesimal_number == 7)
		centesimal_texture = data.TextureData.number7Texture;
	else if (centesimal_number == 8)
		centesimal_texture = data.TextureData.number8Texture;
	else if (centesimal_number == 9)
		centesimal_texture = data.TextureData.number9Texture;

	//decimal
	int decimal_number = (data.life_count % 100) / 10;
	int decimal_texture = 0;

	if (decimal_number == 0)
		decimal_texture = data.TextureData.number0Texture;
	else if (decimal_number == 1)
		decimal_texture = data.TextureData.number1Texture;
	else if (decimal_number == 2)
		decimal_texture = data.TextureData.number2Texture;
	else if (decimal_number == 3)
		decimal_texture = data.TextureData.number3Texture;
	else if (decimal_number == 4)
		decimal_texture = data.TextureData.number4Texture;
	else if (decimal_number == 5)
		decimal_texture = data.TextureData.number5Texture;
	else if (decimal_number == 6)
		decimal_texture = data.TextureData.number6Texture;
	else if (decimal_number == 7)
		decimal_texture = data.TextureData.number7Texture;
	else if (decimal_number == 8)
		decimal_texture = data.TextureData.number8Texture;
	else if (decimal_number == 9)
		decimal_texture = data.TextureData.number9Texture;

	//digit
	int digit_number = data.life_count % 10;
	int digit_texture = 0;

	if (digit_number == 0)
		digit_texture = data.TextureData.number0Texture;
	else if (digit_number == 1)
		digit_texture = data.TextureData.number1Texture;
	else if (digit_number == 2)
		digit_texture = data.TextureData.number2Texture;
	else if (digit_number == 3)
		digit_texture = data.TextureData.number3Texture;
	else if (digit_number == 4)
		digit_texture = data.TextureData.number4Texture;
	else if (digit_number == 5)
		digit_texture = data.TextureData.number5Texture;
	else if (digit_number == 6)
		digit_texture = data.TextureData.number6Texture;
	else if (digit_number == 7)
		digit_texture = data.TextureData.number7Texture;
	else if (digit_number == 8)
		digit_texture = data.TextureData.number8Texture;
	else if (digit_number == 9)
		digit_texture = data.TextureData.number9Texture;

	WEMtx44 transform;
	//centesimal
	WEGraphics::SetTexture(centesimal_texture);
	WEMtx44::MakeTransform(transform,
		20.f,
		20.f,
		0.0f,
		660.f,
		640.f,
		0.0f);
	WEGraphics::Draw(transform);

	//decimal
	WEGraphics::SetTexture(decimal_texture);
	WEMtx44::MakeTransform(transform,
		20.f,
		20.f,
		0.0f,
		680.f,
		640.f,
		0.0f);
	WEGraphics::Draw(transform);

	//digit
	WEGraphics::SetTexture(digit_texture);
	WEMtx44::MakeTransform(transform,
		20.f,
		20.f,
		0.0f,
		700.f,
		640.f,
		0.0f);
	WEGraphics::Draw(transform);

}


void DrawIntroNumber(ReturnData &returndata)
{

	for (int i = 1; i <= MAX_LEVEL; ++i)
	{
		int decimal_number = i / 10;
		int decimal_texture = 0;
		if (decimal_number == 0)
			decimal_texture = returndata.TextureData.number0Texture;
		else if (decimal_number == 1)
			decimal_texture = returndata.TextureData.number1Texture;
		else if (decimal_number == 2)
			decimal_texture = returndata.TextureData.number2Texture;
		else if (decimal_number == 3)
			decimal_texture = returndata.TextureData.number3Texture;
		else if (decimal_number == 4)
			decimal_texture = returndata.TextureData.number4Texture;
		else if (decimal_number == 5)
			decimal_texture = returndata.TextureData.number5Texture;
		else if (decimal_number == 6)
			decimal_texture = returndata.TextureData.number6Texture;
		else if (decimal_number == 7)
			decimal_texture = returndata.TextureData.number7Texture;
		else if (decimal_number == 8)
			decimal_texture = returndata.TextureData.number8Texture;
		else if (decimal_number == 9)
			decimal_texture = returndata.TextureData.number9Texture;


		//digit
		int digit_number = i % 10;
		int digit_texture = 0;


		if (digit_number == 0)
			digit_texture = returndata.TextureData.number0Texture;
		else if (digit_number == 1)
			digit_texture = returndata.TextureData.number1Texture;
		else if (digit_number == 2)
			digit_texture = returndata.TextureData.number2Texture;
		else if (digit_number == 3)
			digit_texture = returndata.TextureData.number3Texture;
		else if (digit_number == 4)
			digit_texture = returndata.TextureData.number4Texture;
		else if (digit_number == 5)
			digit_texture = returndata.TextureData.number5Texture;
		else if (digit_number == 6)
			digit_texture = returndata.TextureData.number6Texture;
		else if (digit_number == 7)
			digit_texture = returndata.TextureData.number7Texture;
		else if (digit_number == 8)
			digit_texture = returndata.TextureData.number8Texture;
		else if (digit_number == 9)
			digit_texture = returndata.TextureData.number9Texture;

		WEMtx44 transform;

		//decimal

		WEGraphics::SetTexture(decimal_texture);
		WEMtx44::MakeTransform(transform,
			20.f,
			20.f,
			0.0f,
			-10.f + i * TERM,
			300.f,
			0.0f);
		WEGraphics::Draw(transform);

		WEGraphics::SetTexture(digit_texture);
		WEMtx44::MakeTransform(transform,
			20.f,
			20.f,
			0.0f,
			10.f + TERM * i,
			300.f,
			0.0f);
		WEGraphics::Draw(transform);
	}
}

void DrawEditExplain(ReturnData &data)
{
	WEMtx44 tranform;
	//button draw
	if (data.explain_button == MOVE)
	{
		WEGraphics::SetTexture(data.TextureData.explain1Texture);
		WEMtx44::MakeTransform(tranform,
			256,
			64.f,
			0,
			940.f,
			670.f,
			0);
		WEGraphics::Draw(tranform);
	}
	else if (data.explain_button == MAGIC)
	{
		WEGraphics::SetTexture(data.TextureData.explain2Texture);
		WEMtx44::MakeTransform(tranform,
			256,
			64.f,
			0,
			940.f,
			670.f,
			0);
		WEGraphics::Draw(tranform);
	}

}


void DrawLevelSel(int texture)
{
	WEMtx44 tranform;
	//button draw
		WEGraphics::SetTexture(texture);
		WEMtx44::MakeTransform(tranform,
			512.f,
			64.f,
			0,
			640.f,
			600.f,
			0);
		WEGraphics::Draw(tranform);
}