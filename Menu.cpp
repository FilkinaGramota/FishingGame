#include "Menu.h"
#include <chrono>
#include <cmath>
#include <iostream>


Menu::Menu(SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height)
{
	font = TTF_OpenFont("./font/8bitOperatorPlus8-Bold.ttf", 32); // last numer = resolution

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	// Pixels from our text
	//SDL_Surface* 
	surfaceText = TTF_RenderText_Solid(font, "FISH or TRASH (version 3.14.15.92.65)", { 255, 255, 255 });
	// Create the texture
	texture_T = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_T.w = 350;
	text_box_T.h = 50;
	text_box_T.x = (window_width / 2) - 120;
	text_box_T.y = 70;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	surfaceText = TTF_RenderText_Solid(font, "START GAME: press S", { 255, 255, 255 });
	texture_S = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_S.w = 200;
	text_box_S.h = 40;
	text_box_S.x = (window_width / 2) - 100;
	text_box_S.y = text_box_T.y + text_box_T.h + 70;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	surfaceText = TTF_RenderText_Solid(font, "SHOW RESULTS: press R", { 255, 255, 255 });
	texture_Rb = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_Rb.w = 200;
	text_box_Rb.h = 40;
	text_box_Rb.x = (window_width / 2) - 100;
	text_box_Rb.y = text_box_S.y + text_box_S.h + 10;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	surfaceText = TTF_RenderText_Solid(font, "QUIT: press Q", { 255, 255, 255 });
	texture_Q = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_Q.w = 120;
	text_box_Q.h = 40;
	text_box_Q.x = (window_width / 2) - 60;
	text_box_Q.y = text_box_Rb.y + text_box_Rb.h + 10;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GAME MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	surfaceText = TTF_RenderText_Solid(font, "MENU: M", { 255, 255, 255 });
	texture_M = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_M.x = 1;
	text_box_M.y = 1;
	text_box_M.w = 50;
	text_box_M.h = 20;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	surfaceText = TTF_RenderText_Solid(font, "QUIT: Q", { 255, 255, 255 });
	texture_Qg = SDL_CreateTextureFromSurface(renderer, surfaceText);
	text_box_Qg.x = 1;
	text_box_Qg.y = text_box_M.y + text_box_M.h + 2;
	text_box_Qg.w = 50;
	text_box_Qg.h = 20;
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;

	text_box_time.x = window_width - 100;
	text_box_time.y = 1;
	text_box_time.w = 90;
	text_box_time.h = 20;
	
	text_box_score.x = window_width - 100;
	text_box_score.y = text_box_M.y + text_box_time.h + 2;
	text_box_score.w = 90;
	text_box_score.h = 20;

	text_box_my_score.w = 300;
	text_box_my_score.h = 40;
	text_box_my_score.x = (window_width / 2) - 150;
	text_box_my_score.y = 20;
	
	text_box_results[0].w = 200;
	text_box_results[0].h = 20;
	text_box_results[0].x = (window_width / 2) - 100;
	text_box_results[0].y = 80;

	for (int i = 1; i < 11; i++)
	{
		text_box_results[i].w = 100;
		text_box_results[i].h = 20;
		text_box_results[i].x = (window_width / 2) - 50;
		text_box_results[i].y = text_box_results[i - 1].y + 30;
	}

	// read results from the file
	file_read.open("best_10_results.txt");
	printf("\n RESULTS:");
	for (int i = 0; i < 10; i++)
	{
		file_read >> best_scores[i];
		printf("\n %d. %d", i+1, best_scores[i]);
	}

	file_read.close();

	//SDL_Surface* surface = nullptr;
	// create fishes
	all_fishes = new Fish[N_fish];
	for (int i = 0; i < N_fish; i++)
		all_fishes[i].create(surfaceText, renderer, i, window_width, window_height);
	
	// create garbages
	all_garbages = new Garbage[N_garbage];
	for (int i = 0; i < N_garbage; i++)
		all_garbages[i].create(surfaceText, renderer, i, window_width, window_height);

	// create hook
	hook.create(surfaceText, renderer, window_width);

	//SDL_FreeSurface(surfaceText);
	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;
}

Menu::~Menu()
{
	SDL_FreeSurface(surfaceText);

	SDL_DestroyTexture(texture_T);
	SDL_DestroyTexture(texture_S);
	SDL_DestroyTexture(texture_Rb);
	SDL_DestroyTexture(texture_R);
	SDL_DestroyTexture(texture_M);
	SDL_DestroyTexture(texture_Q);
	SDL_DestroyTexture(texture_Qg);
	SDL_DestroyTexture(texture_time);
	SDL_DestroyTexture(texture_score);

	// dispose the font
	TTF_CloseFont(font);

	delete[] all_fishes;
	delete[] all_garbages;
}


void Menu::show_main_menu(SDL_Renderer* renderer)
{
	game_menu_pressed_M = false;
	// clear all
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer); // clear everything with the drawing color

	SDL_RenderCopy(renderer, texture_T, NULL, &text_box_T);
	SDL_RenderCopy(renderer, texture_S, NULL, &text_box_S);
	SDL_RenderCopy(renderer, texture_Rb, NULL, &text_box_Rb);
	SDL_RenderCopy(renderer, texture_Q, NULL, &text_box_Q);

	SDL_RenderPresent(renderer); // update the window => show what we paint
}


void Menu::main_menu_loop(bool& quit, SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height)
{
	show_main_menu(renderer);
	bool update_results = true;

	// Checking events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // pressed button "close"
			quit = true;
			break;

		case SDL_KEYDOWN: // pressed a keyboard button (any button)
			switch (event.key.keysym.scancode) // check what the button was pressed
			{
			case SDL_SCANCODE_Q: // pressed Q
				quit = true;
				break;
			case SDL_SCANCODE_S: // pressed S
				// gaming loop
				start_timer = std::chrono::system_clock::now(); // start timer
				timer_over = false;
				total_score = 0;
				update_results = true;
				init_game_objects(renderer, window_width, window_height);
				start_game(quit, event, window, renderer, window_width, window_height);
				save_result(quit, event, renderer, update_results);
				if (game_menu_pressed_M)
				{
					quit = false;
					show_main_menu(renderer);
				}
				break;
			case SDL_SCANCODE_R: // pressed R
				show_results(quit, event, renderer);
				if (game_menu_pressed_M)
				{
					quit = false;
					show_main_menu(renderer);
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}


void Menu::init_game_objects(SDL_Renderer* renderer, int window_width, int window_height)
{
	// Hook
	hook.busy = false;
	hook.bound.x = window_width / 2 - hook.bound.w;
	hook.bound.y = 0;
	SDL_RenderCopy(renderer, hook.texture, NULL, &hook.bound);

	// Fish
	for (int i = 0; i < N_fish; i++)
	{
		all_fishes[i].hook_on = false;
		all_fishes[i].catched = false;
		all_fishes[i].bound.x = rand() % window_width;
		all_fishes[i].bound.y = 100 + (rand() % (window_height - 150));
		SDL_RenderCopy(renderer, all_fishes[i].texture, NULL, &all_fishes[i].bound);
	}

	// Garbage
	for (int i = 0; i < N_garbage; i++)
	{
		all_garbages[i].hook_on = false;
		all_garbages[i].catched = false;
		all_garbages[i].bound.x = rand() % window_width;
		all_garbages[i].bound.y = 100 + (rand() % (window_height - 130));
		SDL_RenderCopy(renderer, all_garbages[i].texture, NULL, &all_garbages[i].bound);
	}
}


// gaming loop
void Menu::start_game(bool& quit, SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height)
{
	bool update_results = true;

	while (!quit && !timer_over)
	{
		// Checking events for hook moving
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // pressed button "close"
				quit = true;
				break;

			case SDL_KEYDOWN: // pressed a keyboard button (any button)
				switch (event.key.keysym.scancode) // check what the button was pressed
				{
				case SDL_SCANCODE_Q: // pressed "Q"
					quit = true;
					break;
				case SDL_SCANCODE_M: // pressed "M"
					quit = true;
					game_menu_pressed_M = true;
					break;
				case SDL_SCANCODE_UP: // pressed "up"
					// Hook top boundary
					if (hook.bound.y + hook.bound.h >= hook.bound.h / 2)
						hook.bound.y = hook.bound.y - hook.speed;
					break;
				case SDL_SCANCODE_DOWN: // pressed "down"
					// Hook bottom boundary
					if (hook.bound.y + hook.bound.h < window_height)
						hook.bound.y = hook.bound.y + hook.speed;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}


		// clear all
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer); // clear everything with the drawing color

		// Hook
		SDL_RenderCopy(renderer, hook.texture, NULL, &hook.bound);

		// Fish
		for (int i = 0; i < N_fish; i++)
		{
			if (!all_fishes[i].catched)
				all_fishes[i].collision(hook);

			if (!all_fishes[i].hook_on) // standard move for free fish
				all_fishes[i].move(renderer, window_width);
			else // if on a hook
			{
				if (!all_fishes[i].catched) // check if this fish was not catched before
				{
					all_fishes[i].bound.x = hook.bound.x;
					all_fishes[i].bound.y = hook.bound.y + hook.bound.h - all_fishes[i].bound.h;

					if (hook.bound.y + hook.bound.h <= hook.bound.h / 2) // fish is catched
					{
						all_fishes[i].catched = true;
						all_fishes[i].bound.y = -all_fishes[i].bound.h;
						total_score = total_score + all_fishes[i].cost;
						hook.busy = false;
					}
				}
			}

			SDL_RenderCopy(renderer, all_fishes[i].texture, NULL, &all_fishes[i].bound);
		}

		// Garbage
		for (int i = 0; i < N_garbage; i++)
		{
			if (!all_garbages[i].catched)
				all_garbages[i].collision(hook);

			if (!all_garbages[i].hook_on)
				all_garbages[i].move(renderer, window_width);
			else
			{
				if (!all_garbages[i].catched)
				{
					all_garbages[i].bound.x = hook.bound.x;
					all_garbages[i].bound.y = hook.bound.y + hook.bound.h - all_garbages[i].bound.h;

					if (hook.bound.y + hook.bound.h <= hook.bound.h / 2) // garbage is catched
					{
						all_garbages[i].catched = true;
						all_garbages[i].bound.y = -all_garbages[i].bound.h;
						total_score = total_score + all_garbages[i].cost;
						hook.busy = false;
					}
				}
			}

			SDL_RenderCopy(renderer, all_garbages[i].texture, NULL, &all_garbages[i].bound);
		}

		// Text box
		show_game_menu(window, renderer);


		SDL_RenderPresent(renderer); // update the window => show what we paint
		SDL_Delay(1000 / 20);

		
		SDL_DestroyTexture(texture_time);
		SDL_DestroyTexture(texture_score);
		texture_time = nullptr;
		texture_score = nullptr;			

	}
}


void Menu::show_game_menu(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture_M, NULL, &text_box_M);
	SDL_RenderCopy(renderer, texture_Qg, NULL, &text_box_Qg);

	end = std::chrono::system_clock::now();

	total_seconds = (end - start_timer);
	min = int(120 - total_seconds.count()) / 60;
	sec = int(120 - total_seconds.count()) % 60;
	if (min == 0 && sec == 0)
		timer_over = true;

	if (sec >= 10)
	time_s = "TIME: 0" + std::to_string(min) + ":" + std::to_string(sec);
	else
		time_s = "TIME: 0" + std::to_string(min) + ":0" + std::to_string(sec);

	surfaceText = TTF_RenderText_Solid(font, time_s.c_str(), { 255, 255, 255 });
	if (min == 0 && sec <= 10)
		surfaceText = TTF_RenderText_Solid(font, time_s.c_str(), { 255, 0, 0 });
	texture_time = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_RenderCopy(renderer, texture_time, NULL, &text_box_time);

	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;
	
	total_score_s = "SCORE: " + std::to_string(total_score) + " ";
	surfaceText = TTF_RenderText_Solid(font, total_score_s.c_str(), { 255, 255, 255 });
	texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_RenderCopy(renderer, texture_score, NULL, &text_box_score);

	SDL_FreeSurface(surfaceText);
	surfaceText = nullptr;
}



void Menu::save_result(bool& quit, SDL_Event& event, SDL_Renderer* renderer, bool& update_results)
{
	if (update_results)
	{
		int old_best_results[10];
		int idx = 0;
		bool first_max = false;

		for (int i = 0; i < 10; i++)
		{
			old_best_results[i] = best_scores[i];
			if (std::max(total_score, best_scores[i]) == total_score && !first_max)
			{
				idx = i;
				first_max = true;
			}
		}

		if (first_max) // if something changes in results
		{
			best_scores[idx] = total_score;
			file_save.open("best_10_results.txt");
			for (int i = 0; i < 10; i++)
			{
				if (i > idx)
					best_scores[i] = old_best_results[i - 1];
				file_save << best_scores[i] << "\n";
			}
			file_save.close();
		}

		update_results = false;
	}

	while (!quit)
	{
		// Checking events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // pressed button "close"
				quit = true;
				break;

			case SDL_KEYDOWN: // pressed a keyboard button (any button)
				switch (event.key.keysym.scancode) // check what the button was pressed
				{
				case SDL_SCANCODE_Q: // pressed "Q"
					quit = true;
					break;
				case SDL_SCANCODE_M: // pressed "M"
					quit = true;
					game_menu_pressed_M = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		// Show results
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer); // clear everything with the drawing color

		SDL_RenderCopy(renderer, texture_M, NULL, &text_box_M);
		SDL_RenderCopy(renderer, texture_Qg, NULL, &text_box_Qg);

		total_score_s = "YOUR SCORE: " + std::to_string(total_score);
		surfaceText = TTF_RenderText_Solid(font, total_score_s.c_str(), { 0, 255, 0 });
		texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);

		SDL_RenderCopy(renderer, texture_score, NULL, &text_box_my_score);
		SDL_FreeSurface(surfaceText);
		SDL_DestroyTexture(texture_score);
		surfaceText = nullptr;
		texture_score = nullptr;


		surfaceText = TTF_RenderText_Solid(font, "RESULTS", { 255, 255, 255 });
		texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);
		SDL_RenderCopy(renderer, texture_score, NULL, &text_box_results[0]);
		SDL_FreeSurface(surfaceText);
		SDL_DestroyTexture(texture_score);
		surfaceText = nullptr;
		texture_score = nullptr;

		for (int i = 1; i < 11; i++)
		{
			total_score_s = std::to_string(i) + ".  " + std::to_string(best_scores[i - 1]);
			surfaceText = TTF_RenderText_Solid(font, total_score_s.c_str(), { 255, 255, 255 });
			texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);
			SDL_RenderCopy(renderer, texture_score, NULL, &text_box_results[i]);
			SDL_DestroyTexture(texture_score);
			SDL_FreeSurface(surfaceText);
			surfaceText = nullptr;
			texture_score = nullptr;
		}

		SDL_RenderPresent(renderer); // update the window => show what we paint
	}
}

void Menu::show_results(bool& quit, SDL_Event& event, SDL_Renderer* renderer)
{
	// system("cls"); // clear console;
	printf("RESULTS:");
	for (int i = 0; i < 10; i++)
		printf("\n %d. %d", i+1, best_scores[i]);

	while (!quit)
	{
		// Checking events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: // pressed button "close"
				quit = true;
				break;

			case SDL_KEYDOWN: // pressed a keyboard button (any button)
				switch (event.key.keysym.scancode) // check what the button was pressed
				{
				case SDL_SCANCODE_Q: // pressed "Q"
					quit = true;
					break;
				case SDL_SCANCODE_M: // pressed "M"
					quit = true;
					game_menu_pressed_M = true;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		// Show results
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer); // clear everything with the drawing color

		SDL_RenderCopy(renderer, texture_M, NULL, &text_box_M);
		SDL_RenderCopy(renderer, texture_Qg, NULL, &text_box_Qg);

		// Show all results
		surfaceText = TTF_RenderText_Solid(font, "RESULTS", { 255, 255, 255 });
		texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);
		SDL_RenderCopy(renderer, texture_score, NULL, &text_box_results[0]);
		SDL_DestroyTexture(texture_score);
		SDL_FreeSurface(surfaceText);
		surfaceText = nullptr;
		texture_score = nullptr;

		for (int i = 1; i < 11; i++)
		{
			total_score_s = std::to_string(i) + ".  " + std::to_string(best_scores[i - 1]);
			surfaceText = TTF_RenderText_Solid(font, total_score_s.c_str(), { 255, 255, 255 });
			texture_score = SDL_CreateTextureFromSurface(renderer, surfaceText);
			SDL_RenderCopy(renderer, texture_score, NULL, &text_box_results[i]);
			SDL_DestroyTexture(texture_score);
			SDL_FreeSurface(surfaceText);
			surfaceText = nullptr;
			texture_score = nullptr;
		}

		SDL_RenderPresent(renderer); // update the window => show what we paint
	}
}

