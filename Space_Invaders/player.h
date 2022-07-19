#pragma once
#include "gameobject.h"
#include "config.h"
#include "graphics.h"
#include <list>

class Player : public GameObject, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT - 30;
	float size = 60.0f;
	float speed = 10.0f;
	int lives = 3;
	int score = 0;
	// Variable to check if player shoots
	bool shooting;
	graphics::Brush br;

public:
	//set methods
	void setScore(int s) { score = s; }
	void setLives(int l) { lives = l; }
	void setPosX(float px) { pos_x = px; }
	//get methods
	int getScore() const { return score; }
	int getLives() const { return lives; }
	float getPosX() const { return pos_x; }
	float getPosY() const { return pos_y;}
	bool getShooting() const { return shooting; }

	Player(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;

	std::list<Disk> getCollisionHullList() const;
};