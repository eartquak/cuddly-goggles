#include "game.h"

playerObject* mChar = nullptr;
makeMap* map = nullptr;

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
	wh = ww = 512;
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ww, wh, 0);
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
	map = new makeMap();
	int pos[2] = { ww/2, wh/2 };
	mChar->pos = pos;
	mChar->ang = 0;
	int dim[2] = { 32, 32 };
	mChar->init(dim, renderer);
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
		default:
			break;
	}
	
}

void game::update()
{
	Uint64 cur_tick = SDL_GetPerformanceCounter();
	delta_time = static_cast<double>((cur_tick - prev_tick) / static_cast<double>(SDL_GetPerformanceFrequency()));
	prev_tick = cur_tick;
	mChar->update(delta_time);
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