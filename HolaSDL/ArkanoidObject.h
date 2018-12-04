#ifndef ArkanoidObjectH
#define ArkanoidObjectH

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class Game;
class ArkanoidObject : public GameObject {
protected:
	Vector2D pos;
	int w, h;
	Texture* texture;
public:
	ArkanoidObject() {}
	ArkanoidObject(int x, int y, int w, int h, Texture* t) :
		pos(x, y), w(w), h(h), texture(t) {}

	~ArkanoidObject() { limpiar(); }
	void limpiar();
	virtual void loadFromFile(ifstream& file, Game* game);
	virtual void saveToFile(ofstream& outfile);
	void render();
	void renderFrame(int row, int col);

	void setPos(Vector2D newPos);

	SDL_Rect getRect();
	int getX();
	int getY();
	int getW();
	int getH();
};

#endif