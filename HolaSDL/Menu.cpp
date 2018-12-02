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
	//TITLE
	titleRect.x = 100;
	titleRect.y = 100;
	titleRect.w = 600;
	titleRect.h = 200;
	titleText = new Texture(renderer);
	titleText->load("..\\images\\title.png", 1, 1);

	// play button
	playButtonRect.x = 350;
	playButtonRect.y = 425; // de 400 a 450
	playButtonRect.w = 100;
	playButtonRect.h = 50;
	playButtonText = new Texture(renderer);
	playButtonText->load("..\\images\\bricks.png", 2, 3);

	// load button
	loadButtonRect.x = 350;
	loadButtonRect.y = 525; // de 500 a 550
	loadButtonRect.w = 100;
	loadButtonRect.h = 50;
	loadButtonText = new Texture(renderer);
	loadButtonText->load("..\\images\\bricks.png", 2, 3);

	// end button
	endButtonRect.x = 350;
	endButtonRect.y = 325; // de 300 a 350
	endButtonRect.w = 100;
	endButtonRect.h = 50;
	endButtonText = new Texture(renderer);
	endButtonText->load("..\\images\\bricks.png", 2, 3);
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

// Ejecuci�n del juego
void Menu::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

// M�todos que ocurren en cada frame
void Menu::update() {} //NOTA = PREGUNTAR SI BORRAR METODO

// Muestra todos los objetos en pantalla
void Menu::render() {
	SDL_RenderClear(renderer);
	titleText->render(titleRect, SDL_FLIP_NONE);
	playButtonText->renderFrame(playButtonRect, 0, 0); //ROJO = JUGAR
	loadButtonText->renderFrame(loadButtonRect, 0, 1); //AZUL = CARGAR
	endButtonText->renderFrame(endButtonRect, 0, 2); //VERDE = SALIR
	SDL_RenderPresent(renderer);
}

// Recoge y administra todos los eventos
void Menu::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;

		if (event.type == SDL_KEYDOWN) {
			Game game = Game();
			string loadCode;
			switch (event.key.keysym.sym)
			{
			case SDLK_p:
				game.run();
				break;
			case SDLK_l:
				cin >> loadCode;
				cout << "Introducido el c�digo: " << loadCode;
				break;
			case SDLK_e:
				exit = true;
				cout << "Se ha terminado el juego";
				break;
			}
			/*Game game = Game();
			game.run();
			exit = true;*/
		}
		// NOTA: revisar si sirve el loadGame
		/*if (event.button.button == SDL_BUTTON_LEFT)
		{
			int x = event.button.x;
			int y = event.button.y;

			if ((x > 350) && (x < 450) && (y > 400) && (y < 450))
			{
				Game game = Game();
				game.run();
				exit = true;
			}

			if ((x > 350) && (x < 450) && (y > 500) && (y < 550))
			{
				string loadCode;
				cin >> loadCode;
				cout << "Introducido el c�digo: " << loadCode;
				// Cargar nivel delde el archivo loadCode
			}
		}*/
	}
}
