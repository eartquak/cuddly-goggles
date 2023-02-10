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
	tmpSurface = IMG_Load("Assets/player.png");
	enemyTex1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	en = (struct enemy*)malloc(sizeof(struct enemy));
	enbull = (struct enebullet*)malloc(sizeof(struct enebullet));
}

void enemyObject::update(double delta_time)
{
	for (int i = 1; i < nEnemy; i++) {
		if ((en + i)->isRendered) {
			if (((en + i)->type == 1)) {
				type1_movement(delta_time, en + i);
			}
			if (((en + i)->type == 2)) {
				type2_movement(delta_time, en + i);
			}
			(en + i)->ttk = (en + i)->ttk - delta_time;
		}
	}
	moveBullet(delta_time);
	if (((int)(*time) % 5) == 0) {
		enbulletDestroy();
	}
}

void enemyObject::render()
{
	for (int i = 1; i < nb; i++) {
		if ((enbull + i)->isRendered) {
			SDL_RenderCopyEx(renderer, bullTex, NULL, &((enbull + i)->bullRend), (enbull + i)->bullAng, NULL, SDL_FLIP_NONE);
		}
	}
	for (int i = 1; i < nEnemy; i++) {
		if ((en + i)->isRendered) {
			if ((en + i)->type == 1) {
				SDL_RenderCopyEx(renderer, enemyTex, NULL, &((en + i)->rend), (en + i)->ang, NULL, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(renderer, enemyTex1, NULL, &((en + i)->rend), (en + i)->ang, NULL, SDL_FLIP_NONE);
			}
		}
	}
}

void enemyObject::enemyCreate(int x, int y, int t)
{
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
	(en + nEnemy - 1)->r = false;
	(en + nEnemy - 1)->tr = 0;
	(en + nEnemy - 1)->type = t;
	(en + nEnemy - 1)->safepos.x = x;
	(en + nEnemy - 1)->safepos.y = y;
}

void enemyObject::enemyAttack(struct enemy *enmy)
{
	if (enmy->ttk <= 0) {
		if (*time > enmy->ptr + 0.2) {
			if (enmy->tr) {
				makeBullet(enmy);
				enmy->ptr = *time;
				enmy->tr--;
			}
			else {
				enmy->ttk = 1;
			}
		}
	}
	else {
		enmy->tr = 6;
	}
}
void enemyObject::enemy_random(struct enemy* enmy, double delta_time)
{
	mt19937 gen(rd1());
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

void enemyObject::enemy_normal(struct enemy* enmy, double delta_time)
{
	enmy->angR = atan2((double)((enmy->rend.y + enmy->rend.h / 2) - SCREEN_SIZE.y / 2), (double)((enmy->rend.x + enmy->rend.w / 2) - SCREEN_SIZE.x / 2));
	enmy->ang = ((double)180 * enmy->angR / M_PI);
	enmy->pos.MakeVel(enmy->vel, enmy->angR, &enmy->enettux, &enmy->enettuy, delta_time);
	enmy->rend.y = enmy->pos.y + transform->y;
	enmy->rend.x = enmy->pos.x + transform->x;
}

void enemyObject::makeBullet(struct enemy *enmy) {
		nb++;
		if (enbull) {
			struct enebullet* tmp = (struct enebullet*)realloc(enbull, nb * sizeof(struct enebullet));
			if (tmp) {
				enbull = tmp;
			}
		}
		if (enbull) {
			(enbull + nb - 1)->bullAng = enmy->ang;
			(enbull + nb - 1)->bullAngR = (M_PI * ((enbull + nb - 1)->bullAng)) / (double)180;
			(enbull + nb - 1)->bullpos.x = (int)((enmy->rend.x - (cos((enbull + nb - 1)->bullAngR) * (enmy->rend.w / 2)) + (enmy->rend.w / 2)) - transform->x);
			(enbull + nb - 1)->bullpos.y = (int)((enmy->rend.y - (sin((enbull + nb - 1)->bullAngR) * (enmy->rend.h / 2)) + (enmy->rend.h / 2)) - transform->y);
			(enbull + nb - 1)->bullRend.h = 4;
			(enbull + nb - 1)->bullRend.w = 8;
			(enbull + nb - 1)->time = *time;
			(enbull + nb - 1)->isRendered = true;
			(enbull + nb - 1)->bullttux = 0;
			(enbull + nb - 1)->bullttuy = 0;
		}
}
//function to move bullet
void enemyObject::moveBullet(double delta_time) {
	for (int i = 1; i < nb; i++) {
		(enbull + i)->bullpos.MakeVel(bullvel, (enbull + i)->bullAngR, &(enbull + i)->bullttux, &(enbull + i)->bullttuy, delta_time);
		(enbull + i)->bullRend.x = (enbull + i)->bullpos.x + transform->x;
		(enbull + i)->bullRend.y = (enbull + i)->bullpos.y + transform->y;
	}
}

void enemyObject::type1_movement(double delta_time, struct enemy *enmy)
{
	if (enmy->r) {
		enemy_random(enmy, delta_time);
	}
	else {
		enemy_normal(enmy, delta_time);
	}
}

void enemyObject::type2_movement(double delta_time, enemy* enmy)
{
	if (enmy->r) {
		enmy->vel = 0;
		enemy_normal(enmy, delta_time);
		enemyAttack(enmy);
	}
	else {
		enmy->vel = 50;
		enemy_normal(enmy, delta_time);
	}
}

void enemyObject::enbulletDestroy() {
	struct enebullet bu[100];
	int k = 0;
	for (int i = 1; i < nb; i++) {
		printf("    %lf\n", (*time - ((enbull + i)->time + 5)));
		if (*time <= ((enbull + i)->time + 5)) {
			bu[i - 1] = *(enbull + i);
			k += 1;
		}
	}
	nb = k + 1;
	if (enbull) {
		struct enebullet*tmp = (struct enebullet*)realloc(enbull, nb * sizeof(struct enebullet));
		if (tmp) {
			enbull = tmp;
		}
	}
	if (enbull) {
		for (int i = 1; i < nb; i++) {
			*(enbull + i) = bu[i - 1];
		}
	}
	printf("%d\n", nb);
}

