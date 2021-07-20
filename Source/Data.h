/******************************************************************************
\file	Data.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef DATA_H
#define DATA_H

#include "WEInput.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEApplication.h"
#include "WEIntersection.h"
#include "WEDebugTools.h"
#include "WERandom.h"
#include "WEMtx44.h"
#include "WEMath.h"
#include "WEVec2.h"
#include <cstdio>

#include "SoundManager.h"
#include "ObjectManager.h"
#include "ReturnStates.h"
#include "Action.h"
#include "physic.h"


#define MENU_BUTTON_WIDTH 256
#define MENU_BUTTON_HEIGHT 64
#define BUTTON_WIDTH 64
#define BUTTON_HEIGHT 64

#define BUTTON_COUNT 2
#define BUTTON_COUNT_OBJECTS 3
#define ONLY 0
#define XREND 1737.5
#define XLEND -457.5
#define YUEND 977.5
#define YDEND -257.5

#define GO_AWAY 9999
#define ZERO 0
#define BOOL_1 1

#define PLANET_LIFE 7

#define DEFAULT_CAMERA_Z 500
#define DEFAULT_SIZE_PLANET 256
#define DEFAULT_SIZE_ASTEROID 50
#define DEFAULT_SIZE_FUEL 75
#define DEFAULT_SIZE_50 50
#define POSITION_SHIP_X 213
#define POSITION_SHIP_Y 120
#define SIZE_SHIP_X 60
#define SIZE_SHIP_Y 30

#define MAX_LEVEL 15

#define TERM 200

enum GameMode
{
	MENU,
	STORY,
	ADVENTURE,
	CUSTOMMODE,
	CUSTOMINTRO
};

enum EditExplain
{
	NONE,
	MOVE,
	MAGIC
};

struct TextureData 
{
	int playerTexture;
	int markTexture;
	int shipTexture;
	int quitTexture;
	int planetTexture;
	int planetPTexture;
	int goalTexture;
	int menuTexture;
	int replayTexture;
	int launchTexture;
	int asteroidTexture;
	int asteroidPTexture;
	int edgeTexture;
	int boostTexture;
	int saveTexture;
	int DragTheSpaceship;
	int BoosterText;
	int RotationText;
	int ZoomText;
	int RestartText;
	int circleTexture;
	int traceTexture;
	int BoostEdgeTexture;
	int FuelTexture;
	int FuelPTexture;
	int EditOnTexture;

	int preplay;
	int pmenu;
	int leveltext;
	int trytext;
	int pausetext;
	int slotText;

	int number0Texture;
	int number1Texture;
	int number2Texture;
	int number3Texture;
	int number4Texture;
	int number5Texture;
	int number6Texture;
	int number7Texture;
	int number8Texture;
	int number9Texture;

	int EggWaitTexture;
	int EggPasicTexture;
	int EggSleepTexture;
	int EggWakeUpTexture;

	int SaveIconTexture;
	int SaveIconPTexture;
	int EditIconTexture;
	int EditIconPTexture;
	int MagicPenTexture;
	int MagicPenPTexture;
	int MoveTexture;
	int MovePTexture;
	int explain1Texture;
	int explain2Texture;
};

struct EditData
{
	bool isSelected;
	WEVec2 relativeLoc;
	int targetObject;
	int targetType;
};


struct ReturnData
{
	ObjectManager *pOM;
	TextureData TextureData;
	float screenWidth;
	float screenHeight;
	float cameraZ;
	bool isFullScreen;


	int max_objects;
	int max_buttons;
	int max_planets;
	int max_asteroid;
	int max_fuel;
	int max_ship;

	int custom_max_asteroid;
	int custom_max_planet;
	int custom_max_fuel;

	int level;
	int life_count;
	bool editmode;
	int mouseState;

	float camera_time;
	
	bool boostfire;
	
	GameMode game_mode;
	EditExplain explain_button;
};

typedef void(*Action)(void);
#endif