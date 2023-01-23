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
	void enemyCreate(int x, int y);
	int nEnemy = 1;
	//SDL_Rect uRect
	struct enemy* en = nullptr;
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* enemyTex = nullptr;
	//double ang = 0;
	//double angR = 0;
	//float tAng = 0;
	SDL_Rect* transform = nullptr;
	SDL_Rect* mCharPos = nullptr;
	//double ttuy, ttux = 0;
	//double vel = 50;
	//SDL_Rect rect;
	//SDL_Rect spawn_rect;
};

struct enemy {
	SDL_Rect rect, rend;
	float ang, angR = 0;
	double enettuy, enettux = 0;
	double time = 0;
	bool isRendered = true;
	int nHit = 0;
	bool isAngry = false;
	double vel = 50;
};