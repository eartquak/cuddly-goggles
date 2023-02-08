#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vector2.h"

class playerObject
{
public:
	playerObject();
	~playerObject();

	double ang = 0;
	void init(SDL_Renderer* render);
	void update(double delta_time, int mu, int mr);
	void render();
	int my = 0;
	int mx = 0;
	SDL_Rect srcRect, destRect;
	Vector2* transform = nullptr;
	void bulletDestroy();
	double* time = nullptr;
	int n = 1;
	struct bullet* bull = nullptr;
	int bulln = 6;
	bool isRendered = true;
	int hp = 100;
	//Vector2 SCREEN_SIZE;
	//Vector2 MAP_SIZE;
	int PLAYER_SIZE;
private:
	SDL_Texture* gObjTex = nullptr;
	SDL_Texture* Hred = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect Hrect;

	SDL_Texture* bullTex = nullptr;
	Mix_Chunk* bullsound = nullptr;
	double defvel = 300;
	double vel = 300;
	double ttux = 0;
	double ttuy = 0;
	int x = 0;
	int y = 0;
	double bullvel = 700;
	void moveBullet(double delta_time);
	void makeBullet();
};

struct player {

};

struct bullet {
	double bullAng = 0;
	double bullAngR = 0;
	Vector2 bullpos;
	SDL_Rect bullRend;
	double bullttux = 0;
	double bullttuy = 0;
	double time = 0;
	bool isRendered = true;
};

