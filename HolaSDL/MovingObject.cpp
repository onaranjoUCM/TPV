#include "MovingObject.h"
#include "Game.h"
#include "checkML.h"
#include <fstream>

using namespace std;

void MovingObject::loadFromFile(ifstream& file, Game* game) {
	int vx, vy;
	file >> vx >> vy;
	vel = Vector2D(vx, vy);
	ArkanoidObject::loadFromFile(file, game);
}

void MovingObject::saveToFile(ofstream& outfile) {
	outfile << vel.getX() << " ";
	outfile << vel.getY() << " ";
	ArkanoidObject::saveToFile(outfile);
}

Vector2D MovingObject::getVel() { return vel; }
void MovingObject::setVel(Vector2D newVel) {
	vel = newVel;
}