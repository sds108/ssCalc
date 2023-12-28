#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#define PI 3.14159265


int main () {
	SDL_Window *window;
	SDL_Init(SDL_INIT_EVERYTHING);
	
	window = SDL_CreateWindow(
		"ssCalc",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	std::vector<SDL_Point> v;
	
	for (int iterations = 1; iterations < 500; iterations++) { 
		v.clear();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (int x = 0; x < 640; x++) {
			v.emplace_back();
			v[v.size() - 1].x = x;
			v[v.size() - 1].y = (240 + (2*sin((PI*x + iterations) / (20)))*(100*sin((PI*x + iterations) / 50)));
		}
		SDL_RenderDrawLines(renderer, v.data(), v.size());
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	
	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}