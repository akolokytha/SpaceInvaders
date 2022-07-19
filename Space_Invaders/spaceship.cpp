#include "spaceship.h"
#include "config.h"
#include "game.h"


void Spaceship::update()
{
	// Move left
	pos_x -= 3.0f;
	// if reached outside of the left edge make it not active | game.cpp will delete it
	if (pos_x < (-size / 2))
	{
		active = false;
	}
}

void Spaceship::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "spaceship.png";

	br.fill_opacity = 0.8f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, br);

	if (game.getDebugMode())
	{
		//draw collision block
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;

		std::list<Disk> hull2 = getCollisionHullList();
		for (auto& element : hull2) {
			graphics::drawDisk(element.cx, element.cy, element.radius, br);
		}
	}
}

void Spaceship::init()
{
}

Spaceship::Spaceship(const Game& mygame)
	: GameObject(mygame)
{
}

Spaceship::~Spaceship()
{
}

Disk Spaceship::getCollisionHull() const
{
	return Disk();
}

// Returns a list of Disks for collision check
std::list<Disk> Spaceship::getCollisionHullList() const
{
	std::list<Disk> hulls;

	Disk disk1;
	disk1.cx = pos_x;
	disk1.cy = pos_y;
	disk1.radius = size / 2 * 0.6f;
	hulls.push_back(disk1);

	Disk disk2;
	disk2.cx = (pos_x - size / 4) - 2;
	disk2.cy = (pos_y - size / 12) + 10;
	disk2.radius = size / 2 * 0.4f;
	hulls.push_back(disk2);

	Disk disk3;
	disk3.cx = (pos_x + size / 4) + 2;
	disk3.cy = (pos_y - size / 12) + 10;
	disk3.radius = size / 2 * 0.4f;
	hulls.push_back(disk3);

	return hulls;
}