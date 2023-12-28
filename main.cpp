#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
#include "window.h"

#define PI 3.14159265


int main () {
	calcWindow myWindow(640, 480);
	
	std::vector<SDL_Point> v;
	
	for (int iterations = 1; iterations < 10000000; iterations++) {
		int i = 0;
	}
	
	for (int iterations = 1; iterations < 300; iterations++) { 
		v.clear();
		
		// Clear frame
		myWindow.clearFrame();
		
		for (int x = 0; x < 640; x++) {
			v.emplace_back();
			v[v.size() - 1].x = x;
			v[v.size() - 1].y = (240 + (2*sin((PI*x + iterations) / (20)))*(100*sin((PI*x + iterations) / 50)));
		}
		
		// Render curve
		myWindow.renderCurve(v);
		
		// Present frame
		myWindow.presentFrame();
		
		SDL_Delay(10);
	}
	
	myWindow.resizeWindow(1000, 200);
	
	for (int iterations = 1; iterations < 300; iterations++) { 
		v.clear();
		
		// Clear frame
		myWindow.clearFrame();
		
		for (int x = 0; x < 1000; x++) {
			v.emplace_back();
			v[v.size() - 1].x = x;
			v[v.size() - 1].y = (240 + (2*sin((PI*x + iterations) / (20)))*(100*sin((PI*x + iterations) / 50)));
		}
		
		// Render curve
		myWindow.renderCurve(v);
		
		// Present frame
		myWindow.presentFrame();
		
		SDL_Delay(10);
	}
	
	SDL_Delay(1000);
	
	myWindow.resizeWindow(1000, 1000);
	
	SDL_Delay(1000);
	
	myWindow.resizeWindow(640, 1000);
	
	SDL_Delay(1000);
	
	myWindow.resizeWindow(1000, 1000);
	
	SDL_Delay(1000);
	
	// Clean up
	myWindow.quitWindow();
	
	SDL_Quit();
	
	return 0;
}