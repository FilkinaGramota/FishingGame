#pragma once
#include <SDL/SDL.h>

// HOOK
class Hook
{
public:
	int speed = 10;
	SDL_Rect bound;
	SDL_Texture* texture = nullptr;

	bool busy = false; // true => something on it
	Hook();
	void create(SDL_Surface* surface, SDL_Renderer* renderer, int window_width); // constructor
	~Hook(); // desctructor

	void draw(SDL_Renderer* renderer); // not nes
};