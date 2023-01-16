#include "playerObject.h"

playerObject::playerObject()
{
}

playerObject::~playerObject()
{
	SDL_DestroyTexture(gObjTex);
}

void playerObject::init(int *dim, SDL_Renderer *render)
{	
	renderer = render;
	SDL_Surface* tmpSurface = IMG_Load("Assets/player.png");
	gObjTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	destRect.h = *dim;
	destRect.w = *(dim + 1);
	destRect.x = *pos - (*dim/2);
	destRect.y = *(pos + 1) - (*(dim + 1)/2);
	tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	bullRect.w = 4;
	bullRect.h = 2;
}

void playerObject::update(double delta_time)
{
	if (game::event.type == SDL_KEYDOWN)
	{
		switch (game::event.key.keysym.sym)
		{
			case SDLK_w:
				my = -1;
				break;
			case SDLK_a:
				mx = -1;
				break;
			case SDLK_s:
				my = 1;
				break;
			case SDLK_d:
				mx = 1;
				break;
		}
	}

	else if (game::event.type == SDL_KEYUP)
	{
		switch (game::event.key.keysym.sym)
		{
		case SDLK_w:
			my = 0;
			break;
		case SDLK_a:
			mx = 0;
			break;
		case SDLK_s:
			my = 0;
			break;
		case SDLK_d:
			mx = 0;
			break;
		}
	}

	if (game::event.type == SDL_MOUSEBUTTONDOWN) {
		switch (game::event.button.button) {
		case SDL_BUTTON_LEFT:
			/*n++;
			bullRect = (SDL_Rect*)realloc(bullRect, n*sizeof(SDL_Rect));
			bullAng = (float*)realloc(bullAng, n * sizeof(float));
			(*(bullRect + n)).x = (destRect.x + destRect.w/2);
			(*(bullRect + n)).y = (destRect.y + destRect.h / 2);
			(*(bullRect + n)).h = 2;
			(*(bullRect + n)).w = 4;
			*(bullAng + n) = ang;*/
			bullRect.x = destRect.x;
			bullRect.y = destRect.y;
			bullAng = ang;
		}
	}
	SDL_GetMouseState(&x, &y);
	// printf("%d, %d\n", x, y);

	ttuy += vel * delta_time * (double)my;
	if (ttuy >= 1) {
		destRect.y += 1;
		ttuy = 0;
	}
	else if (ttuy <= -1) {
		destRect.y -= 1;
		ttuy = 0;
	}

	ttux += vel * delta_time * (double)mx;
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
	SDL_RenderCopyEx(renderer, gObjTex, NULL, &destRect, ang, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, bullTex, NULL, &bullRect, bullAng, NULL, SDL_FLIP_NONE);
}

void playerObject::makeBullet(double delta_time) {
	printf("%lf", delta_time);
	bullttuy += bullvel * delta_time ;
	if (bullttuy >= 1) {
		bullRect.y += 1;
		bullttuy = 0;
	}
	else if (bullttuy <= -1) {
		bullRect.y -= 1;
		bullttuy = 0;
	}

	bullttux += bullvel * delta_time;
	if (bullttux >= 1) {
		bullRect.x += 1;
		bullttux = 0;
	}
	else if (bullttux <= -1) {
		bullRect.x -= 1;
		bullttux = 0;
	}
	printf("%lf, %lf\n", bullttux, bullttuy);
}
