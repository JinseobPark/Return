/******************************************************************************
\file	ParticleManager.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "ParticleManager.h"
#include <cmath>
#include <math.h>
#include "SpaceShip.h"
//static variable
int ParticleManager::particle_option_booster = OPTION_INITIAL_NUMBER;
int ParticleManager::particle_option_explode = OPTION_INITIAL_NUMBER;

namespace
{
	float Width;
	float Height;
}

//constructor
ParticleManager::ParticleManager(void)
{
	ParticleLoad("LevelData/particle.txt");
	d_background = new Particle[d_BG_maxObjects];
	d_explode    = new Particle[d_Explode_maxObjects];
	d_boost      = new Particle[d_Boost_maxObjects];
	d_byebye     = new Particle[d_byebye_maxObjects];

	d_BG_Objectcount = INITIALIZE_ZERO;
	d_Explode_Objectcount = INITIALIZE_ZERO;
	d_Boost_Objectcount = INITIALIZE_ZERO;
	d_byebye_Objectcount = INITIALIZE_ZERO;
}

//destructor
ParticleManager::~ParticleManager(void)
{
	delete[] d_background;
	delete[] d_explode;
	delete[] d_boost;
	delete[] d_byebye;
}

//Get particle
Particle* ParticleManager::GetBG(void)
{
	return d_background;
}

Particle* ParticleManager::GetExplode(void)
{
	return d_explode;
}
Particle* ParticleManager::GetBoost(void)
{
	return d_boost;
}
Particle* ParticleManager::GetByebye(void)
{
	return d_byebye;
}

//load particle information
void ParticleManager::ParticleLoad(const char* pFileName)
{
	FILE* pFile = 0;

	fopen_s(&pFile, pFileName, "rt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");

	fscanf_s(pFile, "%d", &d_BG_maxObjects);
	fscanf_s(pFile, "%f", &d_BG_maxScale);
	fscanf_s(pFile, "%f", &d_BG_minScale);
	fscanf_s(pFile, "%f", &d_BG_maxVel);
	fscanf_s(pFile, "%f", &d_BG_minVel);

	fscanf_s(pFile, "%d", &d_Explode_maxObjects);
	fscanf_s(pFile, "%f", &d_Explode_Vel);
	fscanf_s(pFile, "%f", &d_Explode_Scale);
	fscanf_s(pFile, "%f", &d_Explode_Life);

	fscanf_s(pFile, "%d", &d_Boost_maxObjects);
	fscanf_s(pFile, "%f", &d_Boost_Vel);
	fscanf_s(pFile, "%f", &d_Boost_Scale);
	fscanf_s(pFile, "%f", &d_Boost_Life);
	fscanf_s(pFile, "%f", &d_Boost_Time);

	fscanf_s(pFile, "%d", &d_byebye_maxObjects);
	fscanf_s(pFile, "%f", &d_byebye_Vel);
	fscanf_s(pFile, "%f", &d_byebye_Scale);
	fscanf_s(pFile, "%f", &d_byebye_Life);

	fclose(pFile);
}

//BackGround
void ParticleManager::LoadBG(Particle *p_background)
{
	for (int i = 0; i < d_BG_maxObjects; ++i)
	{
		p_background[i].pos.x = INITIALIZE_ZERO;
		p_background[i].pos.y = INITIALIZE_ZERO;
		p_background[i].vel.x = INITIALIZE_ZERO;
		p_background[i].vel.y = INITIALIZE_ZERO;
		p_background[i].scale.x = INITIALIZE_ZERO;
		p_background[i].scale.y = INITIALIZE_ZERO;
		p_background[i].store.x = INITIALIZE_ZERO;
		p_background[i].store.y = INITIALIZE_ZERO;
		p_background[i].rot     = INITIALIZE_ZERO;
		p_background[i].rotvel  = INITIALIZE_ZERO;
		p_background[i].texture = INITIALIZE_ZERO;
		p_background[i].id      = INITIALIZE_ZERO;
		p_background[i].life    = INITIALIZE_ZERO;
	}
}
void ParticleManager::InitBG(Particle *p_background, int texture)
{
	Width = (float)WEApplication::GetWidth();
	Height = (float)WEApplication::GetHeight();
	for (int i = 0; i < d_BG_maxObjects; ++i)
	{
		p_background[i].pos.x = WERandom::GetFloat(-1.0f * Width, 2.0f * Width);
		p_background[i].pos.y = WERandom::GetFloat(-1.0f *Height, 2.0f * Height);
		p_background[i].vel.x = WERandom::GetFloat(d_BG_minVel, d_BG_maxVel);
		p_background[i].vel.y = WERandom::GetFloat(d_BG_minVel, d_BG_maxVel);
		p_background[i].scale.x = WERandom::GetFloat(d_BG_minScale, d_BG_maxScale);
		p_background[i].scale.y = p_background[i].scale.x;
		p_background[i].texture = texture;
	}
}

void ParticleManager::AD_InitBG(Particle *p_background, TextureData const data)
{
	Width = (float)WEApplication::GetWidth();
	Height = (float)WEApplication::GetHeight();
	for (int i = 0; i < d_BG_maxObjects; ++i)
	{
		p_background[i].pos.x = WERandom::GetFloat(1.2*AD_LEFT, 1.2*AD_RIGHT);
		p_background[i].pos.y = WERandom::GetFloat(1.2*AD_BOTTOM, 1.2*AD_TOP);
		p_background[i].vel.x = WERandom::GetFloat(d_BG_minVel, d_BG_maxVel);
		p_background[i].vel.y = WERandom::GetFloat(d_BG_minVel, d_BG_maxVel);
		p_background[i].scale.x = WERandom::GetFloat(d_BG_minScale, d_BG_maxScale);
		p_background[i].scale.y = p_background[i].scale.x;
		p_background[i].texture = data.circleTexture;
	}
}
void ParticleManager::UpdateBG(Particle *p_background, float dt)
{
	for (int i = 0; i < d_BG_maxObjects; ++i)
	{
		p_background[i].pos.x += p_background[i].vel.x * dt;
		p_background[i].pos.y += p_background[i].vel.y * dt;
	}
}
void ParticleManager::DrawBG(Particle *p_background)
{
	WEMtx44 tranform;
	for (int i = 0; i < d_BG_maxObjects; ++i)
	{
		WEGraphics::SetTexture(d_background[i].texture);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(tranform,
			p_background[i].scale.x,
			p_background[i].scale.y,
			0,
			p_background[i].pos.x,
			p_background[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

//explode
void ParticleManager::LoadCrashing(Particle *p_explode)
{
	for (int i = 0; i < d_Explode_maxObjects; ++i)
	{
		p_explode[i].pos.x   = INITIALIZE_ZERO;
		p_explode[i].pos.y   = INITIALIZE_ZERO;
		p_explode[i].vel.x   = INITIALIZE_ZERO;
		p_explode[i].vel.y   = INITIALIZE_ZERO;
		p_explode[i].scale.x = INITIALIZE_ZERO;
		p_explode[i].scale.y = INITIALIZE_ZERO;
		p_explode[i].store.x = INITIALIZE_ZERO;
		p_explode[i].store.y = INITIALIZE_ZERO;
		p_explode[i].rot     = INITIALIZE_ZERO;
		p_explode[i].rotvel  = INITIALIZE_ZERO;
		p_explode[i].texture = INITIALIZE_ZERO;
		p_explode[i].id      = INITIALIZE_ZERO;
		p_explode[i].life    = INITIALIZE_ZERO;
	}
}
void ParticleManager::InitCrashing(Particle *p_explode, Ship *pship)
{
	switch (ParticleManager::particle_option_explode)
	{
	case 1:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(0.5, 1.5);
			p_explode[i].store.x = pship->pos.x;
			p_explode[i].store.y = pship->pos.y;
			p_explode[i].pos.x = pship->pos.x;
			p_explode[i].pos.y = pship->pos.y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::HALF_PI / 2 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::HALF_PI / 2 * i);
			p_explode[i].scale.x = d_Explode_Scale;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
		}
		break;
	}
	//fire
	case 2:
	{
		{
			d_Explode_Objectcount = d_Explode_maxObjects;
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				d_Explode_Vel = WERandom::GetFloat(1, 2);
				p_explode[i].store.x = pship->pos.x;
				p_explode[i].store.y = pship->pos.y;
				p_explode[i].pos.x = pship->pos.x;
				p_explode[i].pos.y = pship->pos.y;
				p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 100 * i);
				p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 100 * i);
				p_explode[i].scale.x = 3 * d_Explode_Vel;
				p_explode[i].scale.y = p_explode[i].scale.x;
				//p_explode[i].store.x = p_explode[i].pos.x;
				//p_explode[i].store.y = p_explode[i].pos.y;
				p_explode[i].life = d_Explode_Vel / 4;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
				p_explode[i].rot = d_Explode_Vel;
			}
		}
		break;
	}
	//spin
	case 3:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(1.f, 1.5f);
			p_explode[i].store.x = pship->pos.x;
			p_explode[i].store.y = pship->pos.y;
			p_explode[i].pos.x = pship->pos.x;
			p_explode[i].pos.y = pship->pos.y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 20 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 20 * i);
			p_explode[i].scale.x = 3 * d_Explode_Vel * d_Explode_Vel;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
			p_explode[i].rot = d_Explode_Vel * 2;
		}
		break;
	}
	//yellow storm
	case 4:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(0.5f, 1.5f);
			p_explode[i].store.x = pship->pos.x;
			p_explode[i].store.y = pship->pos.y;
			p_explode[i].pos.x = pship->pos.x;
			p_explode[i].pos.y = pship->pos.y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::HALF_PI / 2 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::HALF_PI / 2 * i);
			p_explode[i].scale.x = d_Explode_Scale;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
		}
		break;
	}
	//blue strom
	case 5:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(1.f, 1.5f);
			p_explode[i].store.x = pship->pos.x;
			p_explode[i].store.y = pship->pos.y;
			p_explode[i].pos.x = pship->pos.x;
			p_explode[i].pos.y = pship->pos.y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 3 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 3 * i);
			p_explode[i].scale.x = 6 * d_Explode_Vel * d_Explode_Vel;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel / 2;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
			p_explode[i].rot = d_Explode_Vel * 2;
		}
		break;
	}
	default:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(0.5f, 1.5f);
			p_explode[i].store.x = pship->pos.x;
			p_explode[i].store.y = pship->pos.y;
			p_explode[i].pos.x = pship->pos.x;
			p_explode[i].pos.y = pship->pos.y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::HALF_PI / 2 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::HALF_PI / 2 * i);
			p_explode[i].scale.x = d_Explode_Scale;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
		}
	}
	}

}

void ParticleManager::UpdateCrashing(Particle *p_explode, float &dt)
{

	switch (ParticleManager::particle_option_explode)
	{
	case 1:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * dt * 100;
			p_explode[i].pos.y += p_explode[i].vel.y * dt * 100;
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//fire
	case 2:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * 50 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 50 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x  = p_explode[i].store.x + ((p_explode[i].pos.x  - p_explode[i].store.x)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - p_explode[i].store.y)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y  = p_explode[i].store.y + ((p_explode[i].rotvel - p_explode[i].store.x)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - p_explode[i].store.y)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//spin
	case 3:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * 100 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 100 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x  = p_explode[i].store.x + ((p_explode[i].pos.x  - p_explode[i].store.x)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - p_explode[i].store.y)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y  = p_explode[i].store.y + ((p_explode[i].rotvel - p_explode[i].store.x)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - p_explode[i].store.y)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//yellow storm
	case 4:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * 40 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 40 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x  = p_explode[i].store.x + ((p_explode[i].pos.x  - p_explode[i].store.x)*cos(sqrt(p_explode[i].life) * 2 * dt) - (p_explode[i].pos.y - p_explode[i].store.y)*sin(sqrt(p_explode[i].life) * 2 * dt));
			p_explode[i].pos.y  = p_explode[i].store.y + ((p_explode[i].rotvel - p_explode[i].store.x)*sin(sqrt(p_explode[i].life) * 2 * dt) + (p_explode[i].pos.y - p_explode[i].store.y)*cos(sqrt(p_explode[i].life) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//blue strom
	case 5:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * 80 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 80 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x  = p_explode[i].store.x + ((p_explode[i].pos.x  - p_explode[i].store.x)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - p_explode[i].store.y)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y  = p_explode[i].store.y + ((p_explode[i].rotvel - p_explode[i].store.x)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - p_explode[i].store.y)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	default:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * dt * 100;
			p_explode[i].pos.y += p_explode[i].vel.y * dt * 100;
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}

		}
	}
	}
}
void ParticleManager::DrawCrasing(Particle *p_explode, TextureData data)
{

	WEMtx44 tranform;
	switch (ParticleManager::particle_option_explode)
	{
	case 1:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
		break;
	}
	//fire
	case 2:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			if (p_explode[i].rot < 1.1f)
				WEGraphics::SetTextureColor(255, 255, 255, 255);
			else if (p_explode[i].rot < 1.4f)
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(180, 250), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
			else if (p_explode[i].rot < 1.7f)
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(80, 200), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
			else
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(0, 120), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
		break;
	}

	//spin
	case 3:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(200, 210), (unsigned char)WERandom::GetInt(145, 150));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
		break;
	}
	//yellow storm
	case 4:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(222, 255), (unsigned char)WERandom::GetInt(8, 10), (unsigned char)WERandom::GetInt(247, 250));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
		break;
	}
	//blue strom
	case 5:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(30, 50), (unsigned char)WERandom::GetInt(100, 155), (unsigned char)WERandom::GetInt(200, 255), (unsigned char)WERandom::GetInt(247, 250));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
		break;
	}
	default:
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
			WEMtx44::MakeTransform(tranform,
				p_explode[i].scale.x,
				p_explode[i].scale.y,
				0,
				p_explode[i].pos.x,
				p_explode[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}
	}
}

//option particle
void ParticleManager::OptionInitCrasing(Particle *p_explode)
{

	switch (ParticleManager::particle_option_explode)
	{
	case 1:
	{	
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(0.5, 1.5);
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::HALF_PI / 2 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::HALF_PI / 2 * i);
			p_explode[i].scale.x = d_Explode_Scale;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
		}
		break;
	}
	//fire
	case 2:
	{
		{
			d_Explode_Objectcount = d_Explode_maxObjects;
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				d_Explode_Vel = WERandom::GetFloat(1, 2);
				p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
				p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
				p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 100 * i);
				p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 100 * i);
				p_explode[i].scale.x = 3 * d_Explode_Vel;
				p_explode[i].scale.y = p_explode[i].scale.x;
				p_explode[i].life = d_Explode_Vel / 4;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
				p_explode[i].rot = d_Explode_Vel;
			}
		}
		break;
	}
	//spin
	case 3:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(1, 1.5);
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 20 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 20 * i);
			p_explode[i].scale.x = 3 * d_Explode_Vel * d_Explode_Vel;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
			p_explode[i].rot = d_Explode_Vel * 2;
		}
		break;
	}
	//yellow storm
	case 4:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(0.5, 1.5);
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::HALF_PI / 2 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::HALF_PI / 2 * i);
			p_explode[i].scale.x = d_Explode_Scale;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
		}
		break;
	}
	//blue strom
	case 5:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(1, 1.5);
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 3 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 3 * i);
			p_explode[i].scale.x = 6 * d_Explode_Vel * d_Explode_Vel;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel / 2;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
			p_explode[i].rot = d_Explode_Vel * 2;
		}
		break;
	}
	default:
	{
		d_Explode_Objectcount = d_Explode_maxObjects;
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			d_Explode_Vel = WERandom::GetFloat(1, 2);
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X;
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y;
			p_explode[i].vel.x = d_Explode_Vel * cos(WEMath::TWO_PI / 100 * i);
			p_explode[i].vel.y = d_Explode_Vel * sin(WEMath::TWO_PI / 100 * i);
			p_explode[i].scale.x = 3 * d_Explode_Vel;
			p_explode[i].scale.y = p_explode[i].scale.x;
			p_explode[i].life = d_Explode_Vel / 4 ;// d_Explode_Life * WERandom::GetFloat(0.1, 2);
			p_explode[i].rot = d_Explode_Vel;
		}
	}
	}
}


void ParticleManager::OptionUpdateCrashing(Particle *p_explode, float &dt)
{
	
	switch (ParticleManager::particle_option_explode)
	{
	case 1:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			p_explode[i].pos.x += p_explode[i].vel.x * dt * 100;
			p_explode[i].pos.y += p_explode[i].vel.y * dt * 100;
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}

		}
		break;
	}
	//fire
	case 2:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			//p_explode[i].rot += 0.02 *dt;
			p_explode[i].pos.x += p_explode[i].vel.x * 50 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 50 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X + ((p_explode[i].pos.x - OPTION_EXPLODE_SHIP_X)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - 300)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y + ((p_explode[i].rotvel - OPTION_EXPLODE_SHIP_X)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - 300)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//spin
	case 3:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			//p_explode[i].rot += 0.02 *dt;
			p_explode[i].pos.x += p_explode[i].vel.x * 100 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 100 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X + ((p_explode[i].pos.x - OPTION_EXPLODE_SHIP_X)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y + ((p_explode[i].rotvel - OPTION_EXPLODE_SHIP_X)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//yellow storm
	case 4:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			
			p_explode[i].pos.x += p_explode[i].vel.x * 40 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 40 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X + ((p_explode[i].pos.x - OPTION_EXPLODE_SHIP_X)*cos(sqrt(p_explode[i].life) * 2 * dt) - (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*sin(sqrt(p_explode[i].life) * 2 * dt));
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y + ((p_explode[i].rotvel - OPTION_EXPLODE_SHIP_X)*sin(sqrt(p_explode[i].life) * 2 * dt) + (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*cos(sqrt(p_explode[i].life) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	//blue strom
	case 5:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			//p_explode[i].rot += 0.02 *dt;
			p_explode[i].pos.x += p_explode[i].vel.x * 80 * dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 80 * dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X + ((p_explode[i].pos.x - OPTION_EXPLODE_SHIP_X)*cos((p_explode[i].rot) * 2 * dt) - (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*sin((p_explode[i].rot) * 2 * dt));
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y + ((p_explode[i].rotvel - OPTION_EXPLODE_SHIP_X)*sin((p_explode[i].rot) * 2 * dt) + (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*cos((p_explode[i].rot) * 2 * dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
		break;
	}
	default:
	{
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
			//p_explode[i].rot += 0.02 *dt;
			p_explode[i].pos.x += p_explode[i].vel.x * 50* dt;
			p_explode[i].pos.y += p_explode[i].vel.y * 50 *dt;
			p_explode[i].rotvel = p_explode[i].pos.x;
			p_explode[i].pos.x = OPTION_EXPLODE_SHIP_X +((p_explode[i].pos.x - OPTION_EXPLODE_SHIP_X)*cos((p_explode[i].rot)*2 *dt) - (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*sin((p_explode[i].rot)*2 *dt));
			p_explode[i].pos.y = OPTION_EXPLODE_SHIP_Y +((p_explode[i].rotvel - OPTION_EXPLODE_SHIP_X)*sin((p_explode[i].rot)*2 *dt) + (p_explode[i].pos.y - OPTION_EXPLODE_SHIP_Y)*cos((p_explode[i].rot)*2 *dt));
			p_explode[i].life -= dt;
			if (p_explode[i].life <= 0)
			{
				p_explode[i].scale.x = 0.0f;
				p_explode[i].scale.y = 0.0f;
			}
		}
	}

	}
}
void ParticleManager::OptionDrawCrasing(Particle *p_explode, int texture)
{
	WEMtx44 tranform;
	switch (ParticleManager::particle_option_explode)
	{
		case 1:
		{	
		for (int i = 0; i < d_Explode_maxObjects; ++i)
		{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
		WEMtx44::MakeTransform(tranform,
			p_explode[i].scale.x,
			p_explode[i].scale.y,
			0,
			p_explode[i].pos.x,
			p_explode[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
		}
		break;
		}
		//fire
		case 2:
		{
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				WEGraphics::SetTexture(texture);
				if (p_explode[i].rot < 1.1f)
					WEGraphics::SetTextureColor(255, 255, 255, 255);
				else if (p_explode[i].rot < 1.4f)
					WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(180, 250), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
				else if (p_explode[i].rot < 1.7f)
					WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(80, 200), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
				else
					WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(0, 120), (unsigned char)WERandom::GetInt(0, 10), (unsigned char)WERandom::GetInt(200, 250));
				WEMtx44::MakeTransform(tranform,
					p_explode[i].scale.x,
					p_explode[i].scale.y,
					0,
					p_explode[i].pos.x,
					p_explode[i].pos.y,
					0);
				WEGraphics::Draw(tranform);
			}
			break;
		}

		//spin
		case 3:
		{
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				WEGraphics::SetTexture(texture);
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(200, 210), (unsigned char)WERandom::GetInt(145, 150));
				WEMtx44::MakeTransform(tranform,
					p_explode[i].scale.x,
					p_explode[i].scale.y,
					0,
					p_explode[i].pos.x,
					p_explode[i].pos.y,
					0);
				WEGraphics::Draw(tranform);
			}
			break;
		}
		//yellow storm
		case 4:
		{
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				WEGraphics::SetTexture(texture);
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(250, 255), (unsigned char)WERandom::GetInt(222, 255), (unsigned char)WERandom::GetInt(8, 10), (unsigned char)WERandom::GetInt(247, 250));
				WEMtx44::MakeTransform(tranform,
					p_explode[i].scale.x,
					p_explode[i].scale.y,
					0,
					p_explode[i].pos.x,
					p_explode[i].pos.y,
					0);
				WEGraphics::Draw(tranform);
			}
			break;
		}
		//blue strom
		case 5:
		{
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				WEGraphics::SetTexture(texture);
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(30, 50), (unsigned char)WERandom::GetInt(100, 155), (unsigned char)WERandom::GetInt(200, 255), (unsigned char)WERandom::GetInt(247, 250));
				WEMtx44::MakeTransform(tranform,
					p_explode[i].scale.x,
					p_explode[i].scale.y,
					0,
					p_explode[i].pos.x,
					p_explode[i].pos.y,
					0);
				WEGraphics::Draw(tranform);
			}
			break;
		}
		default:
			for (int i = 0; i < d_Explode_maxObjects; ++i)
			{
				WEGraphics::SetTexture(texture);
				WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
				WEMtx44::MakeTransform(tranform,
					p_explode[i].scale.x,
					p_explode[i].scale.y,
					0,
					p_explode[i].pos.x,
					p_explode[i].pos.y,
					0);
				WEGraphics::Draw(tranform);
			}

	}
}

//boost particle
void ParticleManager::LoadBoosting(Particle *p_boost)
{
	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		p_boost[i].pos.x   = INITIALIZE_ZERO;
		p_boost[i].pos.y   = INITIALIZE_ZERO;
		p_boost[i].vel.x   = INITIALIZE_ZERO;
		p_boost[i].vel.y   = INITIALIZE_ZERO;
		p_boost[i].scale.x = INITIALIZE_ZERO;
		p_boost[i].scale.y = INITIALIZE_ZERO;
		p_boost[i].store.x = INITIALIZE_ZERO;
		p_boost[i].store.y = INITIALIZE_ZERO;
		p_boost[i].rot     = INITIALIZE_ZERO;
		p_boost[i].rotvel  = INITIALIZE_ZERO;
		p_boost[i].texture = INITIALIZE_ZERO;
		p_boost[i].id      = INITIALIZE_ZERO;
		p_boost[i].life    = INITIALIZE_ZERO;
	}
}
void ParticleManager::InitBoosting(Particle *p_boost, Ship *pship)
{
	switch (ParticleManager::particle_option_booster)
	{
	case 1:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.1f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.05f, 0.05f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.05f, 0.05f));
		break;
	}
	case 2:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.1f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.05f, 0.05f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.05f, 0.05f));
		break;
	}
	case 3:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.5f, 1.f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.1f, 0.1f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.1f, 0.1f));
		break;
	}
	case 4:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.8f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.3f, 0.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.3f, 0.3f));
		break;
	}
	case 5:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.8f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.2f, 0.2f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.2f, 0.2f));
		break;
	}
	case 6:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.05f, 0.1f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-1.3f, 1.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-1.3f, 1.3f));
		break;
	}
	case 7:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.6f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-3.3f, 3.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-3.3f, 3.3f));
		break;
	}
	default:
	{
		p_boost->pos.x = pship->pos.x - 30 * cos(pship->angle);
		p_boost->pos.y = pship->pos.y - 30 * sin(pship->angle);
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.2f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(pship->angle + WERandom::GetFloat(-0.1f, 0.1f));
		p_boost->vel.y = -d_Boost_Vel * sin(pship->angle + WERandom::GetFloat(-0.1f, 0.1f));
	}
	}

}

void ParticleManager::PooozicBoosting(Particle *p_boost, Ship *pship, float dt, ReturnData &data)
{
	//if (data.boostfire == true)
	//{
		for (int i = 0; i < d_Boost_maxObjects; ++i)
		{
			p_boost[i].pos.x += p_boost[i].vel.x ;
			p_boost[i].pos.y += p_boost[i].vel.y ;
			p_boost[i].life -= dt;

			if (p_boost[i].life < 0)
			{
				if(data.boostfire == true)
				InitBoosting(p_boost + i, pship);
				else
				{
					p_boost[i].scale.x = 0;
					p_boost[i].scale.y = 0;
				}
			}

		}
		//WEDEBUG_PRINT("time %f\n", d_Boost_Time);
	//}
}

void ParticleManager::DrawBoosting(Particle *p_boost, TextureData data)
{
	WEMtx44 tranform;

	switch (ParticleManager::particle_option_booster)
	{
	case 1:
	{		for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)29, (unsigned char)WERandom::GetInt(109, 255), (unsigned char)WERandom::GetInt(109, 255), (unsigned char)200);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	for (int i = 0; i < d_Boost_maxObjects; i += 10)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)152, (unsigned char)WERandom::GetInt(213, 240), (unsigned char)WERandom::GetInt(240, 255), (unsigned char)210);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 2:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)241, (unsigned char)WERandom::GetInt(31, 212), (unsigned char)31, (unsigned char)221);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 3:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)29, (unsigned char)WERandom::GetInt(109, 255), (unsigned char)WERandom::GetInt(109, 255), (unsigned char)200);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 4:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor(36, 255, 196, 219);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 5:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 6:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(200, 255), (unsigned char)231, (unsigned char)WERandom::GetInt(100, 255), (unsigned char)WERandom::GetInt(200, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 7:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	default:
		for (int i = 0; i < d_Boost_maxObjects; ++i)
		{
			WEGraphics::SetTexture(data.circleTexture);
			WEGraphics::SetTextureColor((unsigned char)54, (unsigned char)255, (unsigned char)WERandom::GetInt(174, 212), (unsigned char)180);
			WEMtx44::MakeTransform(tranform,
				p_boost[i].scale.x,
				p_boost[i].scale.y,
				0,
				p_boost[i].pos.x,
				p_boost[i].pos.y,
				0);
			WEGraphics::Draw(tranform);
		}

	}

}

//option boost particle
void ParticleManager::OptionInitBoost(Particle *p_boost)
{

	switch (ParticleManager::particle_option_booster)
	{
	case 1:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.1f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.05f, 0.05f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.05f, 0.05f));
		break;
	}
	case 2:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.1f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.05f, 0.05f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.05f, 0.05f));
		break;
	}
	case 3:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.5f, 1.f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.1f, 0.1f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.1f, 0.1f));
		break;
	}
	case 4:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.8f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.3f, 0.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.3f, 0.3f));
		break;
	}
	case 5:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.8f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.2f, 0.2f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.2f, 0.2f));
		break;
	}
	case 6:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.05f, 0.1f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-1.3f, 1.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-1.3f, 1.3f));
		break;
	}
	case 7:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.4f, 0.6f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-30.3f, 30.3f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-30.3f, 30.3f));
		break;
	}
	default:
	{
		p_boost->pos.x = OPTION_BOOSTER_SHIP_X;
		p_boost->pos.y = OPTION_BOOSTER_SHIP_Y;
		p_boost->scale.x = d_Boost_Scale;
		p_boost->scale.y = p_boost->scale.x;
		p_boost->life = WERandom::GetFloat(0.2f, 0.5f);
		p_boost->vel.x = -d_Boost_Vel * cos(WERandom::GetFloat(-0.1f, 0.1f));
		p_boost->vel.y = -d_Boost_Vel * sin(WERandom::GetFloat(-0.1f, 0.1f));
	}
	}
		
}
void ParticleManager::OptionPooozicBoost(Particle *p_boost, float dt)
{
	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		p_boost[i].pos.x += p_boost[i].vel.x;
		p_boost[i].pos.y += p_boost[i].vel.y;
		p_boost[i].life -= dt;

		if (p_boost[i].life < 0)
		{
			OptionInitBoost(d_boost + i);
		}
	}
}
void ParticleManager::OptionDrawBoost(Particle *p_boost, int texture)
{
	WEMtx44 tranform;
	switch (ParticleManager::particle_option_booster)
	{
	case 1:
	{		
		for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)29, (unsigned char)WERandom::GetInt(109, 255), (unsigned char)WERandom::GetInt(109, 255), (unsigned char)200);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	for (int i = 0; i < d_Boost_maxObjects; i += 10)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)152, (unsigned char)WERandom::GetInt(213, 240), (unsigned char)WERandom::GetInt(240, 255), (unsigned char)210);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
		break;
	}
	case 2:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)241, (unsigned char)WERandom::GetInt(31, 212), (unsigned char)31, (unsigned char)221);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
		break;
	}
	case 3:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)29, (unsigned char)WERandom::GetInt(109, 255), (unsigned char)WERandom::GetInt(109, 255), (unsigned char)200);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
		break;
	}
	case 4:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor(36, 255, 196, 219);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 5:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(220, 255), (unsigned char)WERandom::GetInt(0, 30), (unsigned char)WERandom::GetInt(200, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 6:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(200, 255), (unsigned char)231, (unsigned char)WERandom::GetInt(100, 255), (unsigned char)WERandom::GetInt(200, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	break;
	}
	case 7:
	{	for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255), (unsigned char)WERandom::GetInt(0, 255));
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
		break;
	}
	default:
		for (int i = 0; i < d_Boost_maxObjects; ++i)
	{
		WEGraphics::SetTexture(texture);
		WEGraphics::SetTextureColor((unsigned char)54, (unsigned char)255, (unsigned char)WERandom::GetInt(174, 212), (unsigned char)180);
		WEMtx44::MakeTransform(tranform,
			p_boost[i].scale.x,
			p_boost[i].scale.y,
			0,
			p_boost[i].pos.x,
			p_boost[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
	}
}


//BByong particle
void ParticleManager::LoadByebye(Particle *p_byebye)
{
	for (int i = 0; i < d_byebye_maxObjects; ++i)
	{
		p_byebye[i].pos.x   = INITIALIZE_ZERO;
		p_byebye[i].pos.y   = INITIALIZE_ZERO;
		p_byebye[i].vel.x   = INITIALIZE_ZERO;
		p_byebye[i].vel.y   = INITIALIZE_ZERO;
		p_byebye[i].scale.x = INITIALIZE_ZERO;
		p_byebye[i].scale.y = INITIALIZE_ZERO;
		p_byebye[i].store.x = INITIALIZE_ZERO;
		p_byebye[i].store.y = INITIALIZE_ZERO;
		p_byebye[i].rot     = INITIALIZE_ZERO;
		p_byebye[i].rotvel  = INITIALIZE_ZERO;
		p_byebye[i].texture = INITIALIZE_ZERO;
		p_byebye[i].id      = INITIALIZE_ZERO;
		p_byebye[i].life    = INITIALIZE_ZERO;
	}
}
void ParticleManager::InitByebye(Particle *p_byebye, Ship *pship)
{
	d_byebye_Objectcount = d_byebye_maxObjects;
	for (int i = 0; i < d_byebye_maxObjects; ++i)
	{
		d_byebye_Vel = WERandom::GetFloat(0.5, 1.0);
		p_byebye[i].pos.x = pship->pos.x;
		p_byebye[i].pos.y = pship->pos.y;
		p_byebye[i].vel.x = d_byebye_Vel * cos(WEMath::HALF_PI * i);
		p_byebye[i].vel.y = d_byebye_Vel * sin(WEMath::HALF_PI * i);
		
		p_byebye[i].scale.x = d_byebye_Scale;
		p_byebye[i].scale.y = p_byebye[i].scale.x;
		p_byebye[i].life = d_byebye_Vel;
	}
}

void ParticleManager::UpdateByebye(Particle *p_byebye, float &dt)
{
	for (int i = 0; i < d_byebye_maxObjects; ++i)
	{
		p_byebye[i].pos.x += p_byebye[i].vel.x;// * WERandom::GetFloat(-5, 5);
		p_byebye[i].pos.y += p_byebye[i].vel.y;// * WERandom::GetFloat(-5, 5);
		p_byebye[i].life -= dt;
		if (p_byebye[i].life <= 0)
		{
			p_byebye[i].scale.x = 0.0f;
			p_byebye[i].scale.y = 0.0f;
		}

	}

}
void ParticleManager::DrawByebye(Particle *p_byebye, TextureData data)
{
	WEMtx44 tranform;
	for (int i = 0; i < d_byebye_maxObjects; ++i)
	{
		int j = WERandom::GetInt((unsigned char)230, (unsigned char)250);
		WEGraphics::SetTexture(data.circleTexture);
		WEGraphics::SetTextureColor((unsigned char)j, (unsigned char)j, (unsigned char)j, (unsigned char)j);
		WEMtx44::MakeTransform(tranform,
			p_byebye[i].scale.x,
			p_byebye[i].scale.y,
			0,
			p_byebye[i].pos.x,
			p_byebye[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}
