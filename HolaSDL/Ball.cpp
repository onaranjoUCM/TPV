#include "Ball.h"
#include "Game.h"
#include "checkML.h"

using namespace std;

void Ball::limpiar() {
	Game* game = nullptr;
}

// Actualiza la posición de la bola según su velocidad y si ha chocado con algo
void Ball::update() {
	Vector2D prevPos = pos;
	Vector2D vel = getVel();

	setPos(pos + getVel());

	Vector2D collVector;
	if (game->collides(&getRect(), &vel, collVector)) {
		vel = vel - (collVector * (2 * (vel * collVector)));
		setVel(vel);
		setPos(prevPos + getVel());
	}

	if (pos.getY() > WIN_HEIGHT + 100) {
		pos = posIni;
		setVel(velIni);
		game->pierdeVida();
	}
}

void Ball::handleEvents() { }