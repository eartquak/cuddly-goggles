#include "include/Vector2.h"

Vector2::Vector2()
{
}

Vector2::~Vector2()
{
}

void Vector2::MakeVel(double vel, double angR, double* ttux, double* ttuy, double delta_time, int m)
{
	y -= vel * delta_time * sin(angR) * (double)m;
	x -= vel * delta_time * cos(angR) * (double)m;
}