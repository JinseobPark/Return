/******************************************************************************
\file	SoundManager.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "SoundManager.h"
#include "fmod_errors.h"

SoundManager* SoundManager::instance = 0;

SoundManager* SoundManager::sharedManager()
{
	if (instance == 0)
	{
		instance = new SoundManager;
	}
	return instance;
}

void SoundManager::init()
{
	r = System_Create(&pFmod);
	ErrorCheck(r);
	r = pFmod->init(100, FMOD_INIT_NORMAL, 0);
	ErrorCheck(r);
}

//load sounds
void SoundManager::loading()
{
	r = pFmod->createStream("media/mainmenu.ogg", FMOD_LOOP_NORMAL, 0, &music[MAINMENU]);
	ErrorCheck(r);
	r = pFmod->createStream("media/backgound.ogg", FMOD_LOOP_NORMAL, 0, &music[BG]);
	ErrorCheck(r);
	r = pFmod->createSound("media/start.ogg", FMOD_DEFAULT, 0, &music[START]);
	ErrorCheck(r);
	r = pFmod->createSound("media/restart.ogg", FMOD_DEFAULT, 0, &music[RESTART]);
	ErrorCheck(r);
	r = pFmod->createSound("media/goal.ogg", FMOD_DEFAULT, 0, &music[GOAL]);
	ErrorCheck(r);
	r = pFmod->createSound("media/explosion.ogg", FMOD_DEFAULT, 0, &music[EXPLOSION]);
	ErrorCheck(r);
	r = pFmod->createSound("media/splash.ogg", FMOD_DEFAULT, 0, &music[SPLASH]);
	ErrorCheck(r);
	r = pFmod->createSound("media/click.ogg", FMOD_DEFAULT, 0, &music[CLICK]);
	ErrorCheck(r);
	r = pFmod->createSound("media/boost.ogg", FMOD_DEFAULT, 0, &music[BOOST]);
	ErrorCheck(r);
	r = pFmod->createSound("media/clear.ogg", FMOD_DEFAULT, 0, &music[CLEAR]);
	ErrorCheck(r);
	r = pFmod->createSound("media/piyac.ogg", FMOD_DEFAULT, 0, &music[PIYAC]);
	ErrorCheck(r);
}

//play sounds
void SoundManager::play(int _type)
{
	r = pFmod->playSound(FMOD_CHANNEL_FREE, music[_type], false, &ch[_type]);
	ErrorCheck(r);
}

void SoundManager::update(void)
{
	pFmod->update();
}

//stop the sound
void SoundManager::stop(int _chNum)
{
	ch[_chNum]->stop();
}

//delete sound
void SoundManager::deleteMusic(int _type)
{
	delete music[_type];
	music[_type] = 0;
}
void SoundManager::ErrorCheck(FMOD_RESULT _r)
{
	if (_r != FMOD_OK)
	{
		//int error = 0;
		/*
		TCHAR szStr[256] = { 0 };
		MultiByteToWideChar(CP_ACP, NULL, FMOD_ErrorString(r), -1, szStr, 256);
		MessageBox(NULL, szStr, L"Sound Error", MB_OK);
		*/
	}

}
void SoundManager::slience(void)
{
	r = pFmod->close();
	r = pFmod->release();
}