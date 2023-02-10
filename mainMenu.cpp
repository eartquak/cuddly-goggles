#include "include/mainMenu.h"
#include "include/game.h"

mainMenu::mainMenu()
{
}

mainMenu::~mainMenu()
{
}

game* game1 = nullptr;

void mainMenu::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL not initialized\n");

		return;
	}
	SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE.x, SCREEN_SIZE.x, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(window, &wx, &wy);
	SCREEN_SIZE.x = wx;
	SCREEN_SIZE.y = wy;
	MAP_SIZE.x = MAP_SIZE.y = SCREEN_SIZE.y;
	//SDL_GLContext GLContext = SDL_GL_CreateContext(window);
	//SDL_GL_MakeCurrent(window, GLContext);
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_GL_SetSwapInterval(-1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	TTF_Init();
	PixelF = TTF_OpenFont("Assets/PublicPixel.ttf", 18);

	Mix_Init(0);
	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024);

	isRunning = true;

	SDL_Surface* tmpSurface = IMG_Load("Assets/Border.png");
	borderTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(PixelF, "Very Generic Game", { 0, 0, 0 });
	Name = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	name_mr.h = SCREEN_SIZE.y / 9;
	name_mr.w = SCREEN_SIZE.x / 2;
	name_mr.x = SCREEN_SIZE.x / 2 - name_mr.w / 2;
	name_mr.y = SCREEN_SIZE.y / 5 - name_mr.h / 2;

	surfaceMessage = TTF_RenderText_Solid(PixelF, "Play", { 0, 0, 0 });
	Play = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	play_mr.h = SCREEN_SIZE.y / 10;
	play_mr.w = SCREEN_SIZE.x / 10;
	play_mr.x = SCREEN_SIZE.x / 2 - play_mr.w / 2;
	play_mr.y = SCREEN_SIZE.y / 2 - play_mr.h / 2;

	surfaceMessage = TTF_RenderText_Solid(PixelF, "Saved Games", { 0, 0, 0 });
	Saved_Game = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	saved_game_mr.h = SCREEN_SIZE.y / 10;
	saved_game_mr.w = (SCREEN_SIZE.x * 2.75) / 10;
	saved_game_mr.x = SCREEN_SIZE.x / 2 - saved_game_mr.w / 2;
	saved_game_mr.y = SCREEN_SIZE.y / 2 + SCREEN_SIZE.y / 9 - saved_game_mr.h / 2;

	surfaceMessage = TTF_RenderText_Solid(PixelF, "Settings", { 0, 0, 0 });
	Settings = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	settings_mr.h = SCREEN_SIZE.y / 10;
	settings_mr.w = (SCREEN_SIZE.x* 2) / 10;
	settings_mr.x = SCREEN_SIZE.x / 2 - settings_mr.w / 2;
	settings_mr.y = SCREEN_SIZE.y / 2 + (SCREEN_SIZE.y * 2) / 9 - settings_mr.h / 2;

	surfaceMessage = TTF_RenderText_Solid(PixelF, "Quit", { 0, 0, 0 });
	Quit = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	quit_mr.h = SCREEN_SIZE.y / 10;
	quit_mr.w = SCREEN_SIZE.x / 10;
	quit_mr.x = SCREEN_SIZE.x / 2 - quit_mr.w / 2;
	quit_mr.y = SCREEN_SIZE.y / 2 + (SCREEN_SIZE.y * 3) / 9 - quit_mr.h / 2;

	SDL_FreeSurface(surfaceMessage);

	borrect.x = saved_game_mr.x - 30;
	borrect.y = play_mr.y - 10;
	borrect.w = saved_game_mr.w + 60;
	borrect.h = saved_game_mr.h + 20;
}

void mainMenu::handleEvent()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}
	SDL_GetMouseState(&x, &y);
}

void mainMenu::update()
{
	if ((x > play_mr.x) && (x < (play_mr.x + play_mr.w)) && (y > play_mr.y) && (y < (play_mr.y + play_mr.h))) {
		borrect.x = saved_game_mr.x - 30;
		borrect.y = play_mr.y - 10;
		borrect.w = saved_game_mr.w + 60;
		borrect.h = saved_game_mr.h + 20;
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				play_game();
			}
		}
	}
	else if ((x > saved_game_mr.x) && (x < (saved_game_mr.x + saved_game_mr.w)) && (y > saved_game_mr.y) && (y < (saved_game_mr.y + saved_game_mr.h))) {
		borrect.x = saved_game_mr.x - 30;
		borrect.y = saved_game_mr.y - 10;
		borrect.w = saved_game_mr.w + 60;
		borrect.h = saved_game_mr.h + 20;
	}
	else if ((x > settings_mr.x) && (x < (settings_mr.x + settings_mr.w)) && (y > settings_mr.y) && (y < (settings_mr.y + settings_mr.h))) {
		borrect.x = saved_game_mr.x - 30;
		borrect.y = settings_mr.y - 10;
		borrect.w = saved_game_mr.w + 60;
		borrect.h = saved_game_mr.h + 20;
	}
	else if ((x > quit_mr.x) && (x < (quit_mr.x + quit_mr.w)) && (y > quit_mr.y) && (y < (quit_mr.y + quit_mr.h))) {
		borrect.x = saved_game_mr.x - 30;
		borrect.y = quit_mr.y - 10;
		borrect.w = saved_game_mr.w + 60;
		borrect.h = saved_game_mr.h + 20;
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				isRunning = false;
			}
		}
	}
}

void mainMenu::render()
{
	SDL_RenderClear(renderer);
	
	SDL_RenderCopy(renderer, Name, NULL, &name_mr);
	SDL_RenderCopy(renderer, Play, NULL, &play_mr);
	SDL_RenderCopy(renderer, Saved_Game, NULL, &saved_game_mr);
	SDL_RenderCopy(renderer, Settings, NULL, &settings_mr);
	SDL_RenderCopy(renderer, Quit, NULL, &quit_mr);
	SDL_RenderCopy(renderer, borderTex, NULL, &borrect);
	SDL_RenderPresent(renderer);
}

void mainMenu::play_game() {
	game1 = new game();
	game1->init(renderer);
	while (game1->running()) {
		game1->handleEvent();
		game1->update();
		game1->render();
	}
}

void mainMenu::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game quit\n");
}
