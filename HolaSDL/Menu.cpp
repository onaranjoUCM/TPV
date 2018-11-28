#include "Menu.h"
#include "Game.h"
#include "Texture.h"
#include "checkML.h"

Menu::Menu() {
	// INITIALIZE SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";

	titleRect.x = 100;
	titleRect.y = 100;
	titleRect.w = 600;
	titleRect.h = 200;
	titleText = new Texture(renderer);
	titleText->load("..\\images\\title.png", 1, 1);
}

Menu::~Menu() {

}

// Ejecución del juego
void Menu::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

// Métodos que ocurren en caada frame
void Menu::update() {

}

// Muestra todos los objetos en pantaalla
void Menu::render() {
	SDL_RenderClear(renderer);
	titleText->render(titleRect, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}

// Recoge y administra todos los eventos
void Menu::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		if (event.type == SDL_KEYDOWN) {
			Game game = Game();
			game.run();
			exit = true;
		}
	}
}

