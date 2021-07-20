/******************************************************************************
\file	Particle.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "Data.h"


#define OPTION_INITIAL_NUMBER 1
#define INITIALIZE_ZERO 0
#define OPTION_EXPLODE_SHIP_X 710
#define OPTION_EXPLODE_SHIP_Y 300
#define OPTION_BOOSTER_SHIP_X 730
#define OPTION_BOOSTER_SHIP_Y 150

struct Particle
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	WEVec2 store;
	float rot;
	float rotvel;
	int texture;
	int id;
	float life;
};


class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager(void);
	

	Particle* GetBG(void);
	Particle* GetExplode(void);
	Particle* GetBoost(void);
	Particle* GetByebye(void);


	void ParticleLoad(const char* pFileName);

	void LoadBG(Particle *p_background);
	void InitBG(Particle *p_background,int texture);
	void AD_InitBG(Particle *p_background, TextureData const data);
	void UpdateBG(Particle *p_background, float dt);
	void DrawBG(Particle *p_background);

	void LoadCrashing(Particle *p_explode);
	void InitCrashing(Particle *p_explode, Ship *pship);
	void UpdateCrashing(Particle *p_explode, float &dt);
	void DrawCrasing(Particle *p_explode, TextureData data);

	void OptionInitCrasing(Particle *p_explode);
	void OptionUpdateCrashing(Particle *p_explode, float &dt);
	void OptionDrawCrasing(Particle *p_explode, int texture);

	void LoadBoosting(Particle *p_boost);
	void InitBoosting(Particle *p_boost, Ship *pship);
	void PooozicBoosting(Particle *p_boost, Ship *pship, float dt, ReturnData &data);
	void DrawBoosting(Particle *p_boost, TextureData data);
	
	void OptionInitBoost(Particle *p_boost);
	void OptionPooozicBoost(Particle *p_boost, float dt);
	void OptionDrawBoost(Particle *p_boost, int texture);



	void LoadByebye(Particle *p_byebye);
	void InitByebye(Particle *p_byebye, Ship *pship);
	void UpdateByebye(Particle *p_byebye, float &dt);
	void DrawByebye(Particle *p_byebye, TextureData data);


	static int particle_option_booster;
	static int particle_option_explode;

private:
	Particle* d_background;
	Particle* d_explode;
	Particle* d_boost;
	Particle* d_byebye;

	int d_BG_maxObjects;
	int d_BG_Objectcount;
	float d_BG_maxScale;
	float d_BG_minScale;
	float d_BG_maxVel;
	float d_BG_minVel;

	int d_Explode_maxObjects;
	int d_Explode_Objectcount;
	float d_Explode_Vel;
	float d_Explode_Scale;
	float d_Explode_Life;

	int   d_Boost_Objectcount;
	int   d_Boost_maxObjects;
	float d_Boost_Vel;
	float d_Boost_Scale;
	float d_Boost_Vec;
	float d_Boost_Life;
	float d_Boost_Time;

	int d_byebye_maxObjects;
	int d_byebye_Objectcount;
	float d_byebye_Vel;
	float d_byebye_Scale;
	float d_byebye_Life;

};


#endif