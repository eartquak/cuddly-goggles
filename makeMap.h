#pragma once
#include <SDL.h>
#include <SDL_image.h>

class makeMap
{
public:
	makeMap();
	~makeMap();



	void init(SDL_Renderer *render);
	void update();
	void render();
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* mapTex = nullptr;
	SDL_Texture* mapT = nullptr;
	SDL_Rect rect;
	int w, h = 0;
};

