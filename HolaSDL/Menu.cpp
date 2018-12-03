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

	playButtonRect.x = 350;
	playButtonRect.y = 400;
	playButtonRect.w = 100;
	playButtonRect.h = 50;
	playButtonText = new Texture(renderer);
	playButtonText->load("..\\images\\bricks.png", 2, 3);

	loadButtonRect.x = 350;
	loadButtonRect.y = 500;
	loadButtonRect.w = 100;
	loadButtonRect.h = 50;
	loadButtonText = new Texture(renderer);
	loadButtonText->load("..\\images\\bricks.png", 2, 3);
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
	playButtonText->renderFrame(playButtonRect, 0, 2);
	loadButtonText->renderFrame(loadButtonRect, 0, 0);
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

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			int x = event.button.x;
			int y = event.button.y;

			if ((x > 350) && (x < 450) && (y > 400) && (y < 450))
			{
				Game game = Game();
				game.run();
				exit = true;
			}

			if ((x > 350) && (x < 450) && (y > 450) && (y < 500))
			{
				cout << "Introduce el codigo del fichero de guardado: ";
				string filename;
				cin >> filename;
				filename = "..\\savedGames\\" + filename + ".txt";
				Game game = Game(filename);
				game.run();
				exit = true;
			}

			if ((x > 350) && (x < 450) && (y > 500) && (y < 550))
			{
				string loadCode;
				cin >> loadCode;
				cout << "Introducido el código: " << loadCode;
				// Cargar nivel delde el archivo loadCode
			}
		}

	}
}

