#include "SDL_image.h"
#include "Texture.h"
#include "Texture.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "checkML.h"
#include <list>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 5;
const int FRAME_RATE = 10;

/*
const TextureAtributes textureAtribs[NUM_TEXTURES] = {
	{"ball.png", 1, 1}, {"bricks.png", 2, 3}, ... 
}
*/
/*

void render() {
	for (ArkanoidObject o in objects) {
		o->render();
	}
}

// Hay que usar static_cast de ArkanoidObject a BlocksMap para poder llamar a HitsBlock
// Todas las destructoras deberían ser virtuales
*/

class Game {
private:
	list<ArkanoidObject*> objects;
	const enum textureName { blocksText, sideWallText, upperWallText, paddleText, ballText };
	Texture* textures[NUM_TEXTURES];
	const string textureNames[NUM_TEXTURES] = { "..\\images\\bricks.png", "..\\images\\side.png", "..\\images\\topside.png", "..\\images\\paddle.png", "..\\images\\ball.png" };

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Wall* sideWallLeft = nullptr;
	Wall* sideWallRight = nullptr;
	Wall* upperWall = nullptr;
	BlocksMap* blocksMap = nullptr;
	Paddle* paddle = nullptr;
	Ball* ball = nullptr;

	bool exit = false;
	bool gameOver = false;
	bool win = false;
	int vidas = 3;
	int nivelActual = 0;
	Vector2D ballSpeed = Vector2D(1, -1);
	string niveles[3] = { "..\\maps\\level01.ark", "..\\maps\\level02.ark", "..\\maps\\level03.ark" };
public:
	Game();
	~Game();
	void run();
	bool collides(const SDL_Rect* rect, const Vector2D* vel, Vector2D& collVector);
	void render() const;
	void handleEvents();
	void update();
	void pierdeVida();
	void nextLevel();
};