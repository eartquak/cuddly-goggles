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
	//rect.h = rect.w = 64;
	//rect.x = rect.y = 0;
	//uRect.h = uRect.w = 64;
	en = (struct enemy*)malloc(sizeof(struct enemy));
	enemyCreate(512, 512);
}

void enemyObject::update(double delta_time)
{
	for (int i = 1; i < nEnemy; i++) {
		if ((en + i)->isAngry) {
			(en + i)->vel = 75;
		}
		else {
			(en + i)->vel = 50;
		}
		(en + i)->angR = atan2((double)(((en+i)->rend.y + (en + i)->rend.h / 2) - SCREEN_SIZE / 2), (double)(((en+i)->rend.x + (en+i)->rend.w / 2) - SCREEN_SIZE / 2));
		(en+i)->ang = ((double)180 * (en+i)->angR / M_PI);
		//printf("(%f) ", ang);
		(en+i)->enettuy += (en+i)->vel * delta_time * sin((en+i)->angR);
		(en+i)->enettux += (en+i)->vel * delta_time * cos((en+i)->angR);
		//printf("(%lf, %lf) (%lf, %lf)\n", cos(ang), sin(ang), ttux, ttuy);
		if ((en+i)->enettuy >= 1) {
			(en+i)->rect.y -= 1;
			(en+i)->enettuy = 0;
		}
		else if ((en+i)->enettuy <= -1) {
			(en+i)->rect.y += 1;
			(en+i)->enettuy = 0;
		}
		else if ((en+i)->enettux >= 1) {
			(en+i)->rect.x -= 1;
			(en+i)->enettux = 0;
		}
		else if ((en+i)->enettux <= -1) {
			(en+i)->rect.x += 1;
			(en+i)->enettux = 0;
		}
		(en+i)->rend.y = (en+i)->rect.y + (*transform).y + 512;
		(en+i)->rend.x = (en+i)->rect.x + (*transform).x + 512;
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
	(en + nEnemy - 1)->rect.x = 0;
	(en + nEnemy - 1)->rect.y = 0;
	(en + nEnemy - 1)->rend.w = 64;
	(en + nEnemy - 1)->rend.h = 64;
	(en + nEnemy - 1)->angR = atan2((double)(((en + nEnemy)->rend.y + (en + nEnemy)->rend.h / 2) - SCREEN_SIZE / 2), (double)(((en + nEnemy)->rend.x + (en + nEnemy)->rend.w / 2) - SCREEN_SIZE / 2));
	(en + nEnemy - 1)->ang = ((double)180 * (en + nEnemy)->angR / M_PI);
	(en + nEnemy - 1)->isRendered = true;
	(en + nEnemy - 1)->nHit = 0;
	(en + nEnemy - 1)->isAngry = false;
	(en + nEnemy - 1)->vel = 50;
}