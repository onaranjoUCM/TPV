#include "Wall.h"
#include "checkML.h"

using namespace std;

void Wall::update() { }

void Wall::handleEvents() { }

bool Wall::collides(const SDL_Rect* rect, Vector2D& collVector) {
	if (SDL_HasIntersection(rect, &getRect())) {
		if (wallPosition == "left") { collVector = Vector2D(1, 0); }
		if (wallPosition == "right") { collVector = Vector2D(-1, 0); }
		if (wallPosition == "top") { collVector = Vector2D(0, -1); }
		return true;
	} else {
		return false;
	}
}