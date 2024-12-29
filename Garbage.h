#pragma once

#include <SDL/SDL.h>
#include "Hook.h"

// GARBAGE
class Garbage
{
public:
	int speed;
	int cost; // how much you will receive if you catch this fish
	SDL_Rect bound;
	SDL_Rect intersect;
	SDL_Texture* texture = nullptr;

	bool hook_on = false; // true => there is a collision with a hook
	bool catched = false; // true => not anymore visible on the screen

	Garbage();
	~Garbage();

	void create(SDL_Surface* surface, SDL_Renderer* renderer, int id, int window_width, int window_height);

	void draw(SDL_Renderer* renderer);
	void move(SDL_Renderer* renderer, int window_width);
	void collision(Hook& hook);
};
