#include "makeMap.h"

makeMap::makeMap()
{
}

makeMap::~makeMap()
{
	SDL_DestroyTexture(mapT);
	SDL_DestroyTexture(mapTex);
}

void makeMap::init(SDL_Renderer *render)
{
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/tile.png");
	mapTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 1024);
	mapT = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_SetRenderTarget(renderer, mapTex);
	rect.w = 32;
	rect.h = 32;
	rect.x = 0;
	rect.y = 0;
	for (int i = 0; i <= 32; i++) {
		for (int j = 0; j < 32; j++) {
			rect.x = j * 32;
			SDL_RenderCopy(renderer, mapT, NULL, &rect);
		}
		rect.y = i * 32;
	}
	SDL_SetRenderTarget(renderer, NULL);
}

void makeMap::update()
{
}

void makeMap::render()
{
	rect.h = 600;
	rect.w = 600;
	SDL_RenderCopy(renderer, mapTex, NULL, NULL);
}
