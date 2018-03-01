#include <iostream>
#include "SDL/include/SDL.h"
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib,"../SDL/libx86/SDL2main.lib")


int main(int argc, char* argv[])
{

	struct windowPos {
		char *title;
		int x;
		int y;
		int width;
		int height;
	} gameWindow;
	
	gameWindow = {
		"MyAwesomeGame V0.1", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		640,
		480};

	SDL_Window *window;
	int SDL_init(SDL_INIT_VIDEO); //no error log for this exercise
								  // SDL init returns 0 when runs ok
								  // SDL_GetError(); if not and return 1
	window = SDL_CreateWindow(
		gameWindow.title,
		gameWindow.x,
		gameWindow.y,
		gameWindow.width,
		gameWindow.height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	SDL_Renderer *ren = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
	
	SDL_Rect rectangle1;
	
	rectangle1 = { //x,y,w,h
		gameWindow.width / 2,
		gameWindow.height / 2,
		32,
		32 };

	bool flag = true;

	while (1)
	
		{
		SDL_SetRenderDrawColor(ren, 0, 121, 220, 255); //RGB and alpha
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 50, 50, 255);
		
		SDL_RenderFillRect(ren, &rectangle1);

		SDL_RenderPresent(ren);
		
		if (rectangle1.x <= gameWindow.width -32 && flag == true) {
			rectangle1.x += 5;
			if (rectangle1.x >= gameWindow.width - 32) flag = false;
		}
		
		if (flag == false){ 
			rectangle1.x -= 5;
			
				if (rectangle1.x <= 0) flag = true;
			}
			
		}

	SDL_Quit();
	return 0;
}