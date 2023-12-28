#ifndef WINDOW_H_
#define WINDOW_H_

class calcWindow {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		int window_width;
		int window_height;
		
		void window_Init();
	
	public:
		// Default Constructor
		calcWindow();
		
		// Simple Constructor
		calcWindow(int width, int height);
		
		// Resize Call
		void resizeWindow(int width, int height);
		
		// Quit Call
		int quitWindow();
	
		// Window clear frame
		void clearFrame();
	
		// Window render a curve
		void renderCurve(std::vector<SDL_Point>& v);
	
		// Window present frame
		void presentFrame();
};

#endif