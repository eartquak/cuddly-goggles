#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class playerObject
{
public:
	playerObject();
	~playerObject();

	float ang = 0;
	void init(SDL_Renderer* render);
	void update(double delta_time, int mu, int mr);
	void render();
	int my, mx = 0;
	SDL_Rect srcRect, destRect;
	SDL_Rect* transform;
	void bulletDestroy();
	double* time = nullptr;
	int n = 1;
	struct bullet {
		float bullAng, bullAngR = 0;
		SDL_Rect bullRect;
		SDL_Rect bullTran;
		double bullttux, bullttuy = 0;
		double time = 0;
	};
private:
	SDL_Texture* gObjTex = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* bullTex = nullptr;
	SDL_Rect bullRend;
	double vel = 100;
	double ttux = 0;
	double ttuy = 0;
	int x, y = 0;
	double bullvel = 600;
	void makeBullet(double delta_time);
	//SDL_Rect bullRect;
	//float bullAng, bullAngR = 0;
	struct bullet *bull = nullptr;
	int nEnemy = 0;
};

