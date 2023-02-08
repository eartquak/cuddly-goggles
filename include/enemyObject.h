#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <random>
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
	void enemy_random(struct enemy* enmy, double delta_time);
	void enemy_normal(struct enemy* enmy, double delta_time);
	void makeBullet(struct enemy* enmy);
	void moveBullet(double delta_time);
	void type1_movement(double delta_time, struct enemy *enmy);
	void type2_movement(double delta_time, struct enemy* enmy);
	void enbulletDestroy();
	int nEnemy = 1;
	//SDL_Rect uRect
	struct enemy* en = nullptr;
	class playerObject* plChar = nullptr;
	//Vector2 SCREEN_SIZE;
	//Vector2 MAP_SIZE;
	int PLAYER_SIZE;
	double *time = 0;
	struct enebullet* enbull;
	int nb;
	double bullvel = 500;
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* enemyTex = nullptr;
	SDL_Texture* enemyTex1 = nullptr;
	SDL_Texture* bullTex = nullptr;
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
	random_device rd1;
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
	double tr = 0;
	double ptr = 0;
	bool r = true;
	int type;
	int bulln;
};

struct enebullet {
	double bullAng = 0;
	double bullAngR = 0;
	Vector2 bullpos;
	SDL_Rect bullRend;
	double bullttux = 0;
	double bullttuy = 0;
	double time = 0;
	bool isRendered = true;
	
};