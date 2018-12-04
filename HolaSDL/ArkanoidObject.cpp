#include "ArkanoidObject.h"
#include "Game.h"
#include "checkML.h"
#include <fstream>

using namespace std;

void ArkanoidObject::loadFromFile(ifstream& file, Game* game) {
	int x, y, width, height;
	file >> x >> y >> width >> height;
	pos = Vector2D(x, y);
	w = width;
	h = height;
}

void ArkanoidObject::saveToFile(ofstream& outfile) {
	outfile << pos.getX() << " ";
	outfile << pos.getY() << " ";
	outfile << w << " ";
	outfile << h << endl;
}

void ArkanoidObject::limpiar() {

}

void ArkanoidObject::render() {
	SDL_Rect dstRect;
	dstRect.x = pos.getX();
	dstRect.y = pos.getY();
	dstRect.w = w;
	dstRect.h = h;
	texture->render(dstRect, SDL_FLIP_NONE);
}

void ArkanoidObject::renderFrame(int row, int col) {
	SDL_Rect dstRect;
	dstRect.x = pos.getX();
	dstRect.y = pos.getY();
	dstRect.w = w;
	dstRect.h = h;
	texture->renderFrame(dstRect, row, col);
}

void ArkanoidObject::setPos(Vector2D newPos) {
	pos = newPos;
}

SDL_Rect ArkanoidObject::getRect() {
	SDL_Rect dstRect;
	dstRect.x = pos.getX();
	dstRect.y = pos.getY();
	dstRect.w = w;
	dstRect.h = h;
	return dstRect;
}

int ArkanoidObject::getX() { return pos.getX(); }
int ArkanoidObject::getY() { return pos.getY(); }
int ArkanoidObject::getW() { return w; }
int ArkanoidObject::getH() { return h; }