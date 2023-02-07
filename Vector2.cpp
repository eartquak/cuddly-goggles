#include "include/Vector2.h"

Vector2::Vector2()
{
}

Vector2::~Vector2()
{
}

void Vector2::MakeVel(double vel, double angR, double* ttux, double* ttuy, double delta_time, int m)
{
	*ttuy += vel * delta_time * sin(angR) * (double)m;
	*ttux += vel * delta_time * cos(angR) * (double)m;
	if (*ttuy >= 1) {
		y -= 1;
		*ttuy = 0;
	}
	else if (*ttuy <= -1) {
		y += 1;
		*ttuy = 0;
	}
	else if (*ttux >= 1) {
		x -= 1;
		*ttux = 0;
	}
	else if (*ttux <= -1) {
		x += 1;
		*ttux = 0;
	}
}