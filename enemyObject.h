#pragma once
#include <SDL.h>
#include <SDL_image.h>

class enemyObject
{
public:
	enemyObject();
	~enemyObject();


	void init(SDL_Renderer* render);
	void update();
	void render();
private:
};

