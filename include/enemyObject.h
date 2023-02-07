#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include "playerObject.h"
#include "Vector2.h"

using namespace std;

class enemyObject
{
public:
	enemyObject();
	~enemyObject();


	void init(SDL_Renderer* render, Vector2* r, SDL_Rect* pR);
	void update(double delta_time);
	void render();
	void enemyCreate(int x, int y);
	void enemyAttack(struct enemy* enmy);
	int nEnemy = 1;
	//SDL_Rect uRect
	struct enemy* en = nullptr;
	class playerObject* plChar = nullptr;
	Vector2 SCREEN_SIZE;
	Vector2 MAP_SIZE;
	int PLAYER_SIZE;
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* enemyTex = nullptr;
	//double ang = 0;
	//double angR = 0;
	//float tAng = 0;
	Vector2* transform = nullptr;
	SDL_Rect* mCharPos = nullptr;
	//double ttuy, ttux = 0;
	//double vel = 50;
	//SDL_Rect rect;
	//SDL_Rect spawn_rect;
	int ramble = 0;
};

struct enemy {
	Vector2 pos;
	SDL_Rect rend;
	double ang, angR = 0;
	double enettuy, enettux = 0;
	double time = 0;
	bool isRendered = true;
	int nHit = 0;
	bool isAngry = false;
	double vel = 50;
	int health = 100;
	double ttk = 0;
};