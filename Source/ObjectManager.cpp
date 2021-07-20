/******************************************************************************
\file   ObjectMAnager.cpp
\title  Return
\author Jinseob Park
\par    GAM150

All content © 2017 DigiPen (USA) Corporation, all rights reserved

******************************************************************************/
#include "ObjectManager.h"
#include "Data.h"

//constructor
ObjectManager::ObjectManager(int max_ship,int max_planets, int max_asteroid, int max_fuel)
{
	m_max_goal = ONLYGOAL;
	m_max_ship = max_ship;
	m_max_planet = max_planets;
	m_max_asteroid = max_asteroid;
	m_max_button = BUTTON_COUNT;
	m_max_mark = ONLYMARK;
	m_max_launch = ONLYLAUNCH;
	m_max_boost = ONLYBOOST;
	m_max_fuel = max_fuel;

	m_ship = new Ship[max_ship];
	m_goal = new Goal[m_max_goal];
	m_button = new Button[BUTTON_COUNT];
	m_edit_save = new Button[BUTTON_COUNT];
	m_edit_objects = new Button[BUTTON_COUNT_OBJECTS];
	m_edit_mouse  = new Button[BUTTON_COUNT];
	m_planet = new Planet[max_planets];
	m_asteroid = new Asteroid[max_asteroid];
	m_launch = new Object[m_max_launch];
	m_mark = new Object[m_max_mark];
	m_edge = new Edge[max_planets];
	m_boost = new Button[m_max_boost];
	m_fuel = new Object[max_fuel];

	m_button_count = COUNT_ZERO;
	m_planet_count = COUNT_ZERO;
	m_asteroid_count = COUNT_ZERO;
	m_ship_count = COUNT_ZERO;
	m_mark_count = COUNT_ZERO;
	m_launch_count = COUNT_ZERO;
	m_goal_count = COUNT_ZERO;
	m_boost_count = COUNT_ZERO;
	m_fuel_count = COUNT_ZERO;
}

//destructor
ObjectManager::~ObjectManager(void)
{

		delete[] m_button;
		m_button = INITIALIZE_ZERO;
		delete[] m_planet;
		m_planet = INITIALIZE_ZERO;
		delete[] m_asteroid;
		m_asteroid = INITIALIZE_ZERO;
		delete[] m_goal;
		m_goal = INITIALIZE_ZERO;
		delete[] m_mark;
		m_mark = INITIALIZE_ZERO;
		delete[] m_ship;
		m_ship = INITIALIZE_ZERO;
		delete[] m_edit_objects;
		m_edit_objects = INITIALIZE_ZERO;
		delete[] m_edit_mouse;
		m_edit_mouse = INITIALIZE_ZERO;
		delete[] m_edit_save;
		m_edit_save = INITIALIZE_ZERO;
		delete[] m_boost;
		m_boost = INITIALIZE_ZERO;
		delete[] m_edge;
		m_edge = INITIALIZE_ZERO;
		delete[] m_fuel;
		m_fuel = INITIALIZE_ZERO;

}


//Ship Object
 Ship* ObjectManager::GetShip(void)
{
	return m_ship;
}

void ObjectManager::SetShip(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel,
	float power, float distance,
	float angle, float mass,float boostGauge, int texture
	, ShipType shiptype, ShipLife shiplife)
{
	if (m_ship_count < m_max_ship)
	{
		m_ship[m_ship_count].texture = texture;
		m_ship[m_ship_count].pos = pos;
		m_ship[m_ship_count].scale = scale;
		m_ship[m_ship_count].vel = vel;
		m_ship[m_ship_count].power = power;
		m_ship[m_ship_count].distance = distance;
		m_ship[m_ship_count].angle = angle;
		m_ship[m_ship_count].mass = mass;
		m_ship[m_ship_count].boostGauge = boostGauge;
		m_ship[m_ship_count].angleAuto = false;
		m_ship[m_ship_count].shiptype = shiptype;
		m_ship[m_ship_count].shiplife = shiplife;
	}
}


//Planet Object
Planet* ObjectManager::GetPlanet(void)
{
	return m_planet;
}
int ObjectManager::GetPlanetCount(void) //const
{
	return m_planet_count;
}
void ObjectManager::SetPlanet(const WEVec2& pos, const WEVec2& scale, float gravity,
	float mass, bool pull, bool count, int texture, int planet_id, int life)
{
	if (planet_id < m_max_planet)
	{
		m_planet[planet_id].pos = pos;
		m_planet[planet_id].scale = scale;
		m_planet[planet_id].gravity = gravity;
		m_planet[planet_id].mass = mass;
		m_planet[planet_id].pull = pull;
		m_planet[planet_id].count = count;
		m_planet[planet_id].texture = texture;
		m_planet[planet_id].life = life;
	}
}

void ObjectManager::SetPlanet(const WEVec2& pos, const WEVec2& scale, float gravity,
	float mass,int texture, int planet_id, int life)
{
	if (planet_id < m_max_planet)
	{
		m_planet[planet_id].pos = pos;
		m_planet[planet_id].scale = scale;
		m_planet[planet_id].gravity = gravity;
		m_planet[planet_id].mass = mass;
		m_planet[planet_id].pull = true;
		m_planet[planet_id].count = true;
		m_planet[planet_id].texture = texture;
		m_planet[planet_id].life = life;
	}
}


//planet edge object
Edge* ObjectManager::GetPlanetEdge(void)
{
	return m_edge;
}
void ObjectManager::SetPlanetEdge(const WEVec2& pos, const WEVec2& scale, int texture, int planet_id)
{
	m_edge[planet_id].pos = pos;
	m_edge[planet_id].scale = scale;
	m_edge[planet_id].texture = texture;
}

//Goal
Goal* ObjectManager::GetGoal(void)
{
	return m_goal;
}

void  ObjectManager::SetGoal(const WEVec2& pos, const WEVec2& scale, int texture)
{
	m_goal[m_goal_count].pos = pos;
	m_goal[m_goal_count].scale = scale;
	m_goal[m_goal_count].texture = texture;
}


//asteroid
Asteroid* ObjectManager::GetAsteroid(void)
{
	return m_asteroid;
}
int ObjectManager::GetAsteroidCount(void) 
{
	return m_asteroid_count;
}
void ObjectManager::SetAsteroid(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float rotate, int texture, int asteroid_count)
{
	if (asteroid_count < m_max_asteroid)
	{
		m_asteroid[asteroid_count].pos = pos;
		m_asteroid[asteroid_count].scale = scale;
		m_asteroid[asteroid_count].vel = vel;
		m_asteroid[asteroid_count].rotate = rotate;
		m_asteroid[asteroid_count].texture = texture;
	}

}

//button
Button* ObjectManager::GetButton(void)
{
	return m_button;
}
void ObjectManager::SetButton(const WEVec2& pos, const WEVec2& scale, int button_count, int texture)
{
	if (button_count < m_max_button)
	{
		m_button[button_count].pos = pos;
		m_button[button_count].scale = scale;
		m_button[button_count].texture = texture;
	}

}

//Edit object button object
Button* ObjectManager::GetEditObjects(void)
{
	return m_edit_objects;
}
void ObjectManager::SetEditObjects(const WEVec2& pos, const WEVec2& scale, int button_count, int texture)
{
	if (button_count < BUTTON_COUNT_OBJECTS)
	{
		m_edit_objects[button_count].pos = pos;
		m_edit_objects[button_count].scale = scale;
		m_edit_objects[button_count].texture = texture;
	}
}

//Edit mouse button object
Button* ObjectManager::GetEditMouse(void)
{
	return m_edit_mouse;
}
void ObjectManager::SetEditMouse(const WEVec2& pos, const WEVec2& scale, int button_count, int texture)
{
	if (button_count < BUTTON_COUNT)
	{
		m_edit_mouse[button_count].pos = pos;
		m_edit_mouse[button_count].scale = scale;
		m_edit_mouse[button_count].texture = texture;
	}

}

//Edit Save&Edit button object
Button* ObjectManager::GetEditSave(void)
{
	return m_edit_save;
}
void ObjectManager::SetEditSave(const WEVec2& pos, const WEVec2& scale, int button_count, int texture)
{
	if (button_count < BUTTON_COUNT)
	{
		m_edit_save[button_count].pos = pos;
		m_edit_save[button_count].scale = scale;
		m_edit_save[button_count].texture = texture;
	}
}

//Mark object 
Object* ObjectManager::GetMark(void)
{
	return m_mark;
}
void ObjectManager::SetMark(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture)
{
	if (m_mark_count < m_max_mark)
	{
		m_mark[m_mark_count].pos = pos;
		m_mark[m_mark_count].scale = scale;
		m_mark[m_mark_count].vel = vel;
		m_mark[m_mark_count].angle = angle;
		m_mark[m_mark_count].texture = texture;
		++m_mark_count;
	}
}

//launch object
Object* ObjectManager::GetLaunch(void)
{
	return m_launch;
}
void ObjectManager::SetLaunch(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture)
{
	m_launch[m_launch_count].pos = pos;
	m_launch[m_launch_count].scale = scale;
	m_launch[m_launch_count].vel = vel;
	m_launch[m_launch_count].angle = angle;
	m_launch[m_launch_count].texture = texture;
}


//Fuel object
int ObjectManager::GetFuelCount(void)
{
	return m_fuel_count;
}

Object* ObjectManager::GetFuel(void)
{
	return m_fuel;
}

void ObjectManager::SetFuel(const WEVec2& pos, const WEVec2& scale, const WEVec2& vel, float angle, int texture, int fuel_count)
{
	if (fuel_count < m_max_fuel)
	{
		m_fuel[fuel_count].pos = pos;
		m_fuel[fuel_count].scale = scale;
		m_fuel[fuel_count].vel = vel;
		m_fuel[fuel_count].angle = angle;
		m_fuel[fuel_count].texture = texture;
	}
}

//Boost object
Button* ObjectManager::GetBoost(void)
{
	return m_boost;
}
void ObjectManager::SetBoost(const WEVec2& pos, const WEVec2& scale, int texture)
{
		m_boost[m_boost_count].pos = pos;
		m_boost[m_boost_count].scale = scale;
		m_boost[m_boost_count].texture = texture;
}


//For Editor
//planet
void ObjectManager::IncPlanetCount(void)
{
	m_planet_count++;
}
void ObjectManager::DecPlanetCount(void)
{
	m_planet_count--;
}
//asteroid
void ObjectManager::IncAsteroidCount(void)
{
	m_asteroid_count++;
}
void ObjectManager::DecAsteroidCount(void)
{
	m_asteroid_count--;
}
//fuel
void ObjectManager::IncFuelCount(void)
{
	m_fuel_count++;
}
void ObjectManager::DecFuelCount(void)
{
	m_fuel_count--;
}