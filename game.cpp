#include "game.h"

playerObject* mChar = nullptr;
Map* map = nullptr;

game::game()
{
}

game::~game()
{
}

SDL_Event game::event;

void game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL not initialized\n");

		return;
	}
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, 0);
	if (!window)
	{
		printf("window not created\n");
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{	
		printf("renderer not created\n");
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	isRunning = true;

	mChar = new playerObject();
	map = new Map();
	SDL_Rect mCharPos;
	mCharPos.x = mCharPos.y =  SCREEN_SIZE/2;
	mChar->destRect = mCharPos;
	mChar->init(renderer);
	map->init(renderer);
	prev_tick = SDL_GetPerformanceCounter();
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
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
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
			}
			break;
			//printf("%d, %d", mChar->mx, mChar->my);
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
	map->update(delta_time, mu, mr);
	cnt++;
	fps_time += delta_time;
	if ((bool)(((int)fps_time) || 0)) {
		printf("\r");
		printf("%d", cnt);
	}
	cnt = (not (bool)(((int)fps_time) || 0)) * cnt;
	fps_time = (not (bool)(((int)fps_time) || 0)) * fps_time;
}

void game::render()
{
	SDL_RenderClear(renderer);
	map->render(); 
	mChar->render();
	SDL_RenderPresent(renderer);
}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game quit\n");
}