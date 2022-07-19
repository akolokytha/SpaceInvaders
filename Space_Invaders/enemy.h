#pragma once
#include "graphics.h"
#include "gameobject.h"
#include "shot.h"

class Enemy : public GameObject, public Collidable
{
	graphics::Brush brush;
	float pos_x, pos_y;
	std::string asset;
	float size;
	int value;
	// all enemies can shoot at start | We update it at game.cpp
	bool can_shoot = true;	
	// all enemies are active at start
	bool active = true;	
public:
	//set methods
	void setPosx(float px) { pos_x = px; }
	void setPosy(float py) { pos_y = py; }
	void setCanShoot(bool cs) { can_shoot = cs; }
	void setActive(bool act) { active = act; }
	//get methods
	float getPosx() const { return pos_x; }
	float getPosy() const { return pos_y; }
	float getSize() const { return size; }
	int getValue() const { return value; }
	bool getCanShoot() const { return can_shoot; }
	bool getActive() const { return active; }

	void update() override;
	void draw() override;
	void init() override;
	Enemy(const class Game& mygame);
	Enemy(const class Game& mygame, graphics::Brush br, float px, float py, float s, std::string asset_name);
	~Enemy();
	Disk getCollisionHull() const override;
};