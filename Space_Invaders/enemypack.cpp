#include "enemypack.h"
#include "config.h"

void EnemyPack::movePack()
{
	for (int i = 0; i < members; ++i)
	{
		if (right_movement && pack[i])
		{
			// Each pack member moves right
			pack[i]->setPosx(pack[i]->getPosx() + 0.6f);
			// Enemies of the pack need to stay next to each other | Each member needs to collide with others
			if (i != 10)
			{
				for (int j = i + 1; j < members; ++j)
				{
					if (pack[i] && pack[j] && i < 10)
					{
						// Calculate distance for collision
						Disk d1 = pack[j]->getCollisionHull();
						Disk d2 = pack[i]->getCollisionHull();
						float dx = d1.cx - d2.cx;
						float dy = d1.cy - d2.cy;
						if (sqrt(dx * dx + dy * dy) > d1.radius + d2.radius)
						{
							pack[i]->setPosx(pack[j]->getPosx() - ((j-i) * (pack[i]->getSize())));
						}
					}
				}
			}	
			/*
				Stop movement when reached the end of the canvas -> Right edge
				Check if the rightest member reached the right limit of the screen
			*/
			bool found = false;
			for (int k = 10; k > 0; --k)
			{
				if (found) break;
				if (pack[k] && pack[i] && (pack[k]->getPosx() > (CANVAS_WIDTH - (pack[k]->getSize() / 2) - ((10-k) * pack[k]->getSize()))))
				{
					right_movement = false;
					found = true;
					// All pack members move downwards if the pack touched the edge
					for (auto& member : this->pack)
					{
						if (member)
							member->setPosy(member->getPosy() + (member->getSize() / 14));
					}
				}
			}
		}
		else if (pack[i] && !right_movement)
		{
			// Each pack member moves left
			pack[i]->setPosx(pack[i]->getPosx() - 0.6f);
			// Enemies of the pack need to stay next to each other | Each member needs to collide with others
			if (i != 0)
			{
				for (int a = i - 1; a > 0; --a)
				{
					if (pack[i] && pack[a] && i > 0)
					{
						//calculate distance for collision
						Disk d1 = pack[a]->getCollisionHull();
						Disk d2 = pack[i]->getCollisionHull();
						float dx = d1.cx - d2.cx;
						float dy = d1.cy - d2.cy;
						if (sqrt(dx * dx + dy * dy) > d1.radius + d2.radius)
						{
							pack[i]->setPosx(pack[a]->getPosx() + ((i - a) * (pack[i]->getSize())));
						}
					}
				}
			}
			/*
				Stop movement when reached the end of the canvas -> Left edge
				Check if the rightest member reached the right limit of the screen
			*/
			bool found2 = false;
			for (int m = 0; m < 10; ++m)
			{
				if (found2) break;
				if (pack[m] && pack[i] && pack[m]->getPosx() < (0.0f + (pack[m]->getSize() / 2) + (m * pack[m]->getSize())))
				{
					right_movement = true;
					found2 = true;
					// All pack members move downwards if the pack touched the edge
					for (auto& member : this->pack)
					{
						if (member)
							member->setPosy(member->getPosy() + (member->getSize() / 14));
					}
				}
			}
		}
	}
}

//(0.0f + (pack[m]->getSize() / 2) +   + mia) meta to getsize
void EnemyPack::update()
{
	for (auto& member : this->pack)
	{
		if (member)
		{
			if (!member->getActive())
			{
				delete member;
				member = nullptr;
			}
			else
			{
				member->update();
			}
		}
	}
	movePack();
}

void EnemyPack::draw()
{
	for (auto& member : this->pack)
	{
		if (member)
			member->draw();
	}
}

void EnemyPack::init()
{
}

EnemyPack::EnemyPack(const class Game& mygame, graphics::Brush brush, float pos_x, float pos_y, float size, std::string asset_name)
	:  Enemy(mygame, brush, pos_x, pos_y, size, asset_name)
{	
	for (int i = 0; i < members; ++i)
	{
		enemy = new Enemy(mygame, brush, pos_x + (i*40.0f), pos_y, size, asset_name);
		pack.push_back(enemy);
	}
}

EnemyPack::~EnemyPack()
{
}

// Return disk to check for collisions
Disk EnemyPack::getCollisionHull(int i) const
{
	Disk  disk;
	disk.cx = pack[i]->getPosx();
	disk.cy = pack[i]->getPosy();
	disk.radius = pack[i]->getSize() * 0.45f;
	return disk;
}