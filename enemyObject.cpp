#include "enemyObject.h"

enemyObject::enemyObject()
{
}

enemyObject::~enemyObject()
{
}

void enemyObject::init(SDL_Renderer* render, SDL_Rect* r, SDL_Rect* pR)
{
	transform = r;
	mCharPos = pR;
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/zombie.png");
	enemyTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	rect.h = rect.w = 64;
	rect.x = rect.y = 0;
	uRect.h = uRect.w = 64;
}

void enemyObject::update(double delta_time)
{
	angR = atan2((double)((uRect.y + uRect.h / 2) - SCREEN_SIZE / 2), (double)((uRect.x + uRect.w / 2) - SCREEN_SIZE / 2));
	ang = ((double)180 * atan2((double)((uRect.y + uRect.h / 2) - SCREEN_SIZE / 2), (double)((uRect.x + uRect.w / 2) - SCREEN_SIZE / 2)) / M_PI);
	//printf("(%f) ", ang);
	ttuy += vel * delta_time * sin(angR);
	ttux += vel * delta_time * cos(angR);
	//printf("(%lf, %lf) (%lf, %lf)\n", cos(ang), sin(ang), ttux, ttuy);
	if (ttuy >= 1) {
		rect.y -= 1;
		ttuy = 0;
	}
	else if (ttuy <= -1) {
		rect.y += 1;
		ttuy = 0;
	}
	else if (ttux >= 1) {
		rect.x -= 1;
		ttux = 0;
	}
	else if (ttux <= -1) {
		rect.x += 1;
		ttux = 0;
	}
	uRect.y = rect.y + (*transform).y + 512;
	uRect.x = rect.x + (*transform).x + 512;
}

void enemyObject::render()
{
	SDL_RenderCopyEx(renderer, enemyTex, NULL, &uRect, ang, NULL, SDL_FLIP_NONE);
}

void game::enemyCreate()
{
	/*spawn_rect.x = spawn_rect.y = 128;
	if (((*transform).x + SCREEN_SIZE * 2) <= 384) {
		spawn_rect.w = (*transform).x + SCREEN_SIZE * 2 - 128;
	}

	else {
		spawn_rect.w = 256;
	}
	if ((*transform).x >= 128) {
		spawn_rect.x = (*transform).x;
		spawn_rect.w = 384 - (*transform).x;
	}
	else {
		spawn_rect.x = 128;
		spawn_rect.w = 256;
	}
	if (384 >= ((*transform).y + SCREEN_SIZE * 2)) {
		spawn_rect.h = (*transform).y + SCREEN_SIZE * 2 - 128;
	}
	else {
		spawn_rect.h = 256;
	}
	if ((*transform).y >= 128) {
		spawn_rect.y = (*transform).y;
		spawn_rect.h = 384 - (*transform).y;
	}
	else {
		spawn_rect.y = 128;
		spawn_rect.h = 256;
	}
	//printf("%d, %d\n", spawn_rect.w, spawn_rect.h);
	SDL_RenderCopy(renderer, bullTex, NULL, &spawn_rect);*/

}