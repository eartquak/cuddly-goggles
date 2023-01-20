#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "playerObject.h"
#include "map.h"
#include "enemyObject.h"
#define SCREEN_SIZE 512

class game {
public:
	game();
	~game();

	void init();
	void handleEvent();
	void update();
	void render();
	void clean();
	void checkCollision();

	bool running() 
	{
		return isRunning;
	}
	static SDL_Event event;
	int mu, mr = 0;
	SDL_Rect mCharPos;
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Uint64 prev_tick = 0;
	double fps_time = 0;
	double delta_time;
	int cnt = 0;
	int wh, ww = 0;
	int c = 0;
	SDL_Rect transform;
};