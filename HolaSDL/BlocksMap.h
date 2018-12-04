#ifndef BlocksMapH
#define BlocksMapH

#include "Block.h"
#include "ArkanoidObject.h"
#include "checkML.h"

class Game;
class BlocksMap : public ArkanoidObject {
private:
	int rows = 0;
	int cols = 0;
	int numBlocks = 0;
	Block*** cells;
	string filename = "..\\maps\\level01.ark";

public:
	BlocksMap() {}
	BlocksMap(int w, int h, Texture* t) :
		ArkanoidObject(0, 0, w, h, t) {}

	~BlocksMap() {
		limpiar();
	}
	
	void update();
	void handleEvents();

	void render();
	void load(const string& filename);
	void loadFromFile(ifstream& file, Game* game);
	void saveToFile(ofstream& outfile);
	void limpiar();
	Block* collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector);
	Block* blockAt(const Vector2D& p);
	void ballHitsBlock(Block* block);
	bool checkCollision(const SDL_Rect* rect, const Vector2D* vel, Vector2D& collVector, Game* game);
	int getNumBlocks();
	int getRows();
	int getCols();
	Block*** getCells();
};

#endif