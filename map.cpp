#include "map.h"

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
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/tile.png");
	mapTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 1024);
	mapT = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_SetRenderTarget(renderer, mapTex);
	rect.w = 64;
	rect.h = 64;
	rect.x = 0;
	rect.y = 0;
	for (int i = 0; i <= 16; i++) {
		for (int j = 0; j < 16; j++) {
			rect.x = j * 64;
			SDL_RenderCopy(renderer, mapT, NULL, &rect);
		}
		rect.y = i * 64;
	}
	SDL_SetRenderTarget(renderer, NULL);
	rect.x = -SCREEN_SIZE;
	rect.y = -SCREEN_SIZE;
}

void Map::update(double delta_time, int mu, int mr)
{
	ttuy += vel * delta_time * mu;
	if (ttuy >= 1) {
		rect.y += 1;
		//transform.y = 1;
		ttuy = 0;
	}
	else if (ttuy <= -1) {
		rect.y -= 1;
		//transform.y = -1;
		ttuy = 0;
	}

	ttux += vel * delta_time * mr;
	if (ttux >= 1) {
		rect.x += 1;
		//transform.x = 1;
		ttux = 0;
	}
	else if (ttux <= -1) {
		rect.x -= 1;
		//transform.x = -1;
		ttux = 0;
	}
}

void Map::render()
{
	rect.h = SCREEN_SIZE*2;
	rect.w = SCREEN_SIZE*2;
	SDL_RenderCopy(renderer, mapTex, NULL, &rect);
}
