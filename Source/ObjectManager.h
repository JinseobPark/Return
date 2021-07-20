/******************************************************************************
\file	ObjectMAnager.h
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

//#pragma once
#include "Struct.h"

#define ONLYGOAL 1
#define ONLYMARK 1
#define ONLYBOOST 1
#define ONLYLAUNCH 1
#define COUNT_ZERO 0
#define INITIALIZE_ZERO 0

class ObjectManager
{
public:
	//constructor
	ObjectManager(int max_ship, int max_planet, int max_asteroid, int max_fuel);
	//destructor
	~ObjectManager(void);

	
	//space ship object
	Ship* GetShip(void);
	void SetShip(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float power, float distance,
		float angle,float mass, float boostGauge, int texture, ShipType shiptype, ShipLife shiplife);

	//planet object
	Planet* GetPlanet(void);
	int GetPlanetCount(void);
	void SetPlanet(const WEVec2& pos, const WEVec2& scale, float gravity,
		float mass, bool pull, bool count, int texture, int planet_id, int life);
	void SetPlanet(const WEVec2& pos, const WEVec2& scale, float gravity,
		float mass, int texture, int planet_id, int life);

	//planet edge object
	Edge* GetPlanetEdge(void);
	void SetPlanetEdge(const WEVec2& pos, const WEVec2& scale, int texture, int planet_id);


	//Goal object
	Goal* GetGoal(void);
	void  SetGoal(const WEVec2& pos, const WEVec2& scale, int texture);

	//Asteroid object
	Asteroid* GetAsteroid(void);
	int GetAsteroidCount(void) ;
	void ObjectManager::SetAsteroid(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float rotate, int texture, int asteroid_count);

	//Button object
	Button* GetButton(void);
	void SetButton(const WEVec2& pos, const WEVec2& scale, int button_count, int texture);



	//Mark object (mark, launch)
	Object* GetMark(void);
	void SetMark(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture);

	//launch object (mark, launch)
	Object* GetLaunch(void);
	void SetLaunch(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture);


	//fuel object
	Object* GetFuel(void);
	int GetFuelCount(void);
	void SetFuel(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture, int fuel_count);


	//Boost object
	Button* GetBoost(void);
	void SetBoost(const WEVec2& pos, const WEVec2& scale, int texture);

	//Edit object button object
	Button* GetEditObjects(void);
	void SetEditObjects(const WEVec2& pos, const WEVec2& scale, int button_count, int texture);

	//Edit mouse button object
	Button* GetEditMouse(void);
	void SetEditMouse(const WEVec2& pos, const WEVec2& scale, int button_count, int texture);

	//Edit Save&Edit button object
	Button* GetEditSave(void);
	void SetEditSave(const WEVec2& pos, const WEVec2& scale, int button_count, int texture);

	//For Editor
	void IncPlanetCount(void);
	void DecPlanetCount(void);
	void IncAsteroidCount(void);
	void DecAsteroidCount(void);
	void IncFuelCount(void);
	void DecFuelCount(void);

private:
	Ship     *m_ship;
	Object   *m_object;
	Object   *m_mark;
	Object   *m_launch;
	Object   *m_fuel;
	Edge     *m_edge;
	Planet   *m_planet;
	Asteroid *m_asteroid;
	Goal     *m_goal;
	Button   *m_edit_objects;
	Button   *m_edit_mouse;
	Button   *m_edit_save;
	Button   *m_boost;
	Button   *m_button;

	int m_max_ship;
	int m_max_button;
	int m_max_planet;
	int m_max_goal;
	int m_max_asteroid;
	int m_max_object;
	int m_max_mark;
	int m_max_launch;
	int m_max_boost;
	int m_max_fuel;
	

	int m_ship_count;
	int m_button_count;
	int m_planet_count;
	int m_asteroid_count;
	int m_goal_count;
	int m_object_count;
	int m_mark_count;
	int m_launch_count;
	int m_boost_count;
	int m_fuel_count;
};

#endif