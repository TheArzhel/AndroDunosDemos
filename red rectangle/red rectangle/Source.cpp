#include "SDL/include/SDL.h"
#include <stdio.h>
using namespace std;
#pragma comment (lib,"SDL/libx86/SDL2.lib")
#pragma comment (lib,"SDL/libx86/SDL2main.lib")

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


	SDL_Rect square; // square def
	square.x = 500;
	square.y = 500;
	square.h = 100;
	square.w = 100;
	
	int i = 0;
	int xsq = 0; // if goes to right
	int ysq = 0; // goes up
	
	while (i == 0) {

		SDL_SetRenderDrawColor(render, 0, 100, 136, 256);//set the color
		SDL_RenderClear(render);//implement the color

		if (square.x == 1000) { xsq = 1; }
		if (square.y == 1000) { ysq = 1; }

		if (square.x == 0) { xsq = 0; }
		if (square.y == 0) { ysq = 0; }

		if (square.x < 1000 && xsq == 0) { //right mov
			square.x++;
		}
		if (square.x > 0 && xsq == 1) { // left movement
				square.x--;
		}

		if (square.y < 1000 && ysq == 0) { //up mov
			square.y++;
		}
		if (square.y > 0 && ysq == 1) { // down movement
			square.y--;
		}
		SDL_RenderDrawRect(render, &square); //draw square
		SDL_SetRenderDrawColor(render, 255, 0, 0, 256);//set the color of rectagle
		SDL_RenderFillRect(render, &square); // square fill

		SDL_RenderPresent(render); //update the window
		SDL_Delay(6);
	}
	SDL_Delay(3000); //waiting  10 sec to next execution
	SDL_DestroyWindow(window);

	SDL_Quit(); // cleans the surfaces to avoid memory leaks
	return 0;
}
