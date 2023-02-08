#include "include/game.h"

playerObject* mChar = nullptr;
Map* map = nullptr;
enemyObject* enemyObj = nullptr;

game::game()
{
}

game::~game()
{
}

SDL_Event game::event;

using namespace std;

void game::init(SDL_Renderer *render)
{
	renderer = render;

	isRunning = true;

	mChar = new playerObject();
	map = new Map();
	enemyObj = new enemyObject();
	mChar->init(renderer);
	mCharPos = &(mChar->destRect);
	(*mCharPos).y = (SCREEN_SIZE.y / 2 - mCharPos->h / 2);
	(*mCharPos).x = (SCREEN_SIZE.x / 2 - mCharPos->w / 2);
	safePos = *mCharPos;
	mChar->time = &time1;
	nBull = &(mChar->n);
	bul = &(mChar->bull);
	bulln = &(mChar->bulln);

	map->init(renderer);
	transform = &(map->mappos);


	mChar->transform = transform;

	enemyObj->init(renderer, transform, mCharPos);
	ene = &(enemyObj->en);
	nEnemy = &(enemyObj->nEnemy);
	enemyObj->plChar = mChar;
	enemyObj->time = &time1;
	enebul = &enemyObj->enbull;
	prev_tick = SDL_GetPerformanceCounter();
	
	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(renderer, &rendererInfo);

	SDL_Surface* tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	agave = TTF_OpenFont("agave.ttf", 24);
}

void game::handleEvent()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break; 
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					mu = 1;
					break;
				case SDLK_a:
					mr = 1;
					break;
				case SDLK_s:
					mu = -1;
					break;
				case SDLK_d:
					mr = -1;
					break;
				case SDLK_r:
					if (!rdown) {
						*bulln = 6;
						rdown = true;
					}
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					mu = 0;
					mu = 0;
					break;
				case SDLK_a:
					mr = 0;
					break;
				case SDLK_s:
					mu = 0;
					break;
				case SDLK_d:
					mr = 0;
					break;
				case SDLK_r:
					rdown = false;
			}
			break;
		default:
			break;
	}
	
}  

void game::update()
{
	Uint64 cur_tick = SDL_GetPerformanceCounter();
	delta_time = static_cast<double>((cur_tick - prev_tick) / static_cast<double>(SDL_GetPerformanceFrequency()));
	prev_tick = cur_tick;
	mChar->update(delta_time, 0, 0);
	map->update(delta_time, mu, mr, false, false);
	enemyObj->update(delta_time);
	cnt++;
	time1 += delta_time;
	checkCollision();
	if (((int)time) % 5 == 0) {
		mChar->bulletDestroy();
	}
	//printf("FPS: %lf", 1 / delta_time);
	//printf("\r");
	enemyTC = (int)(time1/2)+5;
	createEnemy();
	if (mChar->hp <= 0) {
		isRunning = false;
	}
}

void game::render()
{
	SDL_RenderClear(renderer);
	map->render();
	mChar->render();
	enemyObj->render();
	SDL_RenderPresent(renderer);
}
//collison needs to change - quad tree
void game::checkCollision()
{
	if (((SCREEN_SIZE.x / 2 + mChar->destRect.w/2) >= (transform->x + MAP_SIZE.x)) || (SCREEN_SIZE.x / 2 - mChar->destRect.w / 2 <= transform->x)) {
		transform->x = safePos.x;
		coll = 1;
	}
	else {
		safePos.x = (*transform).x;
	}
	if (((SCREEN_SIZE.y/2 + mChar->destRect.h/2) >= (transform->y + MAP_SIZE.y)) || ((SCREEN_SIZE.y/2 - mChar->destRect.h/2) <= transform->y)) {
		transform->y = safePos.y;
		coll = 1;
	}
	else {
		safePos.y = transform->y;
	}
	for (int j = 1; j < *nEnemy; j++) {
		if ((*ene + j)->isRendered) {
			SDL_Rect enecent;
			enecent.x = ((*ene + j)->rend).x + ((*ene + j)->rend).w / 2;
			enecent.y = ((*ene + j)->rend).y + ((*ene + j)->rend).h / 2;
			for (int i = 1; i < *nBull; i++) {
				if ((*bul + i)->isRendered) {
					double dist_2 = pow(((*bul + i)->bullRend.x - enecent.x), 2) + pow(((*bul + i)->bullRend.y - enecent.y), 2);
					if (dist_2 < 200) {
						if (((*ene + j)->nHit) < 3) {
							(*bul + i)->isRendered = false;
							((*ene + j)->nHit)++;
							(*ene + j)->isAngry = true;
							(*ene + j)->vel = 75;
						}
						else {
							(*bul + i)->isRendered = false;
							((*ene + j)->nHit)++;
							(*ene + j)->isAngry = true;
							(*ene + j)->isRendered = false;
							enemyP--;
						}
					}
				}
			}
			double dist_2 = pow((enecent.x - SCREEN_SIZE.x / 2), 2) + pow((enecent.y - SCREEN_SIZE.y / 2), 2);
			if (dist_2 < 400) {
				mChar->hp = mChar->hp - 100;
				(*ene + j)->vel = 0;
			}
			if ((*ene + j)->type == 1) {
				if (dist_2 < 100000) {
					(*ene + j)->r = false;
				}
				else {
					(*ene + j)->r = true;
				}
			}
			if ((*ene + j)->type == 2) {
				if (dist_2 > 100000) {
					(*ene + j)->r = false;
				}
				else {
					(*ene + j)->r = true;
				}
			}
		}
	}
	for (int i = 1; i < enemyObj->nb; i++) {
		if ((*enebul + i)->isRendered) {
			double dist_2 = pow(((*enebul + i)->bullpos.x) - (SCREEN_SIZE.x / 2) + transform->x, 2) + pow(((*enebul + i)->bullpos.y) - (SCREEN_SIZE.y / 2) + transform->y, 2);
			if (dist_2 < 200) {
				mChar->hp = mChar->hp - 25;
				(*enebul + i)->isRendered = false;
			}
		}

	}
}

void game::createEnemy()
{
	mt19937 gen(rd());
	while (enemyTC > enemyP) {
		int x = (gen() % (MAP_SIZE.x - 64)) + 32;
		int y = (gen() % (MAP_SIZE.x - 64)) + 32;
		float dist = pow((x - mCharPos->y + transform->x), 2) + pow((y - mCharPos->y + transform->y), 2);
		while (dist < 30000) {
			printf("%d, %d", x, y);
			x = (gen() % (MAP_SIZE.x - 64)) + 32;
			y = (gen() % (MAP_SIZE.x - 64)) + 32;
			dist = pow((x - mCharPos->y + transform->x), 2) + pow((y - mCharPos->y + transform->y), 2);
		}
		//enemyObj->enemyCreate(x, y);
		enemyP ++;
	}
}