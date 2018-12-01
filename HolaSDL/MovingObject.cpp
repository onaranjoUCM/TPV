#include "MovingObject.h"
#include "checkML.h"
#include <fstream>

using namespace std;

void MovingObject::loadFromFile() {

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