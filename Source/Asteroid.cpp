/******************************************************************************
\file   Planet.cpp
\title  Returner
\author Jinseob Park
\par    GAM150
\brief

" All content ?2017 DigiPen (USA) Corporation, all rights reserved.?

******************************************************************************/
#include "Planet.h"
#include "WEDebugTools.h"
#include <cstdio>
/*
namespace
{
	ReturnData data;
}
*/
void LoadFile(const char* fileName, ReturnData &data)
{
	FILE* pFile = 0;
	Planet planet;
	planet.texture = data.TextureData.planetTexture;
	fopen_s(&pFile, fileName, "rt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");

	for (int planet_count = 0; planet_count < data.max_planets; ++planet_count)
	{
		fscanf_s(pFile, "%f", &planet.pos.x);
		fscanf_s(pFile, "%f", &planet.pos.y);
		fscanf_s(pFile, "%f", &planet.scale.x);
		fscanf_s(pFile, "%f", &planet.scale.y);
		fscanf_s(pFile, "%d", &planet.gravity);
		fscanf_s(pFile, "%f", &planet.mass);
		data.pOM->SetPlanet(planet.pos, planet.scale, planet.gravity, planet.mass, planet.texture, planet_count);
	}
	fclose(pFile);
}
void InitPlanet(ReturnData &data)
{
	//need file i/o
	data.pOM->GetPlanet();
	//int planet_count = data.pOM->GetPlanetCount();
	Planet planet;
	switch (data.level)
	{
	case 1:
	{
		LoadFile("planet1.txt", data);
		break;
	}
	case 2:
	{
		LoadFile("planet2.txt", data);
		break;
	}
	default :
		for (int planet_count = 0; planet_count < data.max_planets; ++planet_count)
		{
			planet.pos.x = 831.0f;
			planet.pos.y = 290.0f;
			planet.scale.x = 256;
			planet.scale.y = 256;
			planet.gravity = 100;
			planet.mass = 100;
			planet.pull = true;
			planet.count = true;
			switch (planet_count) {
			case 0: {planet.texture = data.TextureData.planetTexture; break; }
			default: planet.texture = data.TextureData.planetTexture;
			}


			data.pOM->SetPlanet(planet.pos, planet.scale, planet.gravity, planet.mass, planet.pull, planet.count, planet.texture, planet_count);
		}
	}


}


//effect of gravity
void ActionPlanet(Ship* pShip, Planet* pPlanet, float dt)
{
	if (pShip->shoot == true)
	{
		pShip->vel.x += Universalgravitation(pShip, pPlanet) * Normalx(pShip, pPlanet) * dt;
		pShip->vel.y += Universalgravitation(pShip, pPlanet) * Normaly(pShip, pPlanet) * dt;
	}

}


void EditPlanet(Planet* pPlanet)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
	for (int i = 0; i < 2; ++i)
	{

		if (WEIntersection::PointRect(mouse, pPlanet[i].pos,
			pPlanet[i].scale.x, pPlanet[i].scale.y))
		{
			if (WEInput::IsPressed(WE_MOUSE_LEFT))
			{
				pPlanet[i].pos = mouse;
			}
		}
	}
	/*
	if (WEIntersection::PointRect(mouse, pPlanet[0].pos,
		pPlanet[0].scale.x, pPlanet[0].scale.y))
	{
		if (WEInput::IsPressed(WE_MOUSE_LEFT))
		{
			pPlanet[0].pos = mouse;
		}
	}
	if (WEIntersection::PointRect(mouse, pPlanet[1].pos,
		pPlanet[1].scale.x, pPlanet[1].scale.y))
	{
		if (WEInput::IsPressed(WE_MOUSE_LEFT))
		{
			pPlanet[1].pos = mouse;
		}
	}
	*/
}
void DrawPlanet(Planet *pPlanet, ReturnData &data)
{
	WEMtx44 tranform;
    //planet draw
    for (int planet_count = 0; planet_count < data.max_planets; ++planet_count)
    {
    	WEGraphics::SetTexture(pPlanet[planet_count].texture);
    	WEMtx44::MakeTransform(tranform,
			pPlanet[planet_count].scale.x,
			pPlanet[planet_count].scale.y,
    		0,
    		pPlanet[planet_count].pos.x,
			pPlanet[planet_count].pos.y,
    		0);
    	WEGraphics::Draw(tranform);
    }
}