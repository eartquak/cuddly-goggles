#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include <math.h>

class playerObject
{
public:
	playerObject();
	~playerObject();

	int defPos[2] = { 0, 0 };
	int* pos = defPos;
	float ang = 0;
	void init(int *dimDst, SDL_Renderer* render);
	void update(double delta_time);
	void render();
private:
	SDL_Texture* gObjTex = nullptr;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* bullTex = nullptr;
	double vel = 100;
	double ttux = 0;
	double ttuy = 0;
	int mx = 0;
	int my = 0;
	int x, y = 0;
	double bullvel = 100;
	double bullttux, bullttuy = 0;
	void makeBullet(double delta_time);
	SDL_Rect bullRect;
	float bullAng = 0;
};

