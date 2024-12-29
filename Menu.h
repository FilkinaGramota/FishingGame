#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <chrono>
#include <fstream>

#include "Fish.h"
#include "Garbage.h"
#include "Hook.h"

class Menu
{
private:
	std::ofstream file_save;
	std::ifstream file_read;
	std::chrono::time_point<std::chrono::system_clock> start_timer;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::duration<double> total_seconds;
	int min;
	int sec;
	std::string time_s;
	std::string total_score_s;

	int N_fish = 15;
	int N_garbage = 7;
	Fish* all_fishes = nullptr;
	Garbage* all_garbages = nullptr;
	Hook hook;

public:

	bool timer_over = false;
	int total_score = 0;
	int best_scores[10];
	bool game_menu_pressed_M = false; // press or not M during game

	SDL_Rect text_box_T; // title
	SDL_Rect text_box_S; // start game
	SDL_Rect text_box_R; // results
	SDL_Rect text_box_Rb; // results button
	SDL_Rect text_box_M; // menu
	SDL_Rect text_box_Q; // quit
	SDL_Rect text_box_Qg; // quit during game mode
	SDL_Rect text_box_time; // timer 
	SDL_Rect text_box_score; // score
	SDL_Rect text_box_my_score; // total user score after game
	SDL_Rect text_box_results [11]; // results

	TTF_Font* font = nullptr;

	SDL_Surface* surfaceText = nullptr;

	SDL_Texture* texture_T = nullptr; // title
	SDL_Texture* texture_S = nullptr; // start game
	SDL_Texture* texture_R = nullptr; // results
	SDL_Texture* texture_Rb = nullptr; // results button
	SDL_Texture* texture_M = nullptr; // menu
	SDL_Texture* texture_Q = nullptr; // quit
	SDL_Texture* texture_Qg = nullptr; // quit during game mode
	SDL_Texture* texture_time = nullptr; // timer
	SDL_Texture* texture_score = nullptr; // score

	Menu(SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height);
	~Menu();
	void show_game_menu(SDL_Window* window, SDL_Renderer* renderer);
	void show_main_menu(SDL_Renderer* renderer);

	void main_menu_loop(bool& quit, SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height);
	void init_game_objects(SDL_Renderer* renderer, int window_width, int window_height);
	void start_game(bool& quit, SDL_Event& event, SDL_Window* window, SDL_Renderer* renderer, int window_width, int window_height); // gaming loop

	void save_result(bool& quit, SDL_Event& event, SDL_Renderer* renderer, bool& update_results); 
	void show_results(bool& quit, SDL_Event& event, SDL_Renderer* renderer);
};