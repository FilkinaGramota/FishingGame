#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Hook.h"
#include "Fish.h"
#include "Garbage.h"
#include "Menu.h"












/* command line arguments :
 argc -- argument count (number of argumbets)
 argv -- argument vector (array of string)
 */
int main(int argc, char** argv)
{
	srand(time(0)); // to generate random numbers

	int window_width = 640;
	int window_height = 480;

	SDL_Init(SDL_INIT_EVERYTHING); // init SDL

	// window
	SDL_Window* window = SDL_CreateWindow("Fish_or_Trash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	// painter
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // set the background color 
	SDL_RenderClear(renderer); // clear everything with the drawing color
	SDL_RenderPresent(renderer); // update the window => show what we paint


	//// create a surface to load an image in memory 
	//SDL_Surface* surface = nullptr;

	//int N_fish = 15; // total number of fishes
	//Fish* all_fishes = new Fish[N_fish]; // array of fishes
	//// initialization
	//for (int i = 0; i < N_fish; i++)
	//	all_fishes[i].create(surface, renderer, i, window_width, window_height);

	//int N_garbage = 7; // total number of garabes
	//Garbage* all_garbages = new Garbage[N_garbage]; // array of garbage
	//// initialization
	//for (int i = 0; i < N_garbage; i++)
	//	all_garbages[i].create(surface, renderer, i, window_width, window_height);

	//// Create a hook
	//Hook hook(surface, renderer, window_width);

	//// clear memory (we already save all images to the textures)
	//SDL_FreeSurface(surface);

	////SDL_RenderPresent(renderer); // update the window => show all fishes, trash, and hook

	TTF_Init(); // init SDL_ttf (to work with text)
	Menu menu(window, renderer, window_width, window_height);

	// ~~~~~~~~~~~~~~~ GAMING LOOP ~~~~~~~~~~~~~~~ //   
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		menu.main_menu_loop(quit, event, window, renderer, window_width, window_height);

	}


	//free memory
	//delete[] all_fishes;
	//delete[] all_garbages;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//close SDL
	SDL_Quit();

	return 0;
}
