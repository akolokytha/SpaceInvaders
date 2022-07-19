#pragma once
#include "gameobject.h"
#include "graphics.h"

class Shot : public GameObject, public Collidable
{
	graphics::Brush brush;
	float pos_x, pos_y;
	float size = 25.0f;
	bool enemy = false;		// Show if shot created from enemy
	bool player = false;	// Show if shot created from player
	bool active = true;		// All shots are active when first created
public:
	//set methods
	void setActive(bool a) { active = a; }
	void setPosy(float py) { pos_y = py; }
	//get methods
	bool getActive() const { return active; }
	bool getEnemy() const { return enemy; }
	
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;
	Shot(const class Game& mygame, bool enemy, float px, float py);
	~Shot();
};