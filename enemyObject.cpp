#include "include/enemyObject.h"

using namespace std;

enemyObject::enemyObject()
{
}

enemyObject::~enemyObject()
{
}

void enemyObject::init(SDL_Renderer* render, Vector2* r, SDL_Rect* pR)
{
	PLAYER_SIZE = SCREEN_SIZE.y / 16;
	transform = r;
	mCharPos = pR;
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/zombie.png");
	enemyTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	//rect.h = rect.w = 64;
	//rect.x = rect.y = 0;
	//uRect.h = uRect.w = 64;
	en = (struct enemy*)malloc(sizeof(struct enemy));
	
	//enemyCreate(0, 0);
}

void enemyObject::update(double delta_time)
{
	for (int i = 1; i < nEnemy; i++) {
		if ((en + i)->r) {
			enemy_random(en + i, delta_time);
		}
		else {
			enemy_normal(en + i, delta_time);
		}
	}
}

void enemyObject::render()
{
	for (int i = 1; i < nEnemy; i++) {
		if ((en + i)->isRendered) {
			SDL_RenderCopyEx(renderer, enemyTex, NULL, &((en + i)->rend), (en + i)->ang, NULL, SDL_FLIP_NONE);
		}
	}
}

void enemyObject::enemyCreate(int x, int y)
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
	nEnemy++;
	en = (struct enemy*)realloc(en, nEnemy * sizeof(struct enemy));
	(en + nEnemy - 1)->pos.x = x;
	(en + nEnemy - 1)->pos.y = y;
	(en + nEnemy - 1)->rend.w = PLAYER_SIZE;
	(en + nEnemy - 1)->rend.h = PLAYER_SIZE;
	(en + nEnemy - 1)->angR = atan2((double)(((en + nEnemy)->rend.y + (en + nEnemy)->rend.h / 2) - SCREEN_SIZE.y / 2), (double)(((en + nEnemy)->rend.x + (en + nEnemy)->rend.w / 2) - SCREEN_SIZE.y / 2));
	(en + nEnemy - 1)->ang = ((double)180 * (en + nEnemy)->angR / M_PI);
	(en + nEnemy - 1)->isRendered = true;
	(en + nEnemy - 1)->nHit = 0;
	(en + nEnemy - 1)->isAngry = false;
	(en + nEnemy - 1)->vel = 50;
	(en + nEnemy - 1)->health = 100;
	(en + nEnemy - 1)->enettux = 0;
	(en + nEnemy - 1)->enettuy = 0;
	(en + nEnemy - 1)->ptr = 0;
	(en + nEnemy - 1)->r = true;
	(en + nEnemy - 1)->tr = 0;
}

void enemyObject::enemyAttack(struct enemy *enmy)
{
	/*if (enmy->ttk == 0) {
		mChar
	}*/
}
void enemyObject::enemy_random(enemy* enmy, double delta_time)
{
	mt19937 gen(rd1());
	printf("%lf\n", *time);
	if (*time > enmy->ptr + enmy->tr) {
		enmy->ang = rd1() % 360;
		enmy->angR = M_PI * (enmy->ang) / 180;
		enmy->tr = ((gen() % 10) * 0.05) + 1;
		enmy->ptr = *time;
		enmy->pos.MakeVel(enmy->vel, enmy->angR, &enmy->enettux, &enmy->enettuy, delta_time);
	}
	else {
		enmy->pos.MakeVel(enmy->vel, enmy->angR, &enmy->enettux, &enmy->enettuy, delta_time);
	}
	enmy->rend.y = enmy->pos.y + transform->y;
	enmy->rend.x = enmy->pos.x + transform->x;
}

void enemyObject::enemy_normal(enemy* enmy, double delta_time)
{
	enmy->angR = atan2((double)((enmy->rend.y + enmy->rend.h / 2) - SCREEN_SIZE.y / 2), (double)((enmy->rend.x + enmy->rend.w / 2) - SCREEN_SIZE.x / 2));
	enmy->ang = ((double)180 * enmy->angR / M_PI);
	enmy->pos.MakeVel(enmy->vel, enmy->angR, &enmy->enettux, &enmy->enettuy, delta_time);
}

