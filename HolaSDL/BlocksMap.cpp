#include "BlocksMap.h"
#include "Game.h"
#include <fstream>
#include "checkML.h"
#include <time.h>

using namespace std;

// Recorre el array doble de bloques y renderiza cada uno
void BlocksMap::render() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (cells[r][c] != nullptr) {
				cells[r][c]->render(); 
			}
		}
	}
}

// Crea el array doble de bloques y lo rellena según un fichero de configuración
void BlocksMap::load(const string& filename) {
	ifstream file;
	bool firstBlockFound = false;
	if (file.fail()) {
		throw "Error loading blocks map from " + filename;
	} else {
		file.open(filename);
		file >> rows;
		file >> cols;
		cells = new Block**[rows];
		for (int r = 0; r < rows; r++) {
			cells[r] = new Block*[cols];
		}

		int color;
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				file >> color;
				if (color == 0) {
					cells[r][c] = nullptr;
				}
				else {
					int margenX = (WIN_WIDTH - w) / 2;
					int posX = c * (w / cols) + margenX;
					int posY = r * (h / rows) + 50;
					cells[r][c] = new Block(posX, posY, w / cols, h / rows, r, c, color, texture);
					numBlocks++;

					// PENDIENTE DE MEJORAS
					if (!firstBlockFound) {
						firstBlockFound = true;
						setPos(Vector2D(cells[r][c]->getX(), cells[r][c]->getY()));
					}
				}
			}
		}
		file.close();
	}
}

void BlocksMap::loadFromFile(ifstream& file, Game* game) {
	ArkanoidObject::loadFromFile(file, game);
	
	load(game->getNivelActual());
	int color;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			file >> color;
			Block* block = cells[r][c];
			if (block != nullptr) {
				block->setColor(color);
				if (color == 0) {
					ballHitsBlock(block);
				}
			}
		}
	}
	this->texture = game->getTextures()[0];
}

void BlocksMap::saveToFile(ofstream& outfile) {
	ArkanoidObject::saveToFile(outfile);

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (cells[r][c] != nullptr) {
				outfile << cells[r][c]->getColor() << " ";
			} else {
				outfile << 0 << " ";
			}
		}
		outfile << endl;
	}
	outfile << endl;
}

bool BlocksMap::checkCollision(const SDL_Rect* rect, const Vector2D* vel, Vector2D& collVector, Game* game) {
	if (SDL_HasIntersection(rect, &getRect())) {
		Block* block = collides(rect, vel, collVector);
		if (block != nullptr) {
			srand(time(NULL));
			if (rand() % 5 == 0) {
				game->createReward(block->getX(), block->getY());
			}
			ballHitsBlock(block);
			if (getNumBlocks() == 0) {
				game->nextLevel();
			}
		}
		return true;
	}
}

// Comprueba en que parte del mapa se ha producido la colisión y devuelve el bloque y el vector de rebote correspondiente
Block* BlocksMap::collides(const SDL_Rect* ballRect, const Vector2D* ballVel, Vector2D& collVector) {
	Vector2D p0 = { (double)ballRect->x, (double)ballRect->y }; // top-left
	Vector2D p1 = { (double)ballRect->x + (double)ballRect->w, (double)ballRect->y }; // top-right
	Vector2D p2 = { (double)ballRect->x, (double)ballRect->y + (double)ballRect->h }; // bottom-left
	Vector2D p3 = { (double)ballRect->x + (double)ballRect->w, (double)ballRect->y + (double)ballRect->h }; // bottom-right
	Block* b = nullptr;
	if (ballVel->getX() < 0 && ballVel->getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel->getX() >= 0 && ballVel->getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel->getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel->getX() > 0 && ballVel->getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel->getX() < 0 && ballVel->getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}

// Devuelve el bloque que se encuentra en una posición determinada
Block* BlocksMap::blockAt(const Vector2D& p) {
	/*
	int r = p.getY() / (getH() / rows) - 2;
	int c = p.getX() / (getW() / cols) - 2;
	cout << r << "-" << c << " ";
	if (cells[r][c] != nullptr) {
		return cells[r][c];
	}
	*/
	// PENDIENTE DE MEJORA
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (cells[r][c] != nullptr) {
				if (p.getX() >= cells[r][c]->getX() &&
					p.getY() >= cells[r][c]->getY() &&
					p.getX() <= (cells[r][c]->getX() + cells[r][c]->getW()) &&
					p.getY() <= (cells[r][c]->getY() + cells[r][c]->getH()) 
					) {
					return cells[r][c];
				}
			}
		}
	}
	
	return nullptr;
}

// Avisa a un bloque de que la bola le ha impactado
void BlocksMap::ballHitsBlock(Block* block) {
	numBlocks--;
	cells[block->getR()][block->getC()] = nullptr;
	delete block;
}

// Devuelve el número de bloques que quedan
int BlocksMap::getNumBlocks() {
	return numBlocks;
}

int BlocksMap::getRows() {
	return rows;
}

int BlocksMap::getCols() {
	return cols;
}

Block*** BlocksMap::getCells() {
	return cells;
}

void BlocksMap::limpiar() {
	if (cells != nullptr) {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				delete cells[r][c];
			}
			delete cells[r];
		}
		delete[] cells;
		cells = nullptr;
	}
	rows = cols = 0;
}

void BlocksMap::update() { }

void BlocksMap::handleEvents() { }