/******************************************************************************
\file	Planet.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "Planet.h"
#include "SpaceShip.h" //for map size
#include <string>
namespace
{
	EditData editData;
}
void InitPlanet(ReturnData &data)
{

	data.pOM->GetPlanet();
	switch (data.level)
	{
		case 1:
		{
			PlanetLoadFile("LevelData/planet1.txt", data);
			break;
		}
		case 2:
		{
			PlanetLoadFile("LevelData/planet2.txt", data);
			break;
		}
		case 3:
		{
			PlanetLoadFile("LevelData/planet3.txt", data);
			break;
		}
		case 4:
		{
			PlanetLoadFile("LevelData/planet4.txt", data);
			break;
		}
		case 5:
		{
			PlanetLoadFile("LevelData/planet5.txt", data);
			break;
		}
		case 6:
		{
			PlanetLoadFile("LevelData/planet6.txt", data);
			break;
		}
		case 7:
		{
			PlanetLoadFile("LevelData/planet7.txt", data);
			break;
		}
		case 8:
		{
			PlanetLoadFile("LevelData/planet8.txt", data);
			break;
		}
		case 9:
		{
			PlanetLoadFile("LevelData/planet9.txt", data);
			break;
		}
		case 10:
		{
			PlanetLoadFile("LevelData/planet10.txt", data);
			break;
		}
		case 11:
		{
			PlanetLoadFile("LevelData/planet11.txt", data);
			break;
		}
		case 12:
		{
			PlanetLoadFile("LevelData/planet12.txt", data);
			break;
		}
		case 13:
		{
			PlanetLoadFile("LevelData/planet13.txt", data);
			break;
		}
		case 14:
		{
			PlanetLoadFile("LevelData/planet14.txt", data);
			break;
		}
		case 15:
		{
			PlanetLoadFile("LevelData/planet15.txt", data);
			break;
		}
		default : PlanetLoadFile("LevelData/planet_default.txt", data);
	}//switch

	 //set edit Data
	editData.isSelected = false;
	editData.relativeLoc = { 0, 0 };
	editData.targetObject = -1;


}//init planet

void AD_InitPlanet(ReturnData &data)
{
	//need file i/o
	data.pOM->GetPlanet();
	Planet planet;
	planet.texture = data.TextureData.planetTexture;

	int planetCount = data.max_planets;

	for (int planet_count = 0; planet_count < planetCount; ++planet_count)
	{
		planet.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
		planet.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		while ((planet.pos.x > AD_LEFT / 3 && planet.pos.x < AD_RIGHT / 3) &&
			(planet.pos.y < AD_TOP / 3 && planet.pos.y > AD_BOTTOM / 3))
		{
			planet.pos.x = WERandom::GetFloat(AD_LEFT, AD_RIGHT);
			planet.pos.y = WERandom::GetFloat(AD_BOTTOM, AD_TOP);
		}
		planet.scale.x = WERandom::GetFloat(100,200);
		planet.scale.y = planet.scale.x;
		planet.gravity = (planet.scale.x* planet.scale.x) / 1000.f;
		planet.mass = (planet.scale.x* planet.scale.x) / 1000.f;
		planet.life = PLANET_LIFE;
		data.pOM->SetPlanet(planet.pos, planet.scale, planet.gravity, planet.mass, planet.texture, planet_count, planet.life);
		data.pOM->IncPlanetCount();
	}


}//init planet


void CT_InitPlanet(ReturnData &data)
{

	std::string path = getenv("USERPROFILE");
	path += "/My Documents/Return/";
	//need file i/o
	data.pOM->GetPlanet();
	switch (data.level)
	{
	case 101:
	{
		PlanetLoadFile(std::string(path + "LevelData/planet101.txt").c_str(), data);
		break;
	}
	case 102:
	{
		PlanetLoadFile(std::string(path + "LevelData/planet102.txt").c_str(), data);
		break;
	}
	case 103:
	{
		PlanetLoadFile(std::string(path + "LevelData/planet103.txt").c_str(), data);
		break;
	}
	default: PlanetLoadFile("LevelData/planet_default.txt", data);
	}//switch

	 //set edit Data
	editData.isSelected = false;
	editData.relativeLoc = { 0, 0 };
	editData.targetObject = -1;
}


void InitPlanetEdge(ReturnData &data)
{
	Planet* pPlanet = data.pOM->GetPlanet();
	Edge edge;
	for (int i = 0; i < data.max_planets; ++i)
	{
		edge.pos = pPlanet[i].pos;
		edge.scale = 2 * pPlanet[i].scale;
		edge.texture = data.TextureData.edgeTexture;

		data.pOM->SetPlanetEdge(edge.pos, edge.scale, edge.texture, i );
	}
}

//effect of gravity
void ActionPlanet(Ship* pShip, Planet* pPlanet, float dt)
{
	if (pShip->shiptype == SHIP_SHOOTED)
	{
		pShip->vel.x += Universalgravitation(pShip, pPlanet) * Normalx(pShip, pPlanet) * dt;
		pShip->vel.y += Universalgravitation(pShip, pPlanet) * Normaly(pShip, pPlanet) * dt;
	}
}


void changePlanetTexture(Planet *pPlanet, ReturnData &data, float &time)
{
	WEDEBUG_PRINT("life is %d \n", pPlanet->life);
	pPlanet->life -= 1;
	
	if (pPlanet->life >= 5)
		pPlanet->texture = data.TextureData.planetTexture;
	else if (pPlanet->life >= 4)
		pPlanet->texture = data.TextureData.EggWaitTexture;
	else if (pPlanet->life >= 3)
		pPlanet->texture = data.TextureData.EggPasicTexture;
	else if (pPlanet->life >= 2)
		pPlanet->texture = data.TextureData.EggSleepTexture;
	else if (pPlanet->life < 2)
	{
		SoundManager::sharedManager()->play(PIYAC);
		pPlanet->texture = data.TextureData.EggWakeUpTexture;
		time = 0;
	}
}

void EditPlanetT(Planet* pPlanet, ObjectManager* pOM)
{
	WEVec2 mouse;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	int planetCount = pOM->GetPlanetCount();
	if (editData.isSelected == true)
	{
		pPlanet[editData.targetObject].pos = mouse + editData.relativeLoc;
		if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			editData.targetObject = -1;
			editData.relativeLoc = { 0,0 };
			editData.isSelected = false;
		}

		if (WEInput::IsTriggered(WE_MOUSE_RIGHT) && planetCount > 0)
		{
			pPlanet[editData.targetObject] = pPlanet[planetCount - 1];
			pPlanet[planetCount - 1].pos = { 1500, 1500 };
			pPlanet[planetCount - 1].scale = { 0,0 };
			pOM->DecPlanetCount();
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
			}
		}
	}
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

void PlanetEdgePosition(Edge *pEdge, Planet *pPlanet, ReturnData &data)
{
	for (int i = 0; i < data.max_planets; ++i)
	{
		pEdge[i].pos = pPlanet[i].pos;
		pEdge[i].scale = pPlanet[i].scale * 2;
	}
}

void DrawPlanetEdge(Edge *pEdge, ReturnData &data)
{
	WEMtx44 tranform;
	//planet draw
	for (int planet_count = 0; planet_count < data.max_planets; ++planet_count)
	{
		WEGraphics::SetTexture(pEdge[planet_count].texture);
		WEMtx44::MakeTransform(tranform,
			pEdge[planet_count].scale.x,
			pEdge[planet_count].scale.y,
			0,
			pEdge[planet_count].pos.x,
			pEdge[planet_count].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

void EditPlanetSize(Planet* pPlanet, ObjectManager* pOM)
{
	WEVec2 mouse;
	WEVec2 originScale;
	WEVec2 scale;

	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	scale = editData.relativeLoc;

	int planetCount = pOM->GetPlanetCount();
	if (editData.isSelected == true)
	{
		editData.relativeLoc = pPlanet[editData.targetObject].pos - mouse;
		scale = editData.relativeLoc;
		if (scale.x < 0)
			scale.x *= -1;
		if (scale.y < 0)
			scale.y *= -1;

		if (scale.x > scale.y)
			scale.y = scale.x;
		else
			scale.x = scale.y;

		scale.x *= 2;
		scale.y *= 2;

		pPlanet[editData.targetObject].scale = scale;
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
				pPlanet[i].scale.x / 2)
				&& !WEIntersection::PointCircle(mouse, pPlanet[i].pos,
					pPlanet[i].scale.x / 3)
				&& WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				editData.relativeLoc = pPlanet[i].pos - mouse;
				originScale = pPlanet[i].scale;
				editData.isSelected = true;
				editData.targetObject = i;
			}
		}
	}
}