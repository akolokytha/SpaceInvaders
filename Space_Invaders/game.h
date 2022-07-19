#pragma once
#include "player.h"
#include "enemy.h"
#include "enemypack.h"
#include "shot.h"
#include "spaceship.h"

class Game
{
	/*
		STATUS_USER_LOGIN_SCREEN -> Game title | First stage
		STATUS_MAIN_MENU -> User can see enemy's values and start playing
		STATUS_PLAYING -> Playing stage
		STATUS_END_GAME -> When game finished
	*/
	typedef enum {STATUS_USER_LOGIN_SCREEN, STATUS_MAIN_MENU, STATUS_PLAYING, STATUS_END_GAME} status_t;

	status_t status = STATUS_USER_LOGIN_SCREEN;
	bool pack_initialized = false;	// Pack created only once

	// Enemy objects
	EnemyPack* squid_pack = nullptr;
	EnemyPack* crab1_pack = nullptr;
	EnemyPack* crab2_pack = nullptr;
	EnemyPack* octopus1_pack = nullptr;
	EnemyPack* octopus2_pack = nullptr;
	std::vector<EnemyPack*> pack_vector;	// Vector to keep all packs
	Player* player = nullptr;	// Player object
	Spaceship* spaceship = nullptr; // Spaceship object

	bool create_spaceship = false; // Variable to allow spaceship to be created
	float spaceship_timer = 0.0f;	// Variable to help not create spaceship all the time
	int spaceship_kills = 0; // Variable to chech for next state
	int spaceship_value = 50; // Value of each spaceship

	// Shot objects
	Shot* player_shot = nullptr;
	Shot* enemy_shot = nullptr;

	// Vectors to keep shot objects
	std::vector<Shot*> enemy_shots;
	std::vector<Shot*> player_shots;

	// Timers to check when shots needs to be created
	float enemy_timer = 0.0f;
	float player_timer = 0.0f;

	bool canshoot = false;	// Variable for player's shots
	bool win; // True -> User Won | False -> User Lost
	int numshot = 0;	// Check how many shots enemies create at the same time
	bool touched_down_edge = false; // If enemies touch the end of CANVAS_HEIGHT
	bool touched_player = false; // If enemies touch the player
	bool enemies_died = false; // If all enemies die, player win
	bool enemy_alive; // Variable to check enemies 

	bool debug_mode = false;	//Debug mode state | Default=False

	//update methods for each state
	void updateLoginScreen();
	void updateMenuScreen();
	void updatePlayingScreen();
	void updateEndScreen();
	//draw methods for each state
	void drawLoginScreen();
	void drawMenuScreen();
	void drawPlayingScreen();
	void drawEndScreen();
	//Change Status Mode
	void setStatusMode(status_t s) { status = s; }
	//Get Status Mode
	status_t getStatusMode() const { return status; }
	// Check all collisions
	void checkCollision();
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	Game();
	~Game();
};