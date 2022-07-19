#include "player.h"
#include "game.h"

Player::Player(const Game& mygame)
	: GameObject(mygame)
{
}

void Player::update()
{
	// Player object moves left if user press left button
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
		pos_x -= speed * graphics::getDeltaTime() / 50.0f;
	}
	// Player object moves right if user press right button
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
		pos_x += speed * graphics::getDeltaTime() / 50.0f;
	}

	// Player object can shoot if user press space
	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		shooting = true;
	}
	else
	{
		shooting = false;
	}

	// Player can't move outside the window edges
	if (pos_x < size / 2)
	{
		pos_x = size / 2;
	}
	if (pos_x > CANVAS_WIDTH - size / 2)
	{
		pos_x = CANVAS_WIDTH - size / 2;
	}
}

void Player::draw()
{
	//draw player object
	br.texture = std::string(ASSET_PATH) + "player.png";
	br.fill_opacity = 0.8f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, 30, br);

	//Show collision block on debug mode
	if (game.getDebugMode())
	{
		graphics::Brush brush;
		brush.outline_opacity = 1.0f;
		brush.texture = "";
		brush.fill_color[0] = 1.0f;
		brush.fill_color[1] = 0.3f;
		brush.fill_color[2] = 0.3f;
		brush.fill_opacity = 0.3f;
		brush.gradient = false;

		std::list<Disk> hull2 = getCollisionHullList();
		for (auto& element : hull2) {
			graphics::drawDisk(element.cx, element.cy, element.radius, brush);
		}
	}
}

void Player::init()
{
}

// Return disk to check for collisions | Not used in this game
Disk Player::getCollisionHull() const
{
	Disk  disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;
	return disk;
}

// Returns a list of Disks for collision check
std::list<Disk> Player::getCollisionHullList() const
{
	std::list<Disk> hulls;

	Disk disk1;
	disk1.cx = pos_x;
	disk1.cy = pos_y;
	disk1.radius = size / 2 * 0.5f;
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