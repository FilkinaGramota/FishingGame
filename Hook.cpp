#include "Hook.h"
#include <iostream>

Hook::Hook()
{

}

void Hook::create(SDL_Surface* surface, SDL_Renderer* renderer, int window_width)
{
	surface = SDL_LoadBMP("./image/hook_1conv.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	bound.w = 30; // width
	bound.h = 60; // height
	bound.x = window_width / 2 - bound.w;
	bound.y = 0;

	SDL_RenderCopy(renderer, texture, NULL, &bound);

	SDL_FreeSurface(surface);
}

Hook::~Hook()
{
	SDL_DestroyTexture(texture);
	printf("\n Destroyed Hook's texture ");
}



void Hook::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &bound);
}