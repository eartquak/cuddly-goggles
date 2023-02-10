#pragma once
#include <SDL.h>

class Vector2
{
public:
	Vector2();
	~Vector2();
	float x = 0;
	float y = 0;
	SDL_Rect rect;
	void MakeVel(double vel, double angR, double *ttux, double *ttuy, double delta_time, int m = 1);
};

