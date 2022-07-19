#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "enemy.h"
#include <vector>

class EnemyPack : public Enemy
{
	graphics::Brush br;
	int members = 11;
	Enemy* enemy = nullptr;	// Enemy object
	// Variable for left-right movement of the pack
	bool right_movement = true;

public:
	//Pack vector foe enemies
	std::vector<Enemy*> pack;	
	void movePack();
	void update() override;
	void draw() override;
	void init() override;
	EnemyPack(const class Game& mygame, graphics::Brush brush, float pos_x, float pos_y, float size, std::string asset_name);
	~EnemyPack();
	Disk getCollisionHull(int i) const;
};