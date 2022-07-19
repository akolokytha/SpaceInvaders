#pragma once
#include "gameobject.h"
#include "graphics.h"
#include <list>

class Spaceship : public GameObject, public Collidable
{
	graphics::Brush brush;
	float pos_x = 550.0f;
	float pos_y = 60.0f;
	float size = 70.0f;
	int value = 50;
	bool active = true;
public:
	// Get methods
	bool getActive() const { return active; }
	int getValue() const { return value; }

	// Set method
	void setActive(bool a) { active = a; }

	void update() override;
	void draw() override;
	void init() override;
	Spaceship(const class Game& mygame);
	~Spaceship();
	Disk getCollisionHull() const override;
	std::list<Disk> getCollisionHullList() const;
};