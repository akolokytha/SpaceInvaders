#include "enemy.h"
#include "config.h"
#include "graphics.h"
#include "game.h"

void Enemy::update()
{	
	if (pos_x < (- size /2) || pos_x > (CANVAS_WIDTH + size/2))
	{
		this->active = false;
	}
}

void Enemy::draw()
{
	//draw enemy object
	brush.texture = std::string(ASSET_PATH) + asset;
	brush.fill_opacity = 0.8f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);

	//Show collision block on debug mode
	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;

		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Enemy::init()
{
}

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
}

Enemy::Enemy(const Game& mygame, graphics::Brush brush, float pos_x, float pos_y, float size, std::string asset_name)
	: GameObject(mygame)
{
	if (asset_name == "squid.png")
	{
		this->value = 30;
	}
	else if (asset_name == "crab.png")
	{
		this->value = 20;
	}
	else
	{
		this->value = 10;
	}
	this->brush = brush;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->size = size;
	this->asset = asset_name;
	init();
}

Enemy::~Enemy()
{
}

//Return disk to check for collisions
Disk Enemy::getCollisionHull() const
{
	Disk  disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;
	return disk;
}
