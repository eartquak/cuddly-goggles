#include "playerObject.h"

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
	destRect.w = destRect.h = 64;
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/player.png");
	gObjTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	bull = (struct bullet*)malloc(sizeof(struct bullet));
}

void playerObject::update(double delta_time, int mu, int mr)
{
	SDL_GetMouseState(&x, &y);
	ang = ((double)180 * atan2((double)((destRect.y + destRect.h / 2) - y), (double)((destRect.x + destRect.w / 2) - x)) / M_PI);
	if (game::event.type == SDL_MOUSEBUTTONDOWN) {
		switch (game::event.button.button) {
		case SDL_BUTTON_LEFT:
			if (bulln) {
				n++;
				bull = (struct bullet*)realloc(bull, n * sizeof(struct bullet));
				(bull + n - 1)->bullAng = ang;
				(bull + n - 1)->bullAngR = (M_PI * ((bull + n - 1)->bullAng)) / (double)180;
				(bull + n - 1)->bullRect.x = (destRect.x - (cos((bull + n - 1)->bullAngR) * (destRect.w / 2)) + (destRect.w / 2)) - (*transform).x;
				(bull + n - 1)->bullRect.y = (destRect.y - (sin((bull + n - 1)->bullAngR) * (destRect.h / 2)) + (destRect.h / 2)) - (*transform).y;
				(bull + n - 1)->bullRend.h = 4;
				(bull + n - 1)->bullRend.w = 8;
				(bull + n - 1)->time = *time;
				(bull + n - 1)->isRendered = true;
				bulln--;
				//printf("(%f)\n", (bull + n - 1)->bullAng);
			}
		}
	}
	//printf("%lf", *time);
	// printf("%d, %d\n", x, y);

	ang = ((double)180 * atan2((double)((destRect.y + destRect.h/2)-y), (double)((destRect.x + destRect.w / 2) - x)) / M_PI);
	makeBullet(delta_time);
}

void playerObject::render()
{
	for (int i = 1; i < n; i++) {
		if ((bull + i)->isRendered) {
			SDL_RenderCopyEx(renderer, bullTex, NULL, &((bull + i)->bullRend), (bull + i)->bullAng, NULL, SDL_FLIP_NONE);
		}
		//printf("%lf ", (bull + i)->time);
	}
	//printf("\n");
	SDL_RenderCopyEx(renderer, gObjTex, NULL, &destRect, ang, NULL, SDL_FLIP_NONE);
}

void playerObject::makeBullet(double delta_time) {
	for (int i = 1; i < n; i++) {
		((bull + i)->bullttuy) += bullvel * delta_time * sin((bull + i)->bullAngR);
		if ((bull + i)->bullttuy >= 1) {
			(bull + i)->bullRect.y -= 1;
			(bull + i)->bullttuy = 0;
		}
		else if ((bull + i)->bullttuy <= -1) {
			(bull + i)->bullRect.y += 1;
			(bull + i)->bullttuy = 0;
		}
		((bull + i)->bullttux) += bullvel * delta_time * cos((bull + i)->bullAngR);
		if ((bull + i)->bullttux >= 1) {
			(bull + i)->bullRect.x -= 1;
			(bull + i)->bullttux = 0;
		}
		else if ((bull + i)->bullttux <= -1) {
			(bull + i)->bullRect.x += 1;
			(bull + i)->bullttux = 0;
		}
		(bull + i)->bullRend.x = (bull + i)->bullRect.x + (*transform).x;
		(bull + i)->bullRend.y = (bull + i)->bullRect.y + (*transform).y;
	}
}

void playerObject::bulletDestroy() {
	struct bullet bu[100];
	int k = 0;
	for (int i = 1; i < n; i++) {
		if (*time <= ((bull + i)->time + 2)) {
			bu[i-1] = *(bull + i);
			k += 1;
			//printf("%lf ", bu[i-1].time);
		}
	}
	//printf("\n");
	//printf("%lf", bu[]);
	n = k + 1;
	bull = (struct bullet*)realloc(bull, n * sizeof(struct bullet));
	for (int i = 1; i < n; i++) {
		*(bull + i) = bu[i - 1];
		//printf("%lf\n", bu[n - 1].time);
	}
}