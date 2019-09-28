#include <iostream>
#define GLEW_STATIC                     // damit GLEW statisch gelinkt werden kann
#include <GL/glew.h>
#define SDL_MAIN_HANDLED                // eigene Hauptfunktion für SDL  

#ifdef _WIN32							// nur für Windows
#include <SDL.h>
#pragma comment(lib, "SDL2.lib")                          
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#else
#include <SDL2/SDL.h>                   // Linux / MacOS  
#endif

#include "globals.h"

int main(int argc, char** argv)
{
	// Fenster initialisieren
	SDL_Window* window;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		std::cin.get();
		return 1;
	}

	uint32_t flags = SDL_WINDOW_OPENGL;								// im Fenster
	//uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;	// FullScreen

	// Fenster erzeugen
	window = SDL_CreateWindow("OpenGL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	while (true)
	{
		// Double Buffering (angezeigter Buffer tauschen)
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();
	std::cout << "Test: "  << std::endl;
	std::cin.get();

	return 0;
}