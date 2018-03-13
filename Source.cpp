#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"

#pragma comment (lib,"SDL/libx86/SDL2.lib")
#pragma comment (lib,"SDL/libx86/SDL2main.lib")
#pragma comment (lib,"SDL_Image/libx86/SDL2_image.lib")
#pragma comment (lib,"SDL_Mixer/libx86/SDL2_mixer.lib")

SDL_Window* window; // to create a window, first make a ponter, then we specify
SDL_Renderer* render; // pointer to render
SDL_Event event;

enum KeyPress { KEY_PRESS_SURFACE_SPACE, KEY_PRESS_SURFACE_UP, KEY_PRESS_SURFACE_DOWN, KEY_PRESS_SURFACE_LEFT, KEY_PRESS_SURFACE_RIGHT, KEY_PRESS_SURFACE_ESC };


int main(int argc, char* argv[]) {

	//initialize the library and video functions abailable
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);

	// square def
	SDL_Rect square, laser[50];
	square.x = 0;
	square.y = 0;
	square.h = 120;
	square.w = 120;
	
	SDL_Rect pokemon;
	pokemon.x = 2000;
	pokemon.y = 750;
	pokemon.h = 123;
	pokemon.w = 111;

	bool RightKey = false, LeftKey = false, UpKey = false, DownKey = false, bullet = false, quit = false;


	// constants and counters
	int c = 0;
	int movement = 5;
	int e = 0;

	// name, position x, y, size, windows flag
	window = SDL_CreateWindow("red square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1720, 920, SDL_WINDOW_SHOWN);
	// contex for a window
	render = SDL_CreateRenderer(window, -1, 0);

	//Set the png background

	SDL_Texture* back = nullptr;
	SDL_Texture* shiptxt = nullptr;
	SDL_Texture* laserTexture = nullptr;
	SDL_Surface* Background = IMG_Load("image.png");
	SDL_Surface *Ship = IMG_Load("master_hand.png");
	SDL_Surface *Laser = IMG_Load("pokebal.png");
	back = SDL_CreateTextureFromSurface(render, Background);
	shiptxt = SDL_CreateTextureFromSurface(render, Ship);
	laserTexture = SDL_CreateTextureFromSurface(render, Laser);
	SDL_Texture* eevee = nullptr;
	SDL_Surface* Eevee = IMG_Load("eevee.png");
	eevee = SDL_CreateTextureFromSurface(render, Eevee);

	//initialize music sounds
	Mix_Music *bgm = nullptr;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	bgm = Mix_LoadMUS("fight_pokemon.ogg");
	Mix_VolumeMusic(20);
	Mix_PlayMusic(bgm, -1); 

	//Initialize wav sounds
	Mix_Chunk *shot = nullptr;
	shot = Mix_LoadWAV("throw.wav");
	Mix_VolumeChunk(shot,10);
	Mix_Chunk *capture = nullptr;
	capture = Mix_LoadWAV("capture.wav");
	Mix_VolumeChunk(capture, 10);
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
						e++;
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
			if (square.y != 800 && DownKey == true) {
				square.y += movement;
			}
			if (square.x != 1600 && RightKey == true) {
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
				if (c == 50) { c = 0; }
				Mix_PlayChannel(2, shot, 0);
				bullet = false;
			}
			
			//pokemon movement
			
			if (e == 0)
			{
				pokemon.x = 2000;
			}
			else {
				pokemon.x--;
				if (pokemon.x == -109) {
					pokemon.x = 2000;
					e = 0;
				}
			}


			//set the image on the window, renderer.
			SDL_RenderClear(render);
			SDL_RenderCopy(render, back, NULL, NULL);

			//set color to rectangle
			/*SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
			SDL_RenderDrawRect(render, &square);
			SDL_RenderFillRect(render, &square);*/ 
			SDL_RenderCopy(render, eevee, NULL, &pokemon);
			SDL_RenderCopy(render, shiptxt, NULL, &square);

			for (int i = 0; i < 50; ++i)
			{
				if (laser[i].x > pokemon.x && laser[i].x < pokemon.x+111 &&   laser[i].y > pokemon.y && laser[i].y < pokemon.y+123)
				{
					Mix_PlayChannel(3, capture, 0);
					pokemon.x = -99;
					laser[i].x = laser[i].y = 2020;
				}
				
			}
			

			for (int i = 0; i < 50; ++i)
			{
				laser[i].w = 120;
				laser[i].h = 120;
				laser[i].x += 3;
				//SDL_RenderFillRect(renderer, &greenRect[i]);
				if (laser[i].x < 1720)
				{
					SDL_RenderCopy(render, laserTexture, NULL, &laser[i]);
					
				}
			}

			


			//update the window
			SDL_RenderPresent(render);

			SDL_Delay(2);

		}


		SDL_Delay(30); //waiting to next execution

		SDL_DestroyRenderer(render);
		SDL_DestroyTexture(back);
		SDL_DestroyTexture(shiptxt);
		SDL_DestroyTexture(laserTexture);
		SDL_DestroyTexture(eevee);

		SDL_FreeSurface(Background);
		SDL_FreeSurface(Ship);
		SDL_FreeSurface(Laser);
		SDL_FreeSurface(Eevee);

		Mix_FreeMusic(bgm);

		SDL_DestroyWindow(window);
		SDL_Quit(); // cleans the surfaces to avoid memory leaks
		IMG_Quit();
		return 0;
	}

}

	

	

	


