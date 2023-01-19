#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"

class Map
{
public:
	Map();
	~Map();

	void init(SDL_Renderer* render);
	void update(double delta_time, int mu, int mr);
	void render();
	SDL_Rect mapRect;
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* mapTex = nullptr;
	SDL_Texture* mapT = nullptr;
	SDL_Rect rect;
	int w, h = 0;
	double vel = 100;
	double ttux = 0;
	double ttuy = 0;
};

