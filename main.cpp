#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#pragma comment(lib,"../SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib,"../SDL/libx86/SDL2main.lib")
#define windowWidth 640
#define windowHeight 480

//void shot(SDL_Renderer *, SDL_Rect *, SDL_Rect*);

int main(int argc, char* argv[])
{

	IMG_Init(IMG_INIT_PNG);


	struct windowPos {
		char *title;
		int x;
		int y;
		int width;
		int height;
	} gameWindow;
	
	gameWindow = {
		"MyAwesomeGame V0.2", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		windowWidth,
		windowHeight};

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
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE// | SDL_WINDOW_SHOWN
	);

	SDL_Renderer *ren = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
	
	SDL_Rect rectangle1;
	SDL_Rect bullet;
	
	rectangle1 = { //x,y,w,h
		gameWindow.width / 2,
		gameWindow.height / 2,
		32,
		32 
	};

	bullet = {
		rectangle1.x,
		rectangle1.y,
		60,
		10 };
	int maxBullets = 10;
	int currentBullets;

	/*class bullet {
		SDL_Rect bu;
		int speedX;
		int maxBullets;
		bool alive;
	public:
		bullet();
	};*/

	int rect1_xvel = 0;
	int rect1_yvel = 0;

	bool upPressed = false;
	bool downPressed = false;
	bool rightPressed = false;
	bool leftPressed = false;

	int playerSpeed = 5;
	int bulletSpeed = 30;
	bool spaceShot = false;

	while (1)
	
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
					SDL_Quit();
					return 0;
				}
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						SDL_Quit();
						return 0;
					case SDLK_UP:
						upPressed = true;
						break;
					case SDLK_DOWN:
						downPressed = true;
						break;
					case SDLK_RIGHT:
						rightPressed = true;
						break;
					case SDLK_LEFT:
						leftPressed = true;
						break;
					case SDLK_SPACE:
						//if (spaceShot == false) { //cadence, only 1 shot at time
							bullet.x = rectangle1.x + rectangle1.w; //update shot position
							bullet.y = rectangle1.y + rectangle1.h / 2 - (bullet.h / 2); //
							spaceShot = true;
							break;
						//}
					default:
						break;
					}
			}

			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						upPressed = false;
						break;
					case SDLK_DOWN:
						downPressed = false;
						break;
					case SDLK_RIGHT:
						rightPressed = false;
						break;
					case SDLK_LEFT:
						leftPressed = false;
						break;
					//case SDLK_SPACE:
						//spaceShot = false;

					}
				}
			}

			//////////////////////////playerMove and "collisions"////////////////////////////
			//up mov and collision
			if (upPressed) {
				if (rectangle1.y > 0)  rect1_yvel = playerSpeed * -1;
				else rect1_yvel = 0;
			}
			else if (upPressed == false && rect1_yvel < 0) rect1_yvel = 0;
			//down mov and collision
			if (downPressed) {
				if (rectangle1.y < gameWindow.height - rectangle1.w ) rect1_yvel = playerSpeed;
				else rect1_yvel = 0;
			}
			else if (downPressed == false && rect1_yvel > 0) rect1_yvel = 0;
			//simultaneous up and down pulsation
			if (downPressed && upPressed) rect1_yvel = 0;
			//right mov and collision
			if (rightPressed) {
				if (rectangle1.x <= gameWindow.width - rectangle1.w) {
					rect1_xvel = playerSpeed;
				}
				else rect1_xvel = 0;
			}
			else if (rightPressed == false && rect1_xvel > 0) rect1_xvel = 0;
			//left move and collision
			if (leftPressed) {
				if (rectangle1.x > 0) rect1_xvel = playerSpeed * -1; // ?
				else rect1_xvel = 0;
			}
			else if (leftPressed == false && rect1_xvel < 0) rect1_xvel = 0;
			//simultaneous left and right pulsation
			if (rightPressed && leftPressed) rect1_xvel = 0;
			///////////////////////////////////////////////////////////////////////////////
		rectangle1.y += rect1_yvel;
		rectangle1.x += rect1_xvel;

		SDL_SetRenderDrawColor(ren, 0, 121, 220, 255); //RGB and alpha background
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 50, 50, 255); //rec player
		SDL_RenderFillRect(ren, &rectangle1);
		
		SDL_SetRenderDrawColor(ren, 50, 190, 35, 255); //bullet
		//SDL_RenderFillRect(ren, &bullet);
		
		if (spaceShot) { //show and move
			SDL_RenderFillRect(ren, &bullet);
			bullet.x += bulletSpeed;
		}
		
		SDL_RenderPresent(ren);
			
		}

	SDL_Quit();
	return 0;
}

/*void shot(SDL_Renderer *renderer, SDL_Rect *bullet, SDL_Rect rect1)
{
	//SDL_Rect rect = rect1;
	bullet = {
		rect1.x,
		rect1.y,
		rect1.w / 2,
		rect1.h / 2

	};
		SDL_SetRenderDrawColor(renderer, 50, 190, 35, 255);
		SDL_RenderFillRect(renderer, bullet);
		SDL_RenderPresent(renderer);
	
}*/