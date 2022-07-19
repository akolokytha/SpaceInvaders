#include "shot.h"
#include "config.h"
#include "game.h"

void Shot::update()
{
	// If shot created from enemy
	if (enemy)
	{
		pos_y = pos_y + 4.0f;
	}
	// If shot created from player
	else
	{
		pos_y = pos_y - 7.0f;
	}
	// if shot reached the edge of the window, deactive it to delete it later
	if (pos_y > CANVAS_HEIGHT || pos_y < 0)
	{
		active = false;
	}
}

void Shot::draw()
{
	//draw shot object
	brush.texture = std::string(ASSET_PATH) + "fire.png";
	brush.fill_opacity = 1.0f;
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

void Shot::init()
{
}

// Return disk to check for collisions
Disk Shot::getCollisionHull() const
{
	Disk  disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;
	return disk;
}

Shot::Shot(const Game& mygame, bool enemy, float px, float py)
	: GameObject(mygame)
{
	this->pos_x = px;
	if (enemy)
	{
		this->enemy = enemy;
		this->pos_y = py + 10.0f;
	}
	else
	{
		this->player = !enemy;
		this->pos_y = py - 10.0f;
	}
}

Shot::~Shot()
{
}