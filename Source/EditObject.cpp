/******************************************************************************
\file	EditObject.cpp
\title  Returner
\author Minwoo Choi, Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "EditObject.h"
#include "WEDebugTools.h"

namespace
{
	EditData editData;
}

void EditAsteroid(Asteroid* pAsteroid, ObjectManager* pOM)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	int asteroidCount = pOM->GetAsteroidCount();
	if (editData.isSelected == true && editData.targetType == 2)
	{
		pAsteroid[editData.targetObject].pos = mouse + editData.relativeLoc;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
		if (WEInput::IsTriggered(WE_MOUSE_RIGHT) && asteroidCount > 0)
		{
			pAsteroid[editData.targetObject] = pAsteroid[asteroidCount - 1];
			pAsteroid[asteroidCount - 1].pos = { 15000, 15000 };
			pAsteroid[asteroidCount - 1].scale = { 0,0 };
			pOM->DecAsteroidCount();
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
	}
	else//(editData.isSelected == false)
	{
		for (int i = 0; i < asteroidCount; ++i)
		{
			if (WEIntersection::PointCircle(mouse, pAsteroid[i].pos,
				pAsteroid[i].scale.x / 2) && WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				editData.relativeLoc = pAsteroid[i].pos - mouse;
				editData.isSelected = true;
				editData.targetObject = i;
				editData.targetType = 2;
			}
		}
	}
}



void EditPlanet(Planet* pPlanet, ObjectManager* pOM)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	int planetCount = pOM->GetPlanetCount();
	if (editData.isSelected == true && editData.targetType == 1)
	{
		pPlanet[editData.targetObject].pos = mouse + editData.relativeLoc;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
	}
	else//(editData.isSelected == false)
	{
		for (int i = 0; i < planetCount; ++i)
		{
			if (WEIntersection::PointCircle(mouse, pPlanet[i].pos,
				pPlanet[i].scale.x / 2) && WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				editData.relativeLoc = pPlanet[i].pos - mouse;
				editData.isSelected = true;
				editData.targetObject = i;
				editData.targetType = 2;
				editData.targetType = 1;
			}
		}
	}
}


//EditAsteroidVel
void EditAsteroidVel(Asteroid* pAsteroid, ObjectManager* pOM)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	int asteroidCount = pOM->GetAsteroidCount();
	if (editData.isSelected == true && editData.targetType == 2)
	{
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			pAsteroid[editData.targetObject].vel = mouse - pAsteroid[editData.targetObject].pos - editData.relativeLoc;
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
	}
	else//(editData.isSelected == false)
	{
		for (int i = 0; i < asteroidCount; ++i)
		{
			if (WEIntersection::PointCircle(mouse, pAsteroid[i].pos,
				pAsteroid[i].scale.x / 2) && WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				editData.relativeLoc = pAsteroid[i].pos - mouse;
				editData.isSelected = true;
				editData.targetObject = i;
				editData.targetType = 2;
			}
		}
	}
}

void EditFuel(Object* pObject, ObjectManager* pOM)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	int objectCount = pOM->GetFuelCount();
	if (editData.isSelected == true && editData.targetType == 1)
	{
		pObject[editData.targetObject].pos = mouse + editData.relativeLoc;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
		if (WEInput::IsTriggered(WE_MOUSE_RIGHT) && objectCount > 0)
		{
			pObject[editData.targetObject] = pObject[objectCount - 1];
			pObject[objectCount - 1].pos = { 15000, 15000 };
			pObject[objectCount - 1].scale = { 0,0 };
			pOM->DecFuelCount();
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}
	}
	else//(editData.isSelected == false)
	{
		for (int i = 0; i < objectCount; ++i)
		{
			if (WEIntersection::PointCircle(mouse, pObject[i].pos,
				pObject[i].scale.x / 2) && WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				editData.relativeLoc = pObject[i].pos - mouse;
				editData.isSelected = true;
				editData.targetObject = i;
				editData.targetType = 2;
				editData.targetType = 1;
			}
		}
	}
}