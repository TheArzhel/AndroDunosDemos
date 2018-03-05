#include "SDL/include/SDL.h"
#include <stdio.h>
using namespace std;
#pragma comment (lib,"SDL/libx86/SDL2.lib")
#pragma comment (lib,"SDL/libx86/SDL2main.lib")

enum KeyPress { KEY_PRESS_SURFACE_SPACE, KEY_PRESS_SURFACE_UP, KEY_PRESS_SURFACE_DOWN, KEY_PRESS_SURFACE_LEFT, KEY_PRESS_SURFACE_RIGHT, KEY_PRESS_SURFACE_ESC };

void movesquare(int keypressed, SDL_Rect* square) {
	int movement = 10;

	switch (keypressed) {


	case KEY_PRESS_SURFACE_UP:
		if (square->y != 0) {
			square->y -= movement;

		};
		break;

	case KEY_PRESS_SURFACE_DOWN:
		if (square->y != 900) {
			square->y += movement;

		}
		break;

	case KEY_PRESS_SURFACE_RIGHT:
		if (square->x != 900) {
			square->x += movement;

		};
		break;

	case KEY_PRESS_SURFACE_LEFT:
		if (square->x != 0) {
			square->x -= movement;

		}
		break;
	}


}

void createlaser(SDL_Rect* laser, SDL_Rect square) {

	laser->h = 20;
	laser->w = 100;
	laser->x = square.x + square.w;
	laser->y = square.y + square.h / 2 - laser->h / 2;


}
void movelaser(SDL_Rect* laser, SDL_Renderer* render) {
	laser->x++;

	SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	SDL_RenderFillRect(render, laser);


}
int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_VIDEO); //initialize the library and video functions abailable
	SDL_Window* window; // to create a window, first make a ponter, then we specify
	SDL_Renderer* render; // pointer to render

	window = SDL_CreateWindow("red square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN); // name, position x, y, size, windows flag
	render = SDL_CreateRenderer(window, -1, 0); // contex for a window
												//check window


	if (window == NULL) {

		return 1;
	}



	SDL_Rect square, laser;// square def
	square.x = 500;
	square.y = 500;
	square.h = 100;
	square.w = 100;


	bool quit = false;
	SDL_Event event;

	while (quit == false) {

		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {

				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

				{
					if (currentKeyStates[SDL_SCANCODE_SPACE]) {
						createlaser(&laser, square);
					}
					if (currentKeyStates[SDL_SCANCODE_UP]) {
						movesquare(KEY_PRESS_SURFACE_UP, &square);
					}
					if (currentKeyStates[SDL_SCANCODE_DOWN]) {
						movesquare(KEY_PRESS_SURFACE_DOWN, &square);
					}
					if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
						movesquare(KEY_PRESS_SURFACE_RIGHT, &square);
					}
					if (currentKeyStates[SDL_SCANCODE_LEFT]) {
						movesquare(KEY_PRESS_SURFACE_LEFT, &square);
					}
					if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
						quit = true;
					}



				}


			}
		}


		SDL_SetRenderDrawColor(render, 0, 100, 136, 256);//set the color
		SDL_RenderClear(render);//implement the color

		SDL_RenderDrawRect(render, &square); //draw square
		SDL_SetRenderDrawColor(render, 255, 0, 0, 256);//set the color of rectagle
		SDL_RenderFillRect(render, &square); // square fill
		movelaser(&laser, render);
		SDL_RenderPresent(render); //update the window
		SDL_Delay(6);
	}

	SDL_Delay(3000); //waiting  10 sec to next execution
	SDL_DestroyWindow(window);

	SDL_Quit(); // cleans the surfaces to avoid memory leaks
	return 0;
}
