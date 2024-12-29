#pragma once

#include <SDL/SDL.h>
#include "Hook.h"

// FISH
class Fish
{
public:
	int speed;
	bool left_to_right; // direction of movement
	int cost; // how much you will receive if you catch this fish
	SDL_Rect bound;
	SDL_Rect intersect;
	SDL_Texture* texture = nullptr;

	bool hook_on = false; // true => there is a collision with a hook
	bool catched = false; // true => not anymore visible on the screen

	Fish(); // constructor
	~Fish();

	void create(SDL_Surface* surface, SDL_Renderer* renderer, int id, int window_width, int window_height);
	void draw(SDL_Renderer* renderer);
	void move(SDL_Renderer* renderer, int window_width);
	void collision(Hook& hook);
};
