/******************************************************************************
\file	SpaceShip.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "SpaceShip.h"
#include <cmath>
#include "Objects.h"


// about ship update
void InitShip(ReturnData &data)
{
	Ship spaceship;

		spaceship.texture = data.TextureData.shipTexture;
		spaceship.pos.x = POSITION_SHIP_X;
		spaceship.pos.y = POSITION_SHIP_Y;
		spaceship.scale.x = SIZE_SHIP_X;
		spaceship.scale.y = SIZE_SHIP_Y;
		spaceship.vel.x = 0;
		spaceship.vel.y = 0;
		spaceship.angle = 0;
		spaceship.power = 0;
		spaceship.distance = 0;
		spaceship.mass = 10;
		spaceship.boostGauge = FULL_BOOST;
		spaceship.shiptype = SHIP_STANDBY;
		spaceship.shiplife = SHIP_LIVE;


		data.pOM->SetShip(spaceship.pos, spaceship.scale, spaceship.vel, spaceship.power,
			spaceship.distance,	spaceship.angle, spaceship.mass, spaceship.boostGauge, spaceship.texture,
		spaceship.shiptype, spaceship.shiplife);
	
}
void AD_InitShip(ReturnData &data)
{

	Ship spaceship;

	spaceship.texture = data.TextureData.shipTexture;
	spaceship.pos.x = data.screenWidth/2;
	spaceship.pos.y = data.screenHeight/2;
	spaceship.scale.x = SIZE_SHIP_X;
	spaceship.scale.y = SIZE_SHIP_Y;
	spaceship.vel.x = 0;
	spaceship.vel.y = 0;
	spaceship.angle = 0;
	spaceship.power = 0;
	spaceship.distance = 0;
	spaceship.mass = 10;
	spaceship.boostGauge = AD_FULL_BOOST;
	spaceship.shiptype = SHIP_STANDBY;
	spaceship.shiplife = SHIP_LIVE;


	data.pOM->SetShip(spaceship.pos, spaceship.scale, spaceship.vel, spaceship.power,
		spaceship.distance, spaceship.angle, spaceship.mass, spaceship.boostGauge, spaceship.texture,
		spaceship.shiptype, spaceship.shiplife);

}


void ShipMovement(Ship* pShip, float dt)
{
	//default velocity
	pShip->pos += pShip->vel * dt * 2;

}

void Planet_Gravity_Colision(Ship* pShip, Planet* pPlanet, Edge* pEdge, ReturnData &data, Particle *pCrash, ParticleManager *pPM, float dt, float &time)
{
	for (int i = 0; i < data.max_planets; ++i)
	{
		//take gravity
		if (Distance_planet_edge(pShip, pEdge + i) < Collision_planet_edge(pShip, pEdge + i) * 0.7f)
		{
			ActionPlanet(pShip, pPlanet + i, dt);
		}

		//crash
		if (Distance_planet(pShip, pPlanet + i) <= Collision_planet(pShip, pPlanet + i) * 0.6)
		{
			changePlanetTexture(pPlanet + i, data, time);
			pPM->InitCrashing(pCrash, pShip);
			//Restart
			Crash_Restart(data);
			if (pPlanet[i].life >= 2)
			SoundManager::sharedManager()->play(EXPLOSION);
		}
		if (pPlanet[i].life < 2 && time > 1.5)
		{
			pPlanet[i].texture = data.TextureData.EggSleepTexture;
			pPlanet[i].life  = 2;
		}

		time += dt;
	}

}
void ByeBteShip(Ship* pShip, ReturnData &data, Particle *pByebye, ParticleManager *pPM)
{
	if (pShip[ONLY].pos.x > RIGHT_MAX || pShip[ONLY].pos.x < LEFT_MAX)
	{
		//Restart
		pPM->InitByebye(pByebye, pShip);
		SoundManager::sharedManager()->play(RESTART);
		Crash_Restart(data);
	}
	if (pShip[ONLY].pos.y > TOP_MAX || pShip[ONLY].pos.y < BOTTOM_MAX)
	{
		//Restart
		pPM->InitByebye(pByebye, pShip);
		SoundManager::sharedManager()->play(RESTART);
		Crash_Restart(data);
	}
}
void AD_ByeBteShip(Ship* pShip, ReturnData &data, Particle *pByebye, ParticleManager *pPM)
{
	if (pShip[ONLY].pos.x > AD_RIGHT || pShip[ONLY].pos.x < AD_LEFT)
	{
		//Restart
		pPM->InitByebye(pByebye, pShip);
		SoundManager::sharedManager()->play(RESTART);
		Crash_Restart(data);
	}

	if (pShip[ONLY].pos.y > AD_TOP || pShip[ONLY].pos.y < AD_BOTTOM)
	{
		//Restart
		pPM->InitByebye(pByebye, pShip);
		SoundManager::sharedManager()->play(RESTART);
		Crash_Restart(data);
	}
}

void Asteroid_Collision(Ship* pShip, Asteroid *pAs, ReturnData &data, Particle *pCrash, ParticleManager *pPM)
{
	for (int i = 0; i < data.max_asteroid; ++i)
	{
		if (Distance_asteroid(pShip, pAs + i) <= Collision_asteroid(pShip, pAs + i) * 0.7 && pShip->shiptype== SHIP_SHOOTED)
		{
			pPM->InitCrashing(pCrash, pShip);
			//Restart
			SoundManager::sharedManager()->play(EXPLOSION);
			Crash_Restart(data);
		}
	}
}

//when stage clear
void ArriveGoal(Ship* pShip, Goal * pGoal, ReturnData &data)
{
	//goal
	if (Distance_goal(pShip, pGoal) <= Collision_goal(pShip, pGoal) * 0.9 )
	{
		if (data.game_mode == CUSTOMMODE)
		{
			SoundManager::sharedManager()->play(GOAL);
			WEStateManager::Restart();
		}
		else if (data.game_mode == STORY)
		{
			//level 0 is adventure
			if (data.level == MAX_LEVEL || data.level == 0)
			{
				WEStateManager::SetNextState(DS_THANK);
			}
			if (pShip->shiplife == SHIP_LIVE && data.level != MAX_LEVEL && data.level != 0)
			{
				++data.level;
				SoundManager::sharedManager()->play(GOAL);
				WEStateManager::Restart();
			}
		}
		else if (data.game_mode == ADVENTURE)
			WEStateManager::SetNextState(DS_THANK);
		else
			WEStateManager::Restart();


	}

}

//Control the ship only auto or keyboard
void AngleOfShip(Ship* pShip, Object* pMark)
{
	WEVec2 mousep;
	WEInput::GetMouse(mousep);
	WEGraphics::ConvertScreenToWorld(mousep.x, mousep.y);
	//set spaceship's angle 
	if ( pShip->shiptype == SHIP_PULL)
		Before_Launch_Angle(pShip, pMark);
	else if (pShip->shiptype == SHIP_SHOOTED)
	{
		if (WEInput::IsPressed(WE_MOUSE_RIGHT))
		{
			After_Launch_Angle(pShip, &mousep);
		}
	}
	//Shiptype == standby
	else
		pShip->angle = 0;
}

void MarkPosition(Ship* pShip, Object* pMark)
{
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
	if (pShip->shiptype == SHIP_PULL)
	{
		pMark[ONLY].pos.x = -mouse.x + pShip[ONLY].pos.x * 2;
		pMark[ONLY].pos.y = -mouse.y + pShip[ONLY].pos.y * 2;
	}
	else
	{
		//go away!
		pMark[ONLY].pos.x = GO_AWAY;
		pMark[ONLY].pos.y = GO_AWAY;
	}
}

void LaunchShip(Ship *pShip)
{
	WEVec2 click;
	WEInput::GetMouse(click);
	WEGraphics::ConvertScreenToWorld(click.x, click.y);
	if (WEIntersection::PointRect(click, pShip->pos,
		pShip->scale.x, pShip->scale.y))
	{
		//ship pull
		if (WEInput::IsPressed(WE_MOUSE_LEFT) && pShip->shiptype == SHIP_STANDBY)
		{
			pShip->shiptype = SHIP_PULL;
		}//pressed mouse left

		}	
		if (WEInput::IsPressed(WE_MOUSE_RIGHT) && pShip->shiptype == SHIP_PULL)
		{
			pShip->shiptype = SHIP_STANDBY;
		}
	//shoot ship
	if (WEInput::IsPressed(WE_MOUSE_LEFT) != true && pShip->shiptype == SHIP_PULL)
	{
		pShip->shiptype = SHIP_SHOOTED;
		
		//Object* 
		WEVec2 mouse;
		WEInput::GetMouse(mouse);
		WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
		if (DistanceMouseWithShip(mouse, pShip) > 200)
		{
			pShip->vel.x = 200 * (pShip->pos.x - mouse.x) / DistanceMouseWithShip(mouse, pShip);
			pShip->vel.y = 200 * (pShip->pos.y - mouse.y) / DistanceMouseWithShip(mouse, pShip);
		}
		else
		{
			pShip->vel = pShip->pos - mouse;
		}
	}
}
void LaunchHudLogic(Ship* pShip, Object* pLaunch)
{
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
	if (pShip->shiptype == SHIP_PULL)
	{
		pLaunch[ONLY].pos.x = pShip->pos.x;
		pLaunch[ONLY].pos.y = pShip->pos.y;
		pLaunch[ONLY].vel.x = sqrt(pow(-mouse.x + pShip[ONLY].pos.x, 2) - cos(pLaunch[ONLY].angle) * 25
							+ pow(-mouse.y + pShip[ONLY].pos.y, 2) - sin(pLaunch[ONLY].angle) * 25) * 2;
		pLaunch[ONLY].angle = pShip[ONLY].angle;
		
		if (pLaunch[ONLY].vel.x < 400)
		{
			pLaunch[ONLY].scale.x = sqrt(pow(-mouse.x + pShip[ONLY].pos.x, 2) - cos(pLaunch[ONLY].angle) * 25
				+ pow(-mouse.y + pShip[ONLY].pos.y, 2) - sin(pLaunch[ONLY].angle) * 25) * 2;
		}
							

		pLaunch[ONLY].scale.y = 20; 
	}

	else
	{
		pLaunch[ONLY].scale.x = 0;
		pLaunch[ONLY].scale.y = 0;
	}

}

void BoosterShip(Ship *pShip, Particle *pBooster, ParticleManager *pPM, float dt, ReturnData &data)
{
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	if (pShip->boostGauge > 0)
	{
		if (WEInput::IsTriggered(WE_MOUSE_LEFT) && pShip->shiptype == SHIP_SHOOTED)
		{
			data.boostfire = true;
			pPM->InitBoosting(pBooster, pShip);
			SoundManager::sharedManager()->stop(BOOST);
			SoundManager::sharedManager()->play(BOOST);
		}
		else
		{
			data.boostfire = false;
		}
		if (WEInput::IsPressed(WE_MOUSE_LEFT) && pShip->shiptype == SHIP_SHOOTED)
		{
			data.boostfire = true;
			pPM->PooozicBoosting(pBooster, pShip, dt, data);
			pShip->vel.x += 2 * cos(pShip->angle);
			pShip->vel.y += 2 * sin(pShip->angle);
			pShip->boostGauge--;
		}
	}
	else
		data.boostfire = false;

}

void DrawShip(Ship *pShip,ReturnData &data)
{
	WEMtx44 tranform;
	WEGraphics::SetTexture(data.TextureData.shipTexture);
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
	WEMtx44::MakeTransform(tranform,
		pShip->scale.x,
		pShip->scale.y,
		pShip->angle,
		pShip->pos.x,
		pShip->pos.y,
		0);

	WEGraphics::Draw(tranform);
}

void Crash_Restart(ReturnData &data)
{
	if (data.game_mode == STORY)
	{
		data.life_count += 1;
		data.cameraZ = DEFAULT_CAMERA_Z;
		InitShip(data);
		InitFuel(data);
		data.camera_time = 0;
	}
	else if (data.game_mode == ADVENTURE)
	{
		AD_InitShip(data);
		AD_InitFuel(data);
	}
	else if (data.game_mode == CUSTOMMODE)
	{
		data.life_count += 1;
		data.cameraZ = DEFAULT_CAMERA_Z;
		InitShip(data);
		CT_InitFuel(data);
	}
	else
	{
		data.cameraZ = DEFAULT_CAMERA_Z;
		InitShip(data);
		InitFuel(data);
	}
}


void Fuel_Collision(Ship *pShip, Object *pFuel, ReturnData &data)
{
	for (int i = 0; i < data.max_fuel; ++i)
	{
		if (Distance_fuel(pShip, pFuel + i) <= Collision_fuel(pShip, pFuel + i) * 0.8 && pShip->shiptype == SHIP_SHOOTED)
		{
			if (data.game_mode == ADVENTURE)
				AD_FillFuel(pFuel + i, pShip);
			else //mode is 	STORY, CUSTOMPLAY, CUSTOMEDIT
				FillFuel(pFuel + i, pShip);
		}
	}
}