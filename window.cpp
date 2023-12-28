#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "window.h"
#include <cstring>

#define PI 3.14159265

// Default Constructor
calcWindow::calcWindow () {
	window_width = 640;
	window_height = 480;
	
	window_Init();
}

// Simple Constructor
calcWindow::calcWindow (int width, int height) {
	window_width = width;
	window_height = height;
	
	window_Init();
}

// Resize Call
void calcWindow::resizeWindow (int width, int height) {
	window_width = width;
	window_height = height;
	
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	
	window_Init();
}

// Quit Call
int calcWindow::quitWindow () {
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	
	if (renderer == NULL && window == NULL) return 1;
	else return 0;
}

void calcWindow::window_Init () {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	window = SDL_CreateWindow(
		"ssCalc",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_OPENGL
	);
	
	renderer = SDL_CreateRenderer(window, -1, 0);
}

// Window clear frame
void calcWindow::clearFrame () {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

// Window render a curve
void calcWindow::renderCurve (std::vector<SDL_Point>& v) {
	SDL_RenderDrawLines(renderer, v.data(), v.size());
}

// Window present frame
void calcWindow::presentFrame () {
	SDL_RenderPresent(renderer);
}