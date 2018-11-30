#include "MovingObject.h"
#include "checkML.h"
#include <fstream>

using namespace std;

void MovingObject::loadFromFile() {

}

void MovingObject::saveToFile(ofstream& outfile) {
	outfile << "M ";
	outfile << vel.getX() << " ";
	outfile << vel.getY() << " ";
	outfile << pos.getX() << " ";
	outfile << pos.getY() << " ";
	outfile << w << " ";
	outfile << h << endl;
}

Vector2D MovingObject::getVel() { return vel; }
void MovingObject::setVel(Vector2D newVel) {
	vel = newVel;
}