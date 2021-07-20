/******************************************************************************
\file	Environment.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Environment.h"
#include "SpaceShip.h"
#include "Objects.h"

//Camera Z-axis control by wheel
void Camera_Z(ReturnData &data)
{
	//camera z order
	if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN))
	{
		if (data.cameraZ <= 600)
			data.cameraZ += 40;
	}
	if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_UP))
	{
		if (data.cameraZ >= 200)
			data.cameraZ -= 40;
	}
}

//All control by keyboard in environment
void KeyboardAct(ReturnData &data)
{
	if (WEInput::IsTriggered(WE_ESCAPE))
	{
		if (WEStateManager::GetCurrentState() == DS_CUSTOMMODE)
			WEStateManager::SetNextState(DS_CUSTOMINTRO);
		else
			Go_Menu();
	}

	//for edit
	if (WEInput::IsTriggered(WE_SPACE))
	{
		if (data.editmode != true) data.editmode = true;
		else data.editmode = false;
	}
	
	// bother mouse movement to replay
	if (WEInput::IsTriggered(WE_R))
	{
		//Restart
		SoundManager::sharedManager()->play(RESTART);
		if (data.game_mode == STORY)
		{
			data.life_count += 1;
			data.cameraZ = 500;
			InitShip(data);
			InitFuel(data);
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
			data.life_count += 1;
			data.cameraZ = DEFAULT_CAMERA_Z;
			InitShip(data);
			InitFuel(data);
		}
	}

	//Creat code in story
	if (data.game_mode == STORY)
	{
		//previous stage
		if (WEInput::IsTriggered(WE_1) && data.level > 1 && WEInput::IsPressed(WE_CONTROL))
		{
			data.level -= 1;
			WEStateManager::Restart();
		}
		//next stage
		if (WEInput::IsTriggered(WE_2) && data.level <= MAX_LEVEL && WEInput::IsPressed(WE_CONTROL))
		{
			if (data.level == MAX_LEVEL)
				WEStateManager::SetNextState(DS_THANK);
			else {
				data.level += 1;
				WEStateManager::Restart();
			}
		}
	}
}

//camera potision when zoom in
void Camera_position(Ship *pShip, ReturnData data, float dt)
{
	WEVec2 Vec_cam_ship;
	WEVec2 camera_position;
	camera_position.x = data.screenWidth / 2;
	camera_position.y = data.screenHeight / 2;
	Vec_cam_ship.x = (pShip->pos.x - data.screenWidth / 2);// / 2;
	Vec_cam_ship.y = (pShip->pos.y - data.screenHeight / 2);// / 2;

	if (pShip->shiptype == SHIP_SHOOTED)
	{
		data.camera_time += dt;

		if (data.cameraZ < DEFAULT_CAMERA_Z)
		{
			if (data.camera_time < 1)
			{
				camera_position.x = data.screenWidth / 2 + (Vec_cam_ship.x * data.camera_time);
				camera_position.y = data.screenHeight / 2 + (Vec_cam_ship.y * data.camera_time);
			}
			else
			{
				camera_position.x = pShip->pos.x;
				camera_position.y = pShip->pos.y;
			}

			//boundary
			if (pShip->pos.x > RIGHT_MAX - 1.8 * data.cameraZ)
				camera_position.x = RIGHT_MAX - (float)1.8 * data.cameraZ;
			if (pShip->pos.x < LEFT_MAX + 1.8 * data.cameraZ)
				camera_position.x = LEFT_MAX + (float)1.8 * data.cameraZ;
			if (pShip->pos.y > TOP_MAX -  data.cameraZ)
				camera_position.y = TOP_MAX - data.cameraZ;
			if (pShip->pos.y < BOTTOM_MAX +  data.cameraZ)
				camera_position.y = BOTTOM_MAX + data.cameraZ;
		}
	}
	else
	{
		camera_position.x = data.screenWidth / 2;
		camera_position.y = data.screenHeight / 2;
	}
	WEGraphics::SetCamera(camera_position.x, camera_position.y, data.cameraZ, 0);
}

//Adventure mode camera position
void AD_Camera_position(Ship *pShip, ReturnData data)
{
	
	WEVec2 camera_position;
	camera_position.x = data.screenWidth / 2;
	camera_position.y = data.screenHeight / 2;

	if (pShip->shiptype == SHIP_SHOOTED)
	{
			camera_position.x = pShip->pos.x;
			camera_position.y = pShip->pos.y;
			
			if (pShip->pos.x > AD_RIGHT - 1.8 * data.cameraZ)
				camera_position.x = AD_RIGHT - (float)1.8 * data.cameraZ;
			if (pShip->pos.x < AD_LEFT + 1.8 * data.cameraZ)
				camera_position.x = AD_LEFT + (float)1.8 * data.cameraZ;
			if (pShip->pos.y > AD_TOP - data.cameraZ)
				camera_position.y = AD_TOP - data.cameraZ;
			if (pShip->pos.y < AD_BOTTOM + data.cameraZ)
				camera_position.y = AD_BOTTOM + data.cameraZ;
	}
	else
	{
		camera_position.x = data.screenWidth / 2;
		camera_position.y = data.screenHeight / 2;
	}
	WEGraphics::SetCamera(camera_position.x, camera_position.y, data.cameraZ, 0);
}