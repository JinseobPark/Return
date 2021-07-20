/******************************************************************************
\file	SoundManager.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod.hpp"

#pragma comment(lib, "fmodex_vc.lib")
using namespace FMOD;

enum SOUND {
	MAINMENU = 0, BG, CLICK, START, RESTART, GOAL, EXPLOSION, SPLASH, BOOST, CLEAR, PIYAC
};

class SoundManager {
private:
	SoundManager(void) { ; }

public:
	~SoundManager() { delete instance; }
	static SoundManager* instance;
	static SoundManager* sharedManager(void);
	void init(void);
	void loading(void);
	void update(void);
	void play(int _type);
	void stop(int _chNum);
	void ErrorCheck(FMOD_RESULT _r);
	void deleteMusic(int _type);
	void slience(void);

private:
	System*   pFmod;
	Channel*  ch[12];
	Sound*    music[12];
	FMOD_RESULT r;
};

#endif