#include "Garbage.h"
#include <iostream>


Garbage::Garbage()
{

}


void Garbage::create(SDL_Surface* surface, SDL_Renderer* renderer, int id, int window_width, int window_height)
{
	speed = 1 + (id % 3); // [1; 2; 3]

	if (id % 2 == 0)
	{
		surface = SDL_LoadBMP("./image/garbage_2conv.bmp");
		cost = -(10 + (rand() % 11)); // from 10 to 20
	}
	if (id % 2 == 1)
	{
		surface = SDL_LoadBMP("./image/garbage_3conv.bmp");
		cost = -(40 + (rand() % 11)); // from 40 to 50
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	bound.w = 40;
	bound.h = 40;
	bound.x = rand() % window_width;
	bound.y = 100 + (rand() % (window_height - 130));

	SDL_RenderCopy(renderer, texture, NULL, &bound);

	SDL_FreeSurface(surface);
}

Garbage::~Garbage()
{
	SDL_DestroyTexture(texture);
	printf("\n Destroyed Garbage's texture ");
}


void Garbage::move(SDL_Renderer* renderer, int window_width)
{
	bound.x = bound.x + speed;
	// continue movement through the boundary
	if (bound.x > window_width)
		bound.x = -bound.w;
}

void Garbage::collision(Hook& hook)
{
	SDL_bool sdl_hook_on = SDL_IntersectRect(&bound, &hook.bound, &intersect);

	if (sdl_hook_on)
	{
		if (!hook.busy)
		{
			hook_on = true;
			hook.busy = true;
		}
	}
}

void Garbage::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &bound);
}
