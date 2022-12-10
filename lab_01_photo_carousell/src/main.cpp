#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

const std::string IMG_DIR = "./images";
// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();
// Loads individual image
SDL_Surface* loadSurface(std::string path);
// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
// The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[11];
// Current displayed image
SDL_Surface* gCurrentSurface = NULL;
// total photos + default
const int total = 10;
// Current Position
int position = 10;
//       Images: image_.bmp | Default IMG
// index: 0 1 2 3 4 5 6 7 8 | 9  
// count: 1 2 3 4 5 6 7 8 9 | 10

bool init() {
	// Initialization flag
	bool success = true;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;
	// Load default surface
	gKeyPressSurfaces[total] = loadSurface(IMG_DIR + "/Home.bmp");
	if (gKeyPressSurfaces[total] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}
	// Load up surface
	for (int i = 0; i < total; i++) {
		gKeyPressSurfaces[i] = loadSurface(IMG_DIR + "/image" + std::to_string(i + 1) + ".bmp");
		if (gKeyPressSurfaces[i] == NULL) {
			printf("Failed to load up image!\n");
			success = false;
		}
	}
	return success;
}

void close() {
	// Deallocate surfaces
	for (int i = 0; i < total; i++) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}
	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

int main(int argc, char* args[]) {
	// Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			// Main loop flag
			bool quit = false;
			// Event handler
			SDL_Event e;
			// Set default current surface
			gCurrentSurface = gKeyPressSurfaces[10];
			// While application is running
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					// User presses a key
					else if (e.type == SDL_KEYDOWN) {
						// Select surfaces based on key press
						switch (e.key.keysym.sym) {
						case SDLK_LEFT:
							position--;
							if (position < 0)
								position = 10;
							gCurrentSurface = gKeyPressSurfaces[position];
							break;

						case SDLK_RIGHT:
							position++;
							if (position > 10)
								position = 0;
							gCurrentSurface = gKeyPressSurfaces[position];
							break;

						default:
							gCurrentSurface = gKeyPressSurfaces[10];
							break;
						}
					}
				}
				//Apply the current image
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	//Free resources and close SDL
	close();
	return (0);
}
