#include "game.h"

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

void game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL not initialized\n");

		return;
	}
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_OPENGL);
	SDL_GLContext GLContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, GLContext);
	if (!window)
	{
		printf("window not created\n");
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{	
		printf("renderer not created\n");
		return;
	}
	//SDL_RenderSetScale(renderer, 0.5, 0.5);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_GL_SetSwapInterval(-1);
	isRunning = true;

	mChar = new playerObject();
	map = new Map();
	enemyObj = new enemyObject();
	
	mChar->init(renderer);
	mCharPos = &(mChar->destRect);
	(*mCharPos).x = (*mCharPos).y = SCREEN_SIZE / 2;
	safePos = *mCharPos;
	mChar->time = &time;

	map->init(renderer);
	
	transform = &(map->rect);
	mChar->transform = transform;
	
	printf("%p", transform);
	
	enemyObj->init(renderer, transform, mCharPos);
	
	prev_tick = SDL_GetPerformanceCounter();
	
	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(renderer, &rendererInfo);
	printf("%s", rendererInfo.name);

	SDL_Surface* tmpSurface = IMG_Load("Assets/bullet.png");
	bullTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
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
	//mCharPos = mChar->destRect;
	map->update(delta_time, mu, mr);
	//transform = map->rect;
	enemyObj->update(delta_time);
	cnt++;
	time += delta_time;
	fps_time += delta_time;
	if ((bool)(((int)fps_time) || 0)) {
		//printf("\r");
		//printf("%d", cnt);
	}
	cnt = (not (bool)(((int)fps_time) || 0)) * cnt;
	fps_time = (not (bool)(((int)fps_time) || 0)) * fps_time;
	checkCollision();
	mChar->bulletDestroy();
	//printf("%d, %d\n", mCharPos.x, mCharPos.y);
}

void game::render()
{
	SDL_RenderClear(renderer);
	map->render();
	enemyCreate();
	mChar->render();
	enemyObj->render();
	SDL_RenderPresent(renderer);
}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game quit\n");
}

void game::checkCollision()
{
	if ((256 + 64 >= (*transform).x + 1024) || (256  <= (*transform).x)) {
		*transform = safePos;
	}

	if ((256 + 64 >= (*transform).y + 1024) || (256 <= (*transform).y)) {
		*transform = safePos;
	}

	else {
		safePos = *transform;
		//printf("%d, %d", (*transform).x, (*transform).y);
	}
}

