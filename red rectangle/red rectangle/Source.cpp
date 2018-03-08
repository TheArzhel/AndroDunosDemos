#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"

#pragma comment (lib,"SDL/libx86/SDL2.lib")
#pragma comment (lib,"SDL/libx86/SDL2main.lib")
#pragma comment (lib,"SDL_Image/libx86/SDL2_image.lib")

SDL_Window* window; // to create a window, first make a ponter, then we specify
SDL_Renderer* render; // pointer to render


enum KeyPress { KEY_PRESS_SURFACE_SPACE, KEY_PRESS_SURFACE_UP, KEY_PRESS_SURFACE_DOWN, KEY_PRESS_SURFACE_LEFT, KEY_PRESS_SURFACE_RIGHT, KEY_PRESS_SURFACE_ESC };


void createlaser(SDL_Rect* laser, SDL_Rect square) {
	
	laser->h = 20;
	laser->w = 100; 
	laser->x = square.x + square.w;
	laser->y = square.y + square.h / 2 - laser->h / 2;


}



int main(int argc, char* argv[]) {

	
	SDL_Init(SDL_INIT_VIDEO); //initialize the library and video functions abailable
	IMG_Init(IMG_INIT_PNG);
	
	window = SDL_CreateWindow("red square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN); // name, position x, y, size, windows flag
	render = SDL_CreateRenderer(window, -1, 0); // contex for a window
	
	//check window
	if (window == nullptr) {

		return 1;
	}



	int c = 0; // counter
	SDL_Rect square, laser[50]; // square def
	square.x = 500;
	square.y = 500;
	square.h = 100;
	square.w = 100;
	

	bool quit = false;
	bool RightKey = false, LeftKey = false, UpKey = false, DownKey = false, bullet = false;


	SDL_Event event; 
	
	int movement = 5;

	SDL_Texture* back=nullptr;
	SDL_Texture* shiptxt=nullptr;
	SDL_Surface* Background = IMG_Load("image.png");
	//SDL_Surface *Ship = IMG_Load("ae86.png");
	back = SDL_CreateTextureFromSurface(render, Background);
	//shiptxt = SDL_CreateTextureFromSurface(render, Ship);
	
	/*if (back == nullptr || shiptxt == nullptr)
	{
		return -1;
	}*/


	

	

	while (quit==false) {

		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT)
			{
				quit = true;
			} 

	
			

			else if (event.type == SDL_KEYDOWN) {

				switch (event.key.keysym.sym) {

				case SDLK_SPACE:

					createlaser(&laser[c], square);
					c++;
					bullet = true;
					

					break;

				case SDLK_UP:
					UpKey = true;
					break;

				case SDLK_DOWN:
					DownKey = true;

					break;

				case SDLK_RIGHT:
					RightKey = true;

					break;

				case SDLK_LEFT:
					LeftKey = true;

					break;

				case SDLK_ESCAPE:
					quit = true;
					break;

				default:
					break;

				}

				
				
			}

			else if (event.type = SDL_KEYUP) {

				switch (event.key.keysym.sym) {

				case SDLK_UP:
					UpKey = false;
					break;

				case SDLK_DOWN:
					DownKey = false;
					break;

				case SDLK_RIGHT:
					RightKey = false;
					break;

				case SDLK_LEFT:
					LeftKey = false;
					break;

				default:
					break;

				}
			}
		}

		if (square.y != 0 && UpKey == true) {
			square.y -= movement;
		}

		if (square.y != 900 && DownKey == true) {
			square.y += movement;
		}

		if (square.x != 900 && RightKey == true) {
			square.x += movement;
		}

		if (square.x != 0 && LeftKey == true) {
			square.x -= movement;
		}

		SDL_SetRenderDrawColor(render, 0, 100, 136, 255);//set the color
		
	
		SDL_RenderClear(render);//implement the color

		if (bullet == true) {
			for (int j = 0; j < c; j++) {
				laser[j].x+=10;
				SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
				SDL_RenderFillRect(render, &laser[j]);
			}
			
		}
		
		SDL_RenderDrawRect(render, &square); //draw square
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);//set the color of rectagle
		SDL_RenderFillRect(render, &square); // square fill
		SDL_RenderPresent(render); //update the window

		SDL_Delay(2);

	}



	SDL_Delay(30); //waiting to next execution
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit(); // cleans the surfaces to avoid memory leaks
	IMG_Quit();
	return 0;
}


