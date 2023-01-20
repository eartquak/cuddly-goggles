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
			n++;
			bull = (struct bullet*)realloc(bull, n * sizeof(struct bullet));
			(bull + n - 1)->bullAng = ang;
			(bull + n - 1)->bullAngR = (M_PI * ((bull + n - 1)->bullAng)) / (double)180;
			(bull + n - 1)->bullRect.x = (destRect.x - (cos((bull + n - 1)->bullAngR)*(destRect.w/2)) + (destRect.w / 2));
			(bull + n - 1)->bullRect.y = (destRect.y - (sin((bull + n - 1)->bullAngR)*(destRect.h/2)) + (destRect.h / 2));
			(bull + n - 1)->bullRect.h = 4;
			(bull + n - 1)->bullRect.w = 8;
			//printf("(%d, %d, %f, %d)", (bull + n - 1)->bullRect.x, (bull + n - 1)->bullRect.y, (bull + n - 1)->bullAng, n);
		}
	}
	// printf("%d, %d\n", x, y);

	ttuy += vel * delta_time * mu;
	if (ttuy >= 1) {
		destRect.y += 1;
		ttuy = 0;
	}
	else if (ttuy <= -1) {
		destRect.y -= 1;
		ttuy = 0;
	}

	ttux += vel * delta_time * mr;
	if (ttux >= 1) {
		destRect.x += 1;
		ttux = 0;
	}
	else if (ttux <= -1) {
		destRect.x -= 1;
		ttux = 0;
	}

	ang = ((double)180 * atan2((double)((destRect.y + destRect.h/2)-y), (double)((destRect.x + destRect.w / 2) - x)) / M_PI);
	makeBullet(delta_time);
}

void playerObject::render()
{
	for (int i = 1; i < n; i++) {
		SDL_RenderCopyEx(renderer, bullTex, NULL, &((bull+i)->bullRect), (bull+i)->bullAng, NULL, SDL_FLIP_NONE);
	}
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
	}
}
