#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Vector2.h"

class mainMenu
{
public:
	mainMenu();
	~mainMenu();
	void init();
	void handleEvent();
	void update();
	void render();
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Vector2 SCREEN_SIZE;
	Vector2 MAP_SIZE;
};

