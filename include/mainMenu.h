#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Vector2.h"

class mainMenu
{
public:
	mainMenu();
	~mainMenu();
	void init();
	void handleEvent();
	void update();
	void render();
	void clean();
	void play_game();
	bool running() {
		return isRunning;
	}
private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	Uint64 butt = 0;

	TTF_Font* PixelF = nullptr;

	SDL_Texture* borderTex = nullptr;
	SDL_Rect borrect;

	SDL_Texture* Name;
	SDL_Rect name_mr;
	SDL_Texture* Play;
	SDL_Rect play_mr;
	SDL_Texture* Saved_Game;
	SDL_Rect saved_game_mr;
	SDL_Texture* Settings;
	SDL_Rect settings_mr;
	SDL_Texture* Quit;
	SDL_Rect quit_mr;
	int x, y;
	int wx, wy;
};

