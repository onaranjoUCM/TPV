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


	// play button
	playButtonRect.x = 350;
	playButtonRect.y = 325;
	playButtonRect.w = 100;
	playButtonRect.h = 50;
	playButtonText = new Texture(renderer);
	playButtonText->load("..\\images\\buttons.png", 2, 3);

	// load button
	loadButtonRect.x = 350;
	loadButtonRect.y = 425;
	loadButtonRect.w = 100;
	loadButtonRect.h = 50;
	loadButtonText = new Texture(renderer);
	loadButtonText->load("..\\images\\buttons.png", 2, 3);

	// end button
	endButtonRect.x = 350;
	endButtonRect.y = 525;
	endButtonRect.w = 100;
	endButtonRect.h = 50;
	endButtonText = new Texture(renderer);
	endButtonText->load("..\\images\\buttons.png", 2, 3);
}

Menu::~Menu() {
	// destruye los punteros
	window = nullptr;
	renderer = nullptr;
	playButtonText = nullptr;
	endButtonText = nullptr;
	loadButtonText = nullptr;
	titleText = nullptr;
}

// Ejecución del juego
void Menu::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

// Métodos que ocurren en cada frame
void Menu::update() {} //NOTA = PREGUNTAR SI BORRAR METODO

// Muestra todos los objetos en pantalla
void Menu::render() {
	SDL_RenderClear(renderer);
	titleText->render(titleRect, SDL_FLIP_NONE);
	playButtonText->renderFrame(playButtonRect, 0, 2); //ROJO = JUGAR
	loadButtonText->renderFrame(loadButtonRect, 0, 0); //AZUL = CARGAR
	endButtonText->renderFrame(endButtonRect, 0, 1); //VERDE = SALIR
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

			if ((x > 350) && (x < 450) && (y > 325) && (y < 375)) // play button
			{
				Game game = Game();
				game.run();
				exit = true;
			}

			if ((x > 350) && (x < 450) && (y > 425) && (y < 475)) // load button
			{
				string loadCode;
				cout << "Introduzca el codigo del fichero de guardado: " << loadCode;
				cin >> loadCode;
				loadCode = "..\\savedGames\\" + loadCode + ".txt";
				Game game = Game(loadCode);
				game.run();
				exit = true;
			}

			if ((x > 350) && (x < 450) && (y > 525) && (y < 575)) // exit button
			{
				cout << "Juego terminado.";
				exit = true;
			}
		}
	}
}