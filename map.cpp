#include "include/map.h"

using namespace std;

Map::Map()
{
}

Map::~Map()
{
	SDL_DestroyTexture(mapT);
	SDL_DestroyTexture(mapTex);
}

void Map::init(SDL_Renderer* render)
{
	//initialize tile and map
	PLAYER_SIZE = SCREEN_SIZE.y / 16;
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/tile.png");
	mapTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, MAP_SIZE.x, MAP_SIZE.y);
	mapT = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_SetRenderTarget(renderer, mapTex);
	makeMapTex();
	map.rect.x = 0;
	map.rect.y = 0;
	map.rect.w = MAP_SIZE.x;
	map.rect.h = MAP_SIZE.y;
	map.mapTex = mapTex;
	map.next = (struct maps*)malloc(sizeof(struct maps));
	makeMap(3);

	movsound = Mix_LoadMUS("Assets/Footstep_sound.wav");
	Mix_PlayMusic(movsound, -1);
}

void Map::update(double delta_time, int mu, int mr, bool tx, bool ty)
{
	angR = atan2(-mu, -mr);
	int m = 1;
	int mf = 1;
	if (!(mu || mr)) {
		m = 0;
		Mix_PauseMusic();
		mf = 0;
	}
	if (mf)
	{
		Mix_ResumeMusic();
	}
	mappos.MakeVel(vel, angR, &ttux, &ttuy, delta_time, m);
}

void Map::render()
{
	//render map first
	struct maps tmpm = map;
	for (int i = 0; i < 3; i++) {
		rect.x = mappos.x + tmpm.rect.x;
		rect.y = mappos.y + tmpm.rect.y;
		rect.w = tmpm.rect.w;
		rect.h = tmpm.rect.h;
		tmpm = *(tmpm.next);
		SDL_RenderCopy(renderer, mapTex, NULL, &rect);
	}
}

void Map::makeMapTex()
{
	//initialze the tile for map
	rect.w = rect.h = PLAYER_SIZE;
	int nX = (MAP_SIZE.x) / PLAYER_SIZE;
	int nY = (MAP_SIZE.y) / PLAYER_SIZE;

	//create square map using tile
	for (int i = 0; i <= nY; i++) {
		rect.y = i * PLAYER_SIZE;
		for (int j = 0; j <= nX; j++) {
			rect.x = j * PLAYER_SIZE;
			SDL_RenderCopy(renderer, mapT, NULL, &rect);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	mappos.x = -MAP_SIZE.x / 2 + SCREEN_SIZE.x / 2;
	mappos.y = -MAP_SIZE.y / 2 + SCREEN_SIZE.y / 2;
}

void Map::makeMap(int n)
{
	struct maps* tempm = map.next;
	struct maps prevm = map;
	mt19937 gen(rd());
	int i = 1;
	while (i < n) {
		tempm->mapTex = mapTex;
		int side = gen() % 4;
		switch (side) {
		case 0:
			tempm->rect.x = prevm.rect.x + MAP_SIZE.x + 3 * PLAYER_SIZE;
			tempm->rect.y = prevm.rect.y + 0;
			break;
		case 1:
			tempm->rect.x = prevm.rect.x + 0;
			tempm->rect.y = prevm.rect.y - MAP_SIZE.y - 3 * PLAYER_SIZE;
			break;
		case 2:
			tempm->rect.x = prevm.rect.x - MAP_SIZE.x - 3 * PLAYER_SIZE;
			tempm->rect.y = prevm.rect.y + 0;
			break;
		case 3:
			tempm->rect.x = prevm.rect.x + 0;
			tempm->rect.y = prevm.rect.y + MAP_SIZE.y + 3 * PLAYER_SIZE;
			break;
		}
		tempm->rect.w = MAP_SIZE.x;
		tempm->rect.h = MAP_SIZE.y;
		tempm->next = (struct maps*)malloc(sizeof(struct maps));
		printf("%d, %d", tempm->rect.x, tempm->rect.y);
		prevm = *tempm;
		tempm = tempm->next;
		i++;
	}
}
