#include "include/playerObject.h"

playerObject::playerObject()
{
}

playerObject::~playerObject()
{
	SDL_DestroyTexture(gObjTex);
	free(bull);
}

void playerObject::init(SDL_Renderer* render)
{
	//initializing main char
	PLAYER_SIZE = SCREEN_SIZE.y / 16;
	destRect.w = destRect.h = PLAYER_SIZE;
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/player.png");
	gObjTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	isRendered = true;
	tmpSurface = IMG_Load("Assets/red.png");
	Hred = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	Hrect.w = Hwdef = SCREEN_SIZE.x / 5;
	Hrect.h = SCREEN_SIZE.y / 25;
	Hrect.x = SCREEN_SIZE.x / 25;
	Hrect.y = SCREEN_SIZE.y / 25;
	
	//initializing bullet
	bulln = 6;
	tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	bull = (struct bullet*)malloc(sizeof(struct bullet));
	bullsound = Mix_LoadWAV("Assets/Bullet_sound.wav");
	printf("%p", bullsound);
}

void playerObject::update(double delta_time, int mu, int mr)
{
	//for shooting and making the player look around
	SDL_GetMouseState(&x, &y);
	//ang = ((double)180 * atan2((double)((destRect.y + destRect.h / 2) - y), (double)((destRect.x + destRect.w / 2) - x)) / M_PI);
	if (game::event.type == SDL_MOUSEBUTTONDOWN) {
		switch (game::event.button.button) {
		//case to create a bullet
		case SDL_BUTTON_LEFT:
			makeBullet();
		}
	}
	//set angle for character
	ang = ((double)180 * atan2((double)((destRect.y + destRect.h/2)-y), (double)((destRect.x + destRect.w / 2) - x)) / M_PI);
	//make the bullet move in relation to main surface
	moveBullet(delta_time);
	if (hp <= 0) {
		isRendered = false;
	}
	Hrect.w = (Hwdef * hp) / 100;
	printf("%d", hp);
	printf(" %d\n", Hrect.w);
}

void playerObject::render()
{
	//render the bullet
	for (int i = 1; i < n; i++) {
		if ((bull + i)->isRendered) {
			SDL_RenderCopyEx(renderer, bullTex, NULL, &((bull + i)->bullRend), (bull + i)->bullAng, NULL, SDL_FLIP_NONE);
		}
	}
	//render the main Character
	if (isRendered) {
		SDL_RenderCopyEx(renderer, gObjTex, NULL, &destRect, ang, NULL, SDL_FLIP_NONE);
	}
	SDL_RenderCopy(renderer, Hred, NULL, &Hrect);
}


//function to create the bullet
void playerObject::makeBullet() {
	if (bulln) {
		int ngt = Mix_PlayChannel(-1, bullsound, 0);
		n++;
		bull = (struct bullet*)realloc(bull, n * sizeof(struct bullet));
		(bull + n - 1)->bullAng = ang;
		(bull + n - 1)->bullAngR = (M_PI * ((bull + n - 1)->bullAng)) / (double)180;
		(bull + n - 1)->bullpos.x = (int)((destRect.x - (cos((bull + n - 1)->bullAngR) * (destRect.w / 2)) + (destRect.w / 2)) - transform->x);
		(bull + n - 1)->bullpos.y = (int)((destRect.y - (sin((bull + n - 1)->bullAngR) * (destRect.h / 2)) + (destRect.h / 2)) - transform->y);
		(bull + n - 1)->bullRend.h = 4;
		(bull + n - 1)->bullRend.w = 8;
		(bull + n - 1)->time = *time;
		(bull + n - 1)->isRendered = true;
		(bull + n - 1)->bullttux = 0;
		(bull + n - 1)->bullttuy = 0;
		bulln--;
	}
}
//function to move bullet
void playerObject::moveBullet(double delta_time) {
	for (int i = 1; i < n; i++) {
		(bull + i)->bullpos.MakeVel(bullvel, (bull + i)->bullAngR, &(bull + i)->bullttux, &(bull + i)->bullttuy, delta_time);
		(bull + i)->bullRend.x = (bull + i)->bullpos.x + transform->x;
		(bull + i)->bullRend.y = (bull + i)->bullpos.y + transform->y;
	}
}
//function to free bullet memory
void playerObject::bulletDestroy() {
	struct bullet bu[100];
	int k = 0;
	for (int i = 1; i < n; i++) {
		if (*time >= ((bull + i)->time + 5)) {
			bu[i-1] = *(bull + i);
			k += 1;
		}
	}
	n = k + 1;
	bull = (struct bullet*)realloc(bull, n * sizeof(struct bullet));
	for (int i = 1; i < n; i++) {
		*(bull + i) = bu[i - 1];
	}
}