#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "game.h"
#include "playerObject.h"
#include "Vector2.h"

using namespace std;

class Map
{
public:
	Map();
	~Map();

	void init(SDL_Renderer* render);
	void update(double delta_time, int mu, int mr, bool tx, bool ty);
	void render();
	//Vector2 SCREEN_SIZE;
	//Vector2 MAP_SIZE;
	int PLAYER_SIZE;
	double angR;
	Vector2 mappos;
private:
	void makeMapTex();
	void makeMap(int n);

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* mapTex = nullptr;
	SDL_Texture* mapT = nullptr;

	Mix_Music* movsound = nullptr;
	int mf = 0;

	int w = 0;
	int h = 0;
	Vector2* pos;
	SDL_Rect rect;

	double defvel = 250;
	double vel = 250;
	double ttux = 0;
	double ttuy = 0;

	random_device rd;

	struct maps {
		SDL_Rect rect;
		SDL_Texture* mapTex = nullptr;
		struct maps* next;
	};
	struct maps map;
};

