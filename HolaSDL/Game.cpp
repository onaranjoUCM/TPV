#include "Game.h"
#include "Texture.h"
#include "Block.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "Reward.h"
#include "checkML.h"
#include <fstream>

Game::Game() {
	// INITIALIZE SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
		
	// TEXTURES
	textures[blocksText] = new Texture(renderer);
	textures[blocksText]->load(textureNames[blocksText], 2, 3);
	textures[rewardText] = new Texture(renderer);
	textures[rewardText]->load(textureNames[rewardText], 10, 8);
	for (int i = 2; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load(textureNames[i], 1, 1);
	}

	// GAME OBJECTS
	blocksMap = new BlocksMap(600, 300, textures[blocksText]);
	blocksMap->load(niveles[nivelActual]);
	sideWallLeft = new Wall("left", 4, 0, 20, WIN_HEIGHT, textures[sideWallText]);
	sideWallRight = new Wall("right", WIN_WIDTH - 24, 0, 20, WIN_HEIGHT, textures[sideWallText]);
	upperWall = new Wall("top", 0, 0, WIN_WIDTH, 20, textures[upperWallText]);
	paddle = new Paddle(WIN_WIDTH / 2 - textures[paddleText]->getW() / 2, WIN_HEIGHT - (WIN_HEIGHT / 10), textures[paddleText]->getW(), textures[paddleText]->getH(), textures[paddleText]);
	ball = new Ball(WIN_WIDTH / 2 - textures[ballText]->getW() / 10, WIN_HEIGHT - 100, textures[ballText]->getW() / 5, textures[ballText]->getH() / 5, ballSpeed, textures[ballText], this);
	loadList();
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
			createReward(block->getX(), block->getY());
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
	if (paddle->collides(rect, collVector)) { return true; }

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
		for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			(*it)->update();
		}
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
void Game::render() {
	SDL_RenderClear(renderer);
	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
}

// Recoge y administra todos los eventos
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		paddle->handleEvents(event);
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_s:
				exit = true;
				cout << "Escribe el nombre del fichero donde guardar la partida:" << endl;
				string filename;
				cin >> filename;
				filename = "..\\savedGames\\" + filename + ".txt";
				for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
					(*it)->saveToFile(filename);
				}
				break;
			}
		}
	}
}

void Game::pierdeVida() {
	vidas--;
	cout << "Vidas: " << vidas << endl;
}

void Game::ganaVida() {
	vidas++;
	cout << "Vidas: " << vidas << endl;
}

void Game::nextLevel() {
	if (nivelActual < 2) {
		ball = new Ball(WIN_WIDTH / 2 - textures[4]->getW() / 10, WIN_HEIGHT - 100, textures[4]->getW() / 5, textures[4]->getH() / 5, ballSpeed, textures[4], this);
		nivelActual++;
		blocksMap->load(niveles[nivelActual]);
	}
	else {
		win = true;
		cout << "Has ganado!";
	}
}

void Game::loadList() {
	objects.push_back(blocksMap);
	objects.push_back(paddle);
	objects.push_back(ball);
	objects.push_back(sideWallLeft);
	objects.push_back(sideWallRight);
	objects.push_back(upperWall);
}
/*
void Game::saveGame() {
	int code = readCode();
	...
	ofstream file;
	for (auto o in objects) {
		o->saveToFile(file);
	}
	file.close();
}

void Game::loadNextLevel() {
	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete *it;
		it = objects.erase(it);
	}
	firstReward = objects.end();
}
*/
void Game::createReward(int x, int y) {
	int random = rand() % 4;
	list<ArkanoidObject*>::iterator it = objects.end();
	Reward* r = new Reward(x, y, 50, 20, rewardTypes[random], Vector2D(0, 2), textures[rewardText], paddle, this, it);
	objects.push_back(r);
	/*
	auto itFR = objects.end();
	if (firstReward == objects.end()) {
		firstReward = itFR;
	}
	*/
}

void Game::killObject(list<ArkanoidObject*>::iterator it) {
	//if (it = firstReward) firstRewardH;
	//delete *it;
	//objects.erase(it);
}

void Game::saveToFile() {
	ifstream file;
	file.open(saveFileName.c_str());
}

void Game::deleteReward(Reward* r) {
	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) == r) {
			objects.erase(it);
			break;
		}
	}
	delete r;
}