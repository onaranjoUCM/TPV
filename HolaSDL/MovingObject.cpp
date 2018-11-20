#include "MovingObject.h"
#include "checkML.h"

using namespace std;

void MovingObject::loadFromFile() {

}

void MovingObject::saveToFile() {

}

Vector2D MovingObject::getVel() { return vel; }
void MovingObject::setVel(Vector2D newVel) {
	vel = newVel;
}