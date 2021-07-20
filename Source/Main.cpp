/******************************************************************************
\file   Main.cpp
\title  Return
\author Jinseob Park
\par    GAM150
\brief
  this file is main start file of game.
	All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "WEMemory.h"
/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/

/******************************************************************************/

#include <windows.h> /*WinMain*/ 

/*Include the engine functions*/
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEState.h"
#include "WEGameData.h"

#include "SoundManager.h"
#include "DigipenSplashState.h"
#include "TeamLogoState.h"
#include "GameMenu.h"
#include "Option.h"
#include "Credit.h"
#include "Story.h"
#include "Thank.h"
#include "LevelEditor.h"
#include "LevelSelect.h"
#include "WEDebugTools.h"
#include "Adventure.h"
#include "CustomIntro.h"
#include "CustomMode.h"
#include "StoryIntro.h"

/******************************************************************************/
/*!
The user must add states to their game After initializing the Application, and 
before updating the Application.

\attention
To make switching states easier, I add the states in the order they are listed
in the DemoStates enum.
*/
/******************************************************************************/
void DemoAddStates(void)
{
	WEState state;
	int stateID;
	state.Load = SplashStateLoad;
	state.Init = SplashStateInit;
	state.Update = SplashStateUpdate;
	state.Shutdown = SplashStateShutdown;
	state.Unload = SplashStateUnload;

	stateID = WEStateManager::AddState(state);
	WEStateManager::SetStartState(stateID);

	state.Load = TeamLogoStateLoad;
	state.Init = TeamLogoStateInit;
	state.Update = TeamLogoStateUpdate;
	state.Shutdown = TeamLogoStateShutdown;
	state.Unload = TeamLogoStateUnload;

	WEStateManager::AddState(state);

	state.Load = MenuLoad;
	state.Init = MenuInit;
	state.Update = MenuUpdate;
	state.Shutdown = MenuShutdown;
	state.Unload = MenuUnload;

	WEStateManager::AddState(state);

	state.Load = OptionLoad;
	state.Init = OptionInit;
	state.Update = OptionUpdate;
	state.Shutdown = OptionShutdown;
	state.Unload = OptionUnload;

	WEStateManager::AddState(state);

	state.Load = CreditLoad;
	state.Init = CreditInit;
	state.Update = CreditUpdate;
	state.Shutdown = CreditShutdown;
	state.Unload = CreditUnload;

	WEStateManager::AddState(state);

	state.Load = LSLoad;
	state.Init = LSInit;
	state.Update = LSUpdate;
	state.Shutdown = LSShutdown;
	state.Unload = LSUnload;

	WEStateManager::AddState(state);

	state.Load = StoryLoad;
	state.Init = StoryInit;
	state.Update = StoryUpdate;
	state.Shutdown = StoryShutdown;
	state.Unload = StoryUnload;



	WEStateManager::AddState(state);

	state.Load     =SILoad;
	state.Init     =SIInit;
	state.Update   =SIUpdate;
	state.Shutdown =SIShutdown;
	state.Unload   =SIUnload;
		
	WEStateManager::AddState(state);

	state.Load     = AdventureLoad;
	state.Init     = AdventureInit;
	state.Update   = AdventureUpdate;
	state.Shutdown = AdventureShutdown;
	state.Unload   = AdventureUnload;

	WEStateManager::AddState(state);

	state.Load = CustomIntLoad;
	state.Init = CustomIntInit;
	state.Update = CustomIntUpdate;
	state.Shutdown = CustomIntShutdown;
	state.Unload = CustomIntUnload;

	WEStateManager::AddState(state);

	state.Load = CustomModeLoad;
	state.Init = CustomModeInit;
	state.Update = CustomModeUpdate;
	state.Shutdown = CustomModeShutdown;
	state.Unload = CustomModeUnload;

	WEStateManager::AddState(state);

	state.Load = LevelEditorLoad;
	state.Init = LevelEditorInit;
	state.Update = LevelEditorUpdate;
	state.Shutdown = LevelEditorShutdown;
	state.Unload = LevelEditorUnload;

	WEStateManager::AddState(state);

	state.Load = ThankStateLoad;
	state.Init = ThankStateInit;
	state.Update = ThankStateUpdate;
	state.Shutdown = ThankStateShutdown;
	state.Unload = ThankStateUnload;

	WEStateManager::AddState(state);
}

/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance 
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show 
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/, 
                   LPSTR /*commandLine*/, 
                   int /*show*/)
{
	WEDEBUG_CREATE_CONSOLE();

  /*Declare my InitStruct*/
  WEInitData initStruct;
  /*Create my game data initial values*/
  WEGameData gameData = { 0 };

  /*Set up my InitStruct*/
  initStruct.instance   = instance;
  initStruct.width      = 1280;
  initStruct.height     = 720;
  initStruct.title      = "Return";
  initStruct.fps        = 60;
  initStruct.fullScreen = true;

  /*Information about your specific gamedata */
  initStruct.pGData       = &gameData;
  initStruct.gameDataSize = sizeof(WEGameData);


  /*Pass InitStruct to Function.  This function must be called first!!!*/
  WEApplication::Init(initStruct);
  SoundManager::sharedManager()->init();
  /*Function to add all of my game states*/
  DemoAddStates();
  /*Start running the game*/
  WEApplication::Update();
  /*This function must be called after the window has closed!!!*/

   WEApplication::Shutdown();

   WEDEBUG_DESTROY_CONSOLE();
  return 0;
}

