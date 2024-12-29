#include "Fish.h"
#include <iostream>


Fish::Fish()
{
	
}


void Fish::create(SDL_Surface* surface, SDL_Renderer* renderer, int id, int window_width, int window_height)
{
	speed = 2 + (rand() % 4); // [2; 3; 4; 5]
	left_to_right = true;

	if (id % 4 == 0)
	{
		surface = SDL_LoadBMP("./image/f_3.bmp");
		cost = 10 + (rand() % 10); // from 10 to 19
	}
	if (id % 4 == 1)
	{
		surface = SDL_LoadBMP("./image/f_4conv.bmp");
		cost = 20 + (rand() % 10); // from 20 to 29
		speed = -speed;
		left_to_right = false;
	}
	if (id % 4 == 2)
	{
		surface = SDL_LoadBMP("./image/f_colorful_conv.bmp");
		cost = 30 + (rand() % 10); // from 30 to 39
	}
	if (id % 4 == 3)
	{
		surface = SDL_LoadBMP("./image/f_simple_conv.bmp");
		cost = 40 + (rand() % 11); // from 40 to 50
		speed = -speed;
		left_to_right = false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	bound.w = 80; // width
	bound.h = 50; // height
	bound.x = rand() % window_width;
	bound.y = 100 + (rand() % (window_height - 150));

	SDL_RenderCopy(renderer, texture, NULL, &bound);

	SDL_FreeSurface(surface);
}

Fish::~Fish()
{
	SDL_DestroyTexture(texture);
	printf("\n Destroyed Fish's texture ");
}


void Fish::move(SDL_Renderer* renderer, int window_width)
{
	bound.x = bound.x + speed;
	// continue movement through the boundary
	if (bound.x > window_width && left_to_right)
		bound.x = -bound.w;
	if (bound.x + bound.w < 0 && !left_to_right)
		bound.x = window_width + bound.w;
}

void Fish::collision(Hook& hook)
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


void Fish::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &bound);
}

