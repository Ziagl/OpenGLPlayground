#include <iostream>
#define GLEW_STATIC                     // damit GLEW statisch gelinkt werden kann
#include <GL/glew.h>
#define SDL_MAIN_HANDLED                // eigene Hauptfunktion für SDL  

#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#ifdef _WIN32							// nur für Windows
	#include <SDL.h>
	#pragma comment(lib, "SDL2.lib")                          
	#pragma comment(lib, "glew32s.lib")
	#pragma comment(lib, "opengl32.lib")
#else
	#include <SDL2/SDL.h>                   // Linux / MacOS  
#endif

// im Debug Build gibt es bessere OpenGL Fehlermeldungen
#ifdef _DEBUG
	void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cout << "[OpenGL Error] " << message << std::endl;
	}

	void _GLGetError(const char* file, int line, const char* call) {
		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL Error] " << glewGetErrorString(error) << " in " << file << ":" << line << " Call: " << call << std::endl;
		}
	}
	#define GLCALL(call) call; _GLGetError(__FILE__, __LINE__, #call)
#else
	#define GLCALL(call) call
#endif

#include "globals.h"
#include "SimpleMesh.h"
#include "Origin.h"
#include "Grid.h"
#include "FloatingCamera.h"

int main(int argc, char** argv)
{
	// Fenster initialisieren
	SDL_Window* window;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		std::cin.get();
		return 1;
	}

	// OpenGL initialisieren
	// Frame Buffer definieren
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);		// 8 bit für rot
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);		// 8 bit für grün
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);		// 8 bit für blau
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);		// 8 bit für alpha
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	// 32 bit für Pixel (optional)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	// Double Buffering aktivieren
	SDL_GL_SetSwapInterval(1);						// V-Sync

	uint32_t flags = SDL_WINDOW_OPENGL;								// im Fenster
	//uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;	// FullScreen

	// Fenster erzeugen
	window = SDL_CreateWindow("OpenGL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	// GLEW initialisieren (Context muss bereits existieren)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "glewInit Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return 2;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openGLDebugCallback, 0);
#endif

	// Models
	SimpleMesh triangle;
	Origin origin;
	Grid grid;

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.1f));

	// Camera
	FloatingCamera camera(90.0f, 800.0f, 600.0f);
	camera.translate(glm::vec3(0.0f, 1.0f, 5.0f));
	camera.update();

	glm::mat4 modelViewProj = camera.getViewProj() * model;

	// FPS timer
	uint64_t perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastCounter = SDL_GetPerformanceCounter();
	float delta = 0.0f;

	bool buttonW = false;
	bool buttonS = false;
	bool buttonA = false;
	bool buttonD = false;
	bool buttonSpace = false;
	bool buttonShift = false;

	float cameraSpeed = 2.0f;
	float time = 0.0f;

	// Game Loop
	bool close = false;
	while (!close)
	{
		// Buffer leeren
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		time += delta;

		// move Camera
		if (buttonW) {
			camera.moveFront(delta * cameraSpeed);
		}
		if (buttonS) {
			camera.moveFront(-delta * cameraSpeed);
		}if (buttonA) {
			camera.moveSideways(-delta * cameraSpeed);
		}if (buttonD) {
			camera.moveSideways(delta * cameraSpeed);
		}if (buttonSpace) {
			camera.moveUp(delta * cameraSpeed);
		}if (buttonShift) {
			camera.moveUp(-delta * cameraSpeed);
		}

		camera.update();
		//model = glm::rotate(model, 1.0f * delta, glm::vec3(0, 1, 0));
		modelViewProj = camera.getViewProj() * model;
		glm::mat4 modelView = camera.getView() * model;
		glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));
		
		grid.render(modelViewProj);
		//origin.render(modelViewProj);
		triangle.render(modelViewProj);

		// Double Buffering (angezeigter Buffer tauschen)
		SDL_GL_SwapWindow(window);

		// FPS update
		uint64_t endCounter = SDL_GetPerformanceCounter();
		uint64_t counterElapsed = endCounter - lastCounter;
		delta = ((float)counterElapsed) / (float)perfCounterFrequency;
		uint32_t FPS = (uint32_t)((float)perfCounterFrequency / (float)counterElapsed);
		lastCounter = endCounter;

		// Input abfragen
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					buttonW = true;
					break;
				case SDLK_s:
					buttonS = true;
					break;
				case SDLK_a:
					buttonA = true;
					break;
				case SDLK_d:
					buttonD = true;
					break;
				case SDLK_SPACE:
					buttonSpace = true;
					break;
				case SDLK_LSHIFT:
					buttonShift = true;
					break;
				case SDLK_ESCAPE:
					SDL_SetRelativeMouseMode(SDL_FALSE);
					break;
				}
			}
			else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					buttonW = false;
					break;
				case SDLK_s:
					buttonS = false;
					break;
				case SDLK_a:
					buttonA = false;
					break;
				case SDLK_d:
					buttonD = false;
					break;
				case SDLK_SPACE:
					buttonSpace = false;
					break;
				case SDLK_LSHIFT:
					buttonShift = false;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION) {
				if (SDL_GetRelativeMouseMode()) {
					camera.onMouseMoved(event.motion.xrel, event.motion.yrel);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						close = true;
						break;
				}
			}	
		}
	}

	SDL_Quit();

	return 0;
}