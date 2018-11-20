#include "Game.h"
#include "Texture.h"
#include "Block.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "checkML.h"

Game::Game() {
	// INITIALIZE SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
		
	// TEXTURES
	textures[0] = new Texture(renderer);
	textures[0]->load(textureNames[0], 2, 3);
	for (int i = 1; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load(textureNames[i], 1, 1);
	}

	// GAME OBJECTS
	blocksMap = new BlocksMap(600, 300, textures[blocksText]);
	blocksMap->load(niveles[nivelActual]);
	sideWallLeft = new Wall("left", 4, 0, 20, WIN_HEIGHT, textures[sideWallText]);
	sideWallRight = new Wall("right", WIN_WIDTH - 24, 0, 20, WIN_HEIGHT, textures[sideWallText]);
	upperWall = new Wall("top", 0, 0, WIN_WIDTH, 20, textures[upperWallText]);
	paddle = new Paddle(WIN_WIDTH / 2 - textures[3]->getW() / 2, WIN_HEIGHT - (WIN_HEIGHT / 10), textures[3]->getW(), textures[3]->getH(), textures[paddleText]);
	ball = new Ball(WIN_WIDTH / 2 - textures[4]->getW() / 10, WIN_HEIGHT - 100, textures[4]->getW() / 5, textures[4]->getH() / 5, ballSpeed, textures[ballText], this);
}

Game::~Game() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	delete sideWallLeft;
	sideWallLeft = nullptr;
	delete sideWallRight;
	sideWallRight = nullptr;
	delete upperWall;
	upperWall = nullptr;
	delete blocksMap;
	blocksMap = nullptr;
	delete paddle;
	paddle = nullptr;
	delete ball;
	ball = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();
}

// Comprueba si el objeto pasado por parámetro colisiona con otro objeto del juego
bool Game::collides(const SDL_Rect* rect, const Vector2D* vel, Vector2D& collVector) {
	// BlocksMap
	if (SDL_HasIntersection(rect, &blocksMap->getRect())) {
		Block* block = blocksMap->collides(rect, vel, collVector);
		if (block != nullptr) {
			blocksMap->ballHitsBlock(block);
			if (blocksMap->getNumBlocks() == 0) {
				nextLevel();
			}
		}
		return true;
	}

	// Walls
	if (sideWallLeft->collides(rect, collVector)) { return true; }
	if (sideWallRight->collides(rect, collVector)) { return true; }
	if (upperWall->collides(rect, collVector)) { return true; }

	// Paddle
	if (SDL_HasIntersection(rect, &paddle->getRect())) {
		collVector = paddle->ballCollisionVector(rect);
		return true;
	}

	return false;
	
}

// Ejecución del juego
void Game::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

// Métodos que ocurren en caada frame
void Game::update() {
	int startTime = SDL_GetTicks();
	if (win == false && gameOver == false) {
		paddle->update();
		ball->update();
	}

	if (vidas == 0 && !gameOver) {
		cout << "Has perdido!" << endl;
		gameOver = true;
	}
	int frameTime = SDL_GetTicks() - startTime;
	if (frameTime < FRAME_RATE) {
		SDL_Delay(FRAME_RATE - frameTime);
	}
}

// Muestra todos los objetos en pantaalla
void Game::render() const {
	SDL_RenderClear(renderer);
	sideWallLeft->render();
	sideWallRight->render();
	upperWall->render();
	paddle->render();
	ball->render();
	blocksMap->render();
	SDL_RenderPresent(renderer);
}

// Recoge y administra todos los eventos
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		paddle->handleEvents(event);
	}
}

void Game::pierdeVida() {
	vidas--;
	cout << "Vidas: " << vidas << endl;
}

void Game::nextLevel() {
	if (nivelActual < 2) {
		ball = new Ball(WIN_WIDTH / 2 - textures[4]->getW() / 10, WIN_HEIGHT - 100, textures[4]->getW() / 5, textures[4]->getH() / 5, Vector2D(0.05, -0.05), textures[4], this);
		nivelActual++;
		blocksMap->load(niveles[nivelActual]);
	}
	else {
		win = true;
		cout << "Has ganado!";
	}
}