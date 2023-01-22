#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"

class enemyObject
{
public:
	enemyObject();
	~enemyObject();


	void init(SDL_Renderer* render, SDL_Rect* r, SDL_Rect* pR);
	void update(double delta_time);
	void render();
	void enemyCreate();
	SDL_Rect uRect;
	struct enemy {
		SDL_Rect rect;
		float ang, angR = 0;

	};
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* enemyTex = nullptr;
	double ang = 0;
	double angR = 0;
	//float tAng = 0;
	SDL_Rect* transform = nullptr;
	SDL_Rect* mCharPos = nullptr;
	double ttuy, ttux = 0;
	double vel = 50;
	SDL_Rect rect;
	SDL_Rect spawn_rect;
};