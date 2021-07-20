/******************************************************************************
\file	Object.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Objects.h"
#include "SpaceShip.h" //for map size
#include <string>

//Object Movement
void ObjectMovement(Asteroid* pAsteroid, float dt, ObjectManager* pOM)
{
	//default velocity
	int asteroidCount = pOM->GetAsteroidCount();
		for (int i = 0; i < asteroidCount; i++)
			pAsteroid[i].pos += pAsteroid[i].vel * dt * 2;
	

}

//Init Functions
void InitMark(ReturnData &data)
{

	data.pOM->GetMark();
	Ship* pShip = data.pOM->GetShip();
	
	Object mark;
		mark.texture = data.TextureData.markTexture;
		mark.pos.x = pShip->pos.x;
		mark.pos.y = pShip->pos.y;
		mark.scale.x = DEFAULT_SIZE_50;
		mark.scale.y = DEFAULT_SIZE_50;
		mark.vel.x = ZERO;
		mark.vel.y = ZERO;
		mark.angle = ZERO;

		data.pOM->SetMark(mark.pos, mark.scale, mark.vel, mark.angle, mark.texture);

}
void InitLaunch(ReturnData &data)
{

	data.pOM->GetLaunch();
	Ship* pShip = data.pOM->GetShip();
	Object launch;
	launch.texture = data.TextureData.launchTexture;
	launch.pos.x = pShip->pos.x;
	launch.pos.y = pShip->pos.y;
	launch.scale.x = ZERO;
	launch.scale.y = ZERO;
	launch.vel.x = ZERO;
	launch.vel.y = ZERO;

	data.pOM->SetLaunch(launch.pos, launch.scale, launch.vel, 0, launch.texture);

}

void InitGoal(ReturnData &data)
{

	data.pOM->GetGoal();
	Goal goal;
	goal.texture = data.TextureData.goalTexture;
	goal.pos.x = 1166.f;
	goal.pos.y = 580.f;
	goal.scale.x = 100;
	goal.scale.y = 100;

	data.pOM->SetGoal(goal.pos, goal.scale, goal.texture);
}

void AD_InitGoal(ReturnData &data)
{

	data.pOM->GetGoal();
	Goal goal;
	goal.texture = data.TextureData.goalTexture;
	goal.pos.x = WERandom::GetFloat(0.9*AD_LEFT, 0.9*AD_RIGHT);
	goal.pos.y = WERandom::GetFloat(0.9*AD_BOTTOM, 0.9*AD_TOP);
	while((goal.pos.x > AD_LEFT/2 && goal.pos.x < AD_RIGHT/2)&&
		(  goal.pos.y < AD_TOP/2  && goal.pos.y > AD_BOTTOM/2))
	{
		goal.pos.x = WERandom::GetFloat(0.9*AD_LEFT, 0.9*AD_RIGHT);
		goal.pos.y = WERandom::GetFloat(0.9*AD_BOTTOM, 0.9*AD_TOP);
	}
	goal.scale.x = 100;
	goal.scale.y = 100;

	data.pOM->SetGoal(goal.pos, goal.scale, goal.texture);
}//ad_initgoal

void InitAsteroid(ReturnData &data)
{
	data.pOM->GetAsteroid();
	//need file i/o
	switch (data.level)
	{
		case 1:
		{
			AsteroidLoadFile("LevelData/asteroid1.txt", data);
			break;
		}
		case 2:
		{
			AsteroidLoadFile("LevelData/asteroid2.txt", data);
			break;
		}
		case 3:
		{
			AsteroidLoadFile("LevelData/asteroid3.txt", data);
			break;
		}
		case 4:
		{
			AsteroidLoadFile("LevelData/asteroid4.txt", data);
			break;
		}
		case 5:
		{
			AsteroidLoadFile("LevelData/asteroid5.txt", data);
			break;
		}
		case 6:
		{
			AsteroidLoadFile("LevelData/asteroid6.txt", data);
			break;
		}
		case 7:
		{
			AsteroidLoadFile("LevelData/asteroid7.txt", data);
			break;
		}
		case 8:
		{
			AsteroidLoadFile("LevelData/asteroid8.txt", data);
			break;
		}
		case 9:
		{
			AsteroidLoadFile("LevelData/asteroid9.txt", data);
			break;
		}
		case 10:
		{
			AsteroidLoadFile("LevelData/asteroid10.txt", data);
			break;
		}
		case 11:
		{
			AsteroidLoadFile("LevelData/asteroid11.txt", data);
			break;
		}
		case 12:
		{
			AsteroidLoadFile("LevelData/asteroid12.txt", data);
			break;
		}
		case 13:
		{
			AsteroidLoadFile("LevelData/asteroid13.txt", data);
			break;
		}
		case 14:
		{
			AsteroidLoadFile("LevelData/asteroid14.txt", data);
			break;
		}
		case 15:
		{
			AsteroidLoadFile("LevelData/asteroid15.txt", data);
			break;
		}
		default: AsteroidLoadFile("LevelData/asteroid_default.txt", data);
	}//switch
}//init asteroid

void AD_InitAsteroid(ReturnData &data)
{
	data.pOM->GetAsteroid();

	Asteroid asteroid;
	asteroid.texture = data.TextureData.asteroidTexture;
	int asteroidCount = data.max_asteroid;
	
	for (int asteroid_count = 0; asteroid_count < asteroidCount; ++asteroid_count)
	{
		asteroid.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
		asteroid.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		while ((asteroid.pos.x > 0 && asteroid.pos.x < AD_RIGHT  / 3) &&
			   (asteroid.pos.y < AD_TOP  / 3 && asteroid.pos.y > AD_BOTTOM / 3))
		{
			asteroid.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
			asteroid.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		}
		asteroid.scale.x = DEFAULT_SIZE_ASTEROID;
		asteroid.scale.y = DEFAULT_SIZE_ASTEROID;
		asteroid.vel.x = WERandom::GetFloat(-10, 10);
		asteroid.vel.y = WERandom::GetFloat(-10, 10);
		asteroid.rotate = 0;

		data.pOM->SetAsteroid(asteroid.pos, asteroid.scale, asteroid.vel, asteroid.rotate, asteroid.texture, asteroid_count);
		data.pOM->IncAsteroidCount();
	}//for

}//init asteroid


void CT_InitAsteroid(ReturnData &data)
{

	std::string path = getenv("USERPROFILE");
	path += "/My Documents/Return/";
	data.pOM->GetAsteroid();
	//need file i/o
	switch (data.level)
	{
	case 101:
	{
		AsteroidLoadFile(std::string(path + "LevelData/asteroid101.txt").c_str(), data);
		break;
	}
	case 102:
	{
		AsteroidLoadFile(std::string(path + "LevelData/asteroid102.txt").c_str(), data);
		break;
	}
	case 103:
	{
		AsteroidLoadFile(std::string(path + "LevelData/asteroid103.txt").c_str(), data);
		break;
	}
	default: AsteroidLoadFile(std::string(path + "LevelData/asteroid_default.txt").c_str(), data);
	}//switch
}//Custom asteroid


void CT_InitFuel(ReturnData &data)
{

	std::string path = getenv("USERPROFILE");
	path += "/My Documents/Return/";
	data.pOM->GetFuel();
	switch (data.level)
	{
	case 101:
	{
		FuelLoadFile(std::string(path + "LevelData/fuel101.txt").c_str(), data);
		break;
	}
	case 102:
	{
		FuelLoadFile(std::string(path + "LevelData/fuel102.txt").c_str(), data);
		break;
	}
	case 103:
	{
		FuelLoadFile(std::string(path + "LevelData/fuel103.txt").c_str(), data);
		break;
	}
	default: FuelLoadFile(std::string(path + "LevelData/fuel_default.txt").c_str(), data);
	}
}//custom init fuel


void DrawMark(Object *pMark)
{
	WEMtx44 tranform;
	//Mark draw
	WEGraphics::SetTexture(pMark->texture);
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
	WEMtx44::MakeTransform(tranform,
		pMark->scale.x,
		pMark->scale.y,
		0,
		pMark->pos.x,
		pMark->pos.y,
		0);
	WEGraphics::Draw(tranform);
}

void DrawLaunch(Object *pLaunch)
{
	WEMtx44 tranform;
	//launch HUD draw
	WEGraphics::SetTexture(pLaunch->texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(tranform,
		pLaunch->scale.x,
		pLaunch->scale.y,
		pLaunch->angle,
		pLaunch->pos.x,
		pLaunch->pos.y,
		0);
	WEGraphics::Draw(tranform);

}

void DrawGoal(Goal *pGoal)
{
	WEMtx44 tranform;
	//goal draw
	WEGraphics::SetTexture(pGoal->texture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(tranform,
		pGoal->scale.x,
		pGoal->scale.y,
		0,
		pGoal->pos.x,
		pGoal->pos.y,
		0);
	WEGraphics::Draw(tranform);
}

void DrawAsteroid(Asteroid *pAsteroid,ReturnData &data)
{
	WEMtx44 tranform;
	//asteroid draw
	for (int asteroid_count = 0; asteroid_count < data.max_asteroid; ++asteroid_count)
	{
		WEGraphics::SetTexture(pAsteroid[asteroid_count].texture);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(tranform,
			pAsteroid[asteroid_count].scale.x,
			pAsteroid[asteroid_count].scale.y,
			0,
			pAsteroid[asteroid_count].pos.x,
			pAsteroid[asteroid_count].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

//Asteroid durability
void AsteroidDurab(Asteroid* pAsteroid, ObjectManager* pOM)
{
	int asteroidCount = pOM->GetAsteroidCount();

	for (int i = 0; i < asteroidCount; i++)
	{
	
		if (pAsteroid[i].pos.x > XREND ||
			pAsteroid[i].pos.x < XLEND ||
			pAsteroid[i].pos.y > YUEND ||
			pAsteroid[i].pos.y < YDEND)
		{
			pAsteroid[i].vel.x *= -1;
			pAsteroid[i].vel.y *= -1;
		}
	}
}


void InitFuel(ReturnData &data)
{
	data.pOM->GetFuel();
	switch (data.level)
	{
	case 1:
	{
		FuelLoadFile("LevelData/fuel1.txt", data);
		break;
	}
	case 2:
	{
		FuelLoadFile("LevelData/fuel2.txt", data);
		break;
	}
	case 3:
	{
		FuelLoadFile("LevelData/fuel3.txt", data);
		break;
	}
	case 4:
	{
		FuelLoadFile("LevelData/fuel4.txt", data);
		break;
	}
	case 5:
	{
		FuelLoadFile("LevelData/fuel5.txt", data);
		break;
	}
	case 6:
	{
		FuelLoadFile("LevelData/fuel6.txt", data);
		break;
	}
	case 7:
	{
		FuelLoadFile("LevelData/fuel7.txt", data);
		break;
	}
	case 8:
	{
		FuelLoadFile("LevelData/fuel8.txt", data);
		break;
	}
	case 9:
	{
		FuelLoadFile("LevelData/fuel9.txt", data);
		break;
	}
	case 10:
	{
		FuelLoadFile("LevelData/fuel10.txt", data);
		break;
	}
	case 11:
	{
		FuelLoadFile("LevelData/fuel11.txt", data);
		break;
	}
	case 12:
	{
		FuelLoadFile("LevelData/fuel12.txt", data);
		break;
	}
	case 13:
	{
		FuelLoadFile("LevelData/fuel13.txt", data);
		break;
	}
	case 14:
	{
		FuelLoadFile("LevelData/fuel14.txt", data);
		break;
	}
	case 15:
	{
		FuelLoadFile("LevelData/fuel15.txt", data);
		break;
	}
	default: FuelLoadFile("LevelData/fuel_default.txt", data);
	}//switch
}


void AD_InitFuel(ReturnData &data)
{
	data.pOM->GetFuel();

	Object fuel;
	fuel.texture = data.TextureData.FuelTexture;

	for (int fuel_count = 0; fuel_count < data.max_fuel; ++fuel_count)
	{
		fuel.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
		fuel.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		while ((fuel.pos.x > 0 && fuel.pos.x < AD_RIGHT / 3) &&
			(fuel.pos.y < AD_TOP / 3 && fuel.pos.y > AD_BOTTOM / 3))
		{
			fuel.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
			fuel.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		}
		fuel.scale.x = DEFAULT_SIZE_FUEL;
		fuel.scale.y = DEFAULT_SIZE_FUEL;
		fuel.vel.x = 0;
		fuel.vel.y = 0;
		fuel.angle = 0;

		data.pOM->SetFuel(fuel.pos, fuel.scale, fuel.vel, fuel.angle, fuel.texture, fuel_count);
		data.pOM->IncFuelCount();
	}
}


void FillFuel(Object *pFuel, Ship *pShip)
{
	if (pFuel->angle <= BOOL_1)
	{
		if (pShip->boostGauge + FUEL_BOOST > FULL_BOOST)
		{
			pShip->boostGauge = FULL_BOOST;
			Have_Fuel(pFuel);
		}
		else // (pShip->boostGauge + FUEL_BOOST <= 100)
		{
			pShip->boostGauge += FUEL_BOOST;
			Have_Fuel(pFuel);
		}
	}
}

void AD_FillFuel(Object *pFuel, Ship *pShip)
{
	if (pFuel->angle <= BOOL_1)
	{
		if (pShip->boostGauge + AD_FUEL_BOOST > AD_FULL_BOOST)
		{
			pShip->boostGauge = AD_FULL_BOOST;
			Have_Fuel(pFuel);
		}
		else // (pShip->boostGauge + FUEL_BOOST <= 600)
		{
			pShip->boostGauge += AD_FUEL_BOOST;
			Have_Fuel(pFuel);
		}
	}
}

void Have_Fuel(Object *pFuel)
{
	pFuel->angle += BOOL_FUEL;
	pFuel->pos.x = GO_AWAY;
	pFuel->pos.y = GO_AWAY;
	pFuel->scale.x = ZERO;
	pFuel->scale.y = ZERO;
}

void DrawFuel(Object *pFuel, ReturnData &data)
{

	for (int fuel_count = 0; fuel_count < data.max_fuel; ++fuel_count)
	{

		WEMtx44 tranform;
		//launch HUD draw
		WEGraphics::SetTexture(pFuel[fuel_count].texture);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(tranform,
			pFuel[fuel_count].scale.x,
			pFuel[fuel_count].scale.y,
			0,
			pFuel[fuel_count].pos.x,
			pFuel[fuel_count].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}

}