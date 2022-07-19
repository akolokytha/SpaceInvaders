#include "game.h"
#include "graphics.h"
#include "config.h"

// Check objects collisions
void Game::checkCollision()
{
	// If an enemy's shot touch the player, player lose a life and shot is not active anymore
	for (auto& enemy_shot : enemy_shots)
	{
		if (enemy_shot)
		{
			Disk d1 = enemy_shot->getCollisionHull();
			for (auto& circle : player->getCollisionHullList())
			{
				// Calculate distance
				Disk d2 = circle;
				float dx = d1.cx - d2.cx;
				float dy = d1.cy - d2.cy;
				if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
				{
					enemy_shot->setActive(false);
					player->setLives(player->getLives() - 1);
				}
			}
		}
	}
	// If a player's shot touch an enemy, enemy dies, player's score increase and shot is not active anymore
	for (auto& player_shot : player_shots)
	{
		if (player_shot)
		{
			Disk d1 = player_shot->getCollisionHull();
			if (!pack_vector.empty())
			{
				for (int i = 0; i < pack_vector.size(); i++)
				{
					for (int j = 0; j < pack_vector[i]->pack.size(); j++)
					{
						if (pack_vector[i]->pack[j])
						{
							// Calculate distance
							Disk d2 = pack_vector[i]->pack[j]->getCollisionHull();
							float dx = d1.cx - d2.cx;
							float dy = d1.cy - d2.cy;
							if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
							{
								player_shot->setActive(false);
								if (i < 4 && pack_vector[i + 1]->pack[j])
								{
									pack_vector[i + 1]->pack[j]->setCanShoot(true);
								}
								pack_vector[i]->pack[j]->setActive(false);
								player->setScore(player->getScore() + pack_vector[i]->pack[j]->getValue());
							}
						}		
					}				
				}
			}
			if (spaceship)
			{
				Disk d1 = player_shot->getCollisionHull();
				for (auto& circle : spaceship->getCollisionHullList())
				{
					// Calculate distance
					Disk d2 = circle;
					float dx = d1.cx - d2.cx;
					float dy = d1.cy - d2.cy;
					if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
					{
						player_shot->setActive(false);
						player->setScore(player->getScore() + spaceship->getValue());
						spaceship_kills += 1;
						spaceship->setActive(false);
					}
				}
			}
		}
	}
	// If enemy touch player, player lose
	for (auto& pack : pack_vector)
	{
		for (auto& enemy : pack->pack)
		{
			if (enemy)
			{
				Disk d1 = enemy->getCollisionHull();
				for (auto& circle : player->getCollisionHullList())
				{
					// Calculate distance
					Disk d2 = circle;
					float dx = d1.cx - d2.cx;
					float dy = d1.cy - d2.cy;
					if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
					{
						touched_player = true;
					}
				}
			}
		}
	}
		
}

void Game::update()
{
	if (getStatusMode() == STATUS_USER_LOGIN_SCREEN)
	{
		updateLoginScreen();
	}
	else if (getStatusMode() == STATUS_MAIN_MENU)
	{
		updateMenuScreen();
	}
	else if (getStatusMode() == STATUS_PLAYING)
	{
		updatePlayingScreen();
	}
	else
	{
		updateEndScreen();
	}
}

void Game::draw()
{
	// Draw backround image
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "sky.png";
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT + 50.0f, br);

	if (getStatusMode() == STATUS_USER_LOGIN_SCREEN)
	{
		drawLoginScreen();
	}
	else if (getStatusMode() == STATUS_MAIN_MENU)
	{
		drawMenuScreen();
	}
	else if (getStatusMode() == STATUS_PLAYING)
	{
		drawPlayingScreen();
	}
	else
	{
		drawEndScreen();
	}
}

void Game::init()
{
	// Initialize font
	graphics::setFont(std::string(ASSET_PATH) + "font.ttf");
	// Start playing music
	graphics::playMusic(std::string(ASSET_PATH) + "music.mp3", 0.1f, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::updateLoginScreen()
{
	// Wait for 1 second before start the menu screen
	if (graphics::getGlobalTime() > 1000.0f)
	{
		setStatusMode(STATUS_MAIN_MENU);
	}
	
}

void Game::updateMenuScreen()
{
	//when enter pressed move to next state -> Start game
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		setStatusMode(STATUS_PLAYING);
	}
}

void Game::updatePlayingScreen()
{
	// Create the packs
	if (!pack_initialized)
	{
		graphics::Brush brush;
		squid_pack = new EnemyPack(*this, brush, 100.0f, 100.0f, 40.0f, "squid.png");
		crab1_pack = new EnemyPack(*this, brush, 100.0f, 150.0f, 40.0f, "crab.png");
		crab2_pack = new EnemyPack(*this, brush, 100.0f, 200.0f, 40.0f, "crab.png");
		octopus1_pack = new EnemyPack(*this, brush, 100.0f, 250.0f, 40.0f, "octopus.png");
		octopus2_pack = new EnemyPack(*this, brush, 100.0f, 300.0f, 40.0f, "octopus.png");
		pack_initialized = true;
		pack_vector.push_back(octopus2_pack);
		pack_vector.push_back(octopus1_pack);
		pack_vector.push_back(crab2_pack);
		pack_vector.push_back(crab1_pack);
		pack_vector.push_back(squid_pack);
	}
	// Create player
	if (!player)
	{
		player = new Player(*this);
	}
	// Check which enemy can shoot
	if (!pack_vector.empty())
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 1; j < pack_vector.size(); j++)
			{
				if (pack_vector[j - 1]->pack[i] && pack_vector[j]->pack[i] && pack_vector[j - 1]->pack[i]->getActive())
				{
					pack_vector[j]->pack[i]->setCanShoot(false);
				}
			}
		}
	}

	// Check if all enemies died
	if (!pack_vector.empty())
	{
		for (int i = 1; i < pack_vector.size(); i++)
		{
			if (enemy_alive)
				break;
			for (int j = 0; j < 11; j++)
			{
				if (enemy_alive)
					break;
				if (pack_vector[i]->pack[j]->getActive())
				{
					enemy_alive = true;
				}
				else
				{
					enemy_alive = false;
				}
			}
		}
	}
	if (!enemy_alive)
		enemies_died = true;

	// Update packs
	for (auto& pack : pack_vector)
	{
		if (pack)
			pack->update();
	}
	
	if (!pack_vector.empty())
	{
		for (int i = 0; i < pack_vector.size()-1; i++)
		{
			for (int j = 0; j < 11; ++j)
			{
				// Keep packs together
				if (pack_vector[i]->pack[j] && pack_vector[i + 1]->pack[j])
				{
					pack_vector[i]->pack[j]->setPosy(pack_vector[i + 1]->pack[j]->getPosy() + 50.0f);
				}
				// If pack touch the down edge user lose
				if (pack_vector[i]->pack[j] && pack_vector[i]->pack[j]->getPosy() > (CANVAS_HEIGHT - pack_vector[i]->pack[j]->getSize()))
				{
					touched_down_edge = true;
				}
			}
		}
	}
	if (player)
	{
		// Update Player
		player->update();
		// Check lives, score, enemies and enemies' position to end game
		if (player->getLives() < 1 || touched_down_edge || touched_player)
		{
			win = false;
			setStatusMode(STATUS_END_GAME);
		}
		if (player->getScore() == 990 + (spaceship_kills * spaceship_value) || enemies_died)
		{
			win = true;
			setStatusMode(STATUS_END_GAME);
		}
	}
		

	for (auto& enemy_shot : enemy_shots)
	{
		if (enemy_shot)
		{
			// Update its enemy's shot
			enemy_shot->update();
			// Delete shot if it is not active
			if (!enemy_shot->getActive())
			{
				delete enemy_shot;
				enemy_shot = nullptr;
			}
		}
	}

	for (auto& player_shot : player_shots)
	{
		if (player_shot)
		{
			// Update its player's shot
			player_shot->update();
			// Delete shot if it is not active
			if (!player_shot->getActive())
			{
				delete player_shot;
				player_shot = nullptr;
			}
		}
	}
	// Fix time variables for enemy's and player's shots
	enemy_timer += graphics::getDeltaTime();
	player_timer += graphics::getDeltaTime();

	if (enemy_timer > 2000.0f && numshot == 2)
	{
		numshot = 0;
		enemy_timer = 0.0f;
	}
	if (player_timer > 300.0f && !canshoot)
	{
		player_timer = 0.0f;
		canshoot = true;
	}

	spaceship_timer += graphics::getDeltaTime();
	if (spaceship_timer > 40000.0f)
	{
		spaceship_timer = 0.0f;
		create_spaceship = true;
	}
	// Create Spaceship
	if (!spaceship && create_spaceship)
	{
		spaceship = new Spaceship(*this);
		create_spaceship = false;
	}

	// Update Spaceship
	if (spaceship)
	{
		spaceship->update();
		// Delete spaceship if it is not active
		if (!spaceship->getActive())
		{
			delete spaceship;
			spaceship = nullptr;
		}
	}
	// Check Collisions
	checkCollision();
}

void Game::updateEndScreen()
{
	// If pressed ESC close game
	if (graphics::getKeyState(graphics::SCANCODE_ESCAPE))
	{
		return;
	}	
}

void Game::drawLoginScreen()
{
	graphics::Brush br;
	char info[40];

	// Draw first screen text
	sprintf_s(info, "SPACE   INVADERS");
	graphics::drawText(50, 200, 60, info, br);

	sprintf_s(info, "Protect   your   land   from   aliens!");
	graphics::drawText(75, 450, 30, info, br);
}

void Game::drawMenuScreen()
{
	graphics::Brush brush;
	char info[40];

	//draw game title on screen
	sprintf_s(info, "SPACE   INVADERS");
	graphics::drawText(50, 100, 60, info, brush);
	
	//draw the value of each enemy
	brush.texture = std::string(ASSET_PATH) + "spaceship.png";
	brush.fill_opacity = 0.8f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(200, 160, 45, 40, brush);

	sprintf_s(info, "= 50 POINTS");
	graphics::drawText(230, 170, 30, info, brush);

	brush.texture = std::string(ASSET_PATH) + "squid.png";
	brush.fill_opacity = 0.8f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(200, 200, 35, 35, brush);

	sprintf_s(info, "= 30 POINTS");
	graphics::drawText(230, 210, 30, info, brush);

	brush.texture = std::string(ASSET_PATH) + "crab.png";
	brush.fill_opacity = 0.8f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(200, 240, 35, 35, brush);

	sprintf_s(info, "= 20 POINTS");
	graphics::drawText(230, 250, 30, info, brush);

	brush.texture = std::string(ASSET_PATH) + "octopus.png";
	brush.fill_opacity = 0.8f;
	brush.outline_opacity = 0.0f;
	graphics::drawRect(200, 280, 40, 40, brush);

	sprintf_s(info, "= 10 POINTS");
	graphics::drawText(230, 290, 30, info, brush);
	
	//draw user's button
	sprintf_s(info, "Use LEFT ARROW and RIGHT ARROW to Move");
	graphics::drawText(25, 340, 25, info, brush);

	sprintf_s(info, "Press SPACE to Fire");
	graphics::drawText(170, 390, 30, info, brush);

	//draw button to start
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(60, 500, 50, info, brush);

}

void Game::drawPlayingScreen()
{
	if (player)
	{
		// Show Player's Score and Lives
		graphics::Brush brush;
		char info[30];
		sprintf_s(info, "SCORE: %d", player->getScore());
		graphics::drawText(20, 30, 30, info, brush);

		sprintf_s(info, "LIVES: %d", player->getLives());
		graphics::drawText(330, 30, 30, info, brush);

		if (player->getLives() > 1 )
		{
			brush.texture = std::string(ASSET_PATH) + "player.png";
			brush.fill_opacity = 0.8f;
			brush.outline_opacity = 0.0f;
			graphics::drawRect(480, 20, 30, 20, brush);
		}
		if (player->getLives() > 2)
		{
			brush.texture = std::string(ASSET_PATH) + "player.png";
			brush.fill_opacity = 0.8f;
			brush.outline_opacity = 0.0f;
			graphics::drawRect(520, 20, 30, 20, brush);
		}

		// Draw Player
		player->draw();

		// Create Player's Shot
		if (player->getShooting() && canshoot)
		{
			canshoot = false;
			player_timer = 0.0f;
			player_shot = new Shot(*this, false, player->getPosX(), player->getPosY());
			player_shots.push_back(player_shot);
			graphics::playSound(std::string(ASSET_PATH) + "shot_sound.mp3", 0.1f);
		}
	}

	// Draw packs
	for (auto& pack : pack_vector)
	{
		if (pack)
			pack->draw();
	}
	// Create enemy's shot randomly | Two at a time - Max
	if (!pack_vector.empty())
	{
		int ran1 = rand0toGiven(4); // Random pack number
		int ran2 = rand0toGiven(10); // Random enemy number
		if (pack_vector[ran1]->pack[ran2] && pack_vector[ran1]->pack[ran2]->getCanShoot() && numshot < 2)
		{
			numshot = numshot + 1;
			enemy_timer = 0.0f;
			enemy_shot = new Shot(*this, true, pack_vector[ran1]->pack[ran2]->getPosx(), pack_vector[ran1]->pack[ran2]->getPosy());
			enemy_shots.push_back(enemy_shot);
			graphics::playSound(std::string(ASSET_PATH) + "shot_sound.mp3", 0.05f);
		}
	}

	// Draw Enemys's Shots
	for (auto& element : enemy_shots) {
		if (element)
			element->draw();
	}
	// Draw Player's Shots
	for (auto& element : player_shots) {
		if(element)
			element->draw();
	}

	// Draw Spaceship
	if (spaceship)
		spaceship->draw();
}

void Game::drawEndScreen()
{
	graphics::stopMusic();
	graphics::Brush br;
	char info[30];

	sprintf_s(info, "Your Score: %d", player->getScore());
	graphics::drawText(130, 200, 50, info, br);

	if (!win)
	{
		sprintf_s(info, "DEFEAT :(");
		graphics::drawText(200, 320, 50, info, br);
	}
	else
	{
		sprintf_s(info, "VICTORY!");
		graphics::drawText(180, 300, 50, info, br);
	}
	sprintf_s(info, "Press ESC to EXIT");
	graphics::drawText(130, 450, 40, info, br);
}