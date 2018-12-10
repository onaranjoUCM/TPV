#include "SDL_image.h"
#include "Texture.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "Reward.h"
#include "checkML.h"
#include <list>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 6;
const int FRAME_RATE = 10;

/*
const TextureAtributes textureAtribs[NUM_TEXTURES] = {
	{"ball.png", 1, 1}, {"bricks.png", 2, 3}, ... 
}

// Hay que usar static_cast de ArkanoidObject a BlocksMap para poder llamar a HitsBlock
// Todas las destructoras deberían ser virtuales
*/

class GameStateMachine; // NUEVO
class Game {
private:
	const enum textureName { blocksText, rewardText, sideWallText, upperWallText, paddleText, ballText };
	enum gameStates { menu = 0, play = 1, end = 3, pause = 4 }; //NUEVO
	Texture* textures[NUM_TEXTURES];
	const string textureNames[NUM_TEXTURES] = { "..\\images\\bricks.png", "..\\images\\rewards.png", "..\\images\\side.png", "..\\images\\topside.png", "..\\images\\paddle.png", "..\\images\\ball.png" };

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine; //NUEVO
	gameStates currentGameState; //NUEVO

	list<ArkanoidObject*> objects;
	Wall* sideWallLeft = nullptr;
	Wall* sideWallRight = nullptr;
	Wall* upperWall = nullptr;
	BlocksMap* blocksMap = nullptr;
	Paddle* paddle = nullptr;
	Ball* ball = nullptr;
	Reward* reward = nullptr;

	bool exit = false;
	bool gameOver = false;
	bool win = false;
	int vidas = 3;
	int nivelActual = 0;
	int rewardTypes[4] = {0, 1, 3, 4};
	Vector2D ballSpeed = Vector2D(2, -2);
	string niveles[3] = { "..\\maps\\level01.ark", "..\\maps\\level02.ark", "..\\maps\\level03.ark" };
public:
	Game();
	Game(string filename);
	~Game();
	void run();
	bool collides(const SDL_Rect* rect, const Vector2D* vel, Vector2D& collVector);
	void render();
	void handleEvents();
	void update();
	void pierdeVida();
	void nextLevel();
	void loadList();
	void createReward(int x, int y);
	void ganaVida();
	void deleteReward(Reward* r);
	void killObject(list<ArkanoidObject*>::iterator it);
	void saveGame();
	string getNivelActual();
	Texture** getTextures();
};