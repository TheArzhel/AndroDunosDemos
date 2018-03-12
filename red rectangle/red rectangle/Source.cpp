#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"

#pragma comment (lib,"SDL/libx86/SDL2.lib")
#pragma comment (lib,"SDL/libx86/SDL2main.lib")
#pragma comment (lib,"SDL_Image/libx86/SDL2_image.lib")

SDL_Window* window; // to create a window, first make a ponter, then we specify
SDL_Renderer* render; // pointer to render
SDL_Event event;

enum KeyPress { KEY_PRESS_SURFACE_SPACE, KEY_PRESS_SURFACE_UP, KEY_PRESS_SURFACE_DOWN, KEY_PRESS_SURFACE_LEFT, KEY_PRESS_SURFACE_RIGHT, KEY_PRESS_SURFACE_ESC };


//void createlaser(SDL_Rect* laser, SDL_Rect square) {
//	
//	laser->h = 120;
//	laser->w = 120; 
//	laser->x = square.x + square.w;
//	laser->y = square.y + square.h / 2 - laser->h / 2;
//
//
//}



int main(int argc, char* argv[]) {

	//initialize the library and video functions abailable
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);


	// square def
	SDL_Rect square, laser[50];
	square.x = 500;
	square.y = 500;
	square.h = 120;
	square.w = 120;

	bool RightKey = false, LeftKey = false, UpKey = false, DownKey = false, bullet = false, quit = false;


	// constants and counters
	int c = 0;
	int movement = 5;

	// name, position x, y, size, windows flag
	window = SDL_CreateWindow("red square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1200, SDL_WINDOW_SHOWN);
	// contex for a window
	render = SDL_CreateRenderer(window, -1, 0);

	//Set the png background

	SDL_Texture* back = nullptr;
	SDL_Texture* shiptxt = nullptr;
	SDL_Texture* laserTexture = nullptr;
	SDL_Surface* Background = IMG_Load("image.png");
	SDL_Surface *Ship = IMG_Load("pokebal.png");
	SDL_Surface *Laser = IMG_Load("pokebal1.png");
	back = SDL_CreateTextureFromSurface(render, Background);
	shiptxt = SDL_CreateTextureFromSurface(render, Ship);
	laserTexture = SDL_CreateTextureFromSurface(render, Laser);

	if ((back == nullptr || shiptxt == nullptr || laser == nullptr) && window == nullptr)
	{
		return -1;
	}
	else
	{
		while (quit == false)
		{

			while (SDL_PollEvent(&event) != 0)
			{

				if (event.type == SDL_QUIT)
				{
					quit = true;
				}


				else if (event.type == SDL_KEYDOWN)
				{

					switch (event.key.keysym.sym)
					{

					case SDLK_SPACE:
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
			if (square.y != 1080 && DownKey == true) {
				square.y += movement;
			}
			if (square.x != 1800 && RightKey == true) {
				square.x += movement;
			}
			if (square.x != 0 && LeftKey == true) {
				square.x -= movement;
			}

			if (bullet == true)
			{
				/*createlaser(&laser[c], square);*/
				laser[c].x = square.x;
				laser[c].y = square.y;
				c++;
				bullet = false;
			}



			//set the image on the window, renderer.
			SDL_RenderClear(render);
			SDL_RenderCopy(render, back, NULL, NULL);


			for (int i = 0; i < 50; ++i)
			{
				laser[i].w = 120;
				laser[i].h = 120;
				laser[i].x += 10;
				//SDL_RenderFillRect(renderer, &greenRect[i]);
				if (laser[i].x < 2000)
				{
					SDL_RenderCopy(render, laserTexture, NULL, &laser[i]);
				}
			}



			//set color to rectangle
			/*SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
			SDL_RenderDrawRect(render, &square);
			SDL_RenderFillRect(render, &square);*/
			SDL_RenderCopy(render, shiptxt, NULL, &square);


			//update the window
			SDL_RenderPresent(render);

			SDL_Delay(2);

		}


		SDL_Delay(30); //waiting to next execution

		SDL_DestroyRenderer(render);
		SDL_DestroyTexture(back);
		SDL_DestroyTexture(shiptxt);
		SDL_DestroyTexture(laserTexture);

		SDL_FreeSurface(Background);
		SDL_FreeSurface(Ship);
		SDL_FreeSurface(Laser);

		SDL_DestroyWindow(window);
		SDL_Quit(); // cleans the surfaces to avoid memory leaks
		IMG_Quit();
		return 0;
	}

}

	

	

	


