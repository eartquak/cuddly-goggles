#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <random>
#include "playerObject.h"
#include "map.h"
#include "enemyObject.h"
#include "Vector2.h"


using namespace std;

extern Vector2 SCREEN_SIZE;
extern Vector2 MAP_SIZE;

class game {
public:
	game();
	~game();

	void init(SDL_Renderer *render);
	void handleEvent();
	void update();
	void render();
	//void clean();
	void checkCollision();
	void createEnemy();
	struct enemy** ene = nullptr;
	struct enebullet** enebul = nullptr;
	struct bullet** bul = nullptr;
	bool running() 
	{
		return isRunning;
	}
	static SDL_Event event;
	int mu = 0;
	int mr = 0;
	int coll = 0;
private:
	bool isRunning = false;
	SDL_Renderer* renderer = nullptr;
	//Vector2 SCREEN_SIZE;
	//Vector2 MAP_SIZE;
	Uint64 prev_tick = 0;
	double fps_time = 0;
	double delta_time = 0;
	int cnt = 0;
	int wh = 0;
	int ww = 0;
	int c = 0;
	Vector2* transform = nullptr;
	SDL_Rect safePos;
	SDL_Rect* mCharPos = nullptr;
	double time1 = 0;
	SDL_Rect spawn_rect;
	SDL_Texture* bullTex = nullptr;
	int* nEnemy = nullptr;
	int* nBull = nullptr;
	int* bulln = nullptr;
	bool rdown = false;
	TTF_Font* agave = nullptr;
	int ntr = 0;
	int enemyTC = 0;
	int enemyP = 0;
	random_device rd;
};