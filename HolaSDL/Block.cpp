#include "Block.h"
#include "checkML.h"

using namespace std;

void Block::update() { }

void Block::handleEvents() { }

void Block::limpiar() {
	color = row = col = 0;
}

// Renderiza el bloque con un fragmento de la textura dependiendo del color
void Block::render() {
	int row, col;
	switch (color) {
	case 1:
		row = 0;
		col = 0;
		break;
	case 2:
		row = 0;
		col = 1;
		break;
	case 3:
		row = 0;
		col = 2;
		break;
	case 4:
		row = 1;
		col = 0;
		break;
	case 5:
		row = 1;
		col = 1;
		break;
	case 6:
		row = 1;
		col = 2;
		break;
	}

	SDL_Rect dstRect;
	dstRect.x = pos.getX();
	dstRect.y = pos.getY();
	dstRect.w = w;
	dstRect.h = h;
	texture->renderFrame(dstRect, row, col);
}

void Block::setColor(int c) {
	color = c;
}

// Getters
int Block::getR() { return row; }
int Block::getC() { return col; }
int Block::getColor() { return color; }