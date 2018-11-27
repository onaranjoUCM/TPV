#include "Paddle.h"
#include "checkML.h"
#include "Game.h"

using namespace std;

void Paddle::limpiar() {
	
}

void Paddle::expandW() {
	w = w + (w / 2);
}

void Paddle::reduceW() {
	w = w - (w / 2);
}

void Paddle::resetW() {
	w = wIni;
}

void Paddle::update() {
	if (pos.getX() > 25 - speed && pos.getX() < WIN_WIDTH - w - speed - 25) {
		pos = Vector2D(pos.getX() + speed, pos.getY());
	}
}

Vector2D Paddle::ballCollisionVector(const SDL_Rect* ballRect) {
	Vector2D collVector;
	int ballCenter = ballRect->x + (ballRect->w / 2);
	int espacio = w / 6;
	
	if (ballCenter > pos.getX() && ballCenter < pos.getX() + espacio * 1) {
		collVector = Vector2D(2, 10);
	}

	if (ballCenter > pos.getX() + (espacio * 1) && ballCenter < pos.getX() + espacio * 2) {
		collVector = Vector2D(1, 10);
	}
	
	if (ballCenter > pos.getX() + (espacio * 2) && ballCenter < pos.getX() + espacio * 3) {
		collVector = Vector2D(0, 10);
	}

	if (ballCenter > pos.getX() + (espacio * 3) && ballCenter < pos.getX() + espacio * 4) {
		collVector = Vector2D(0, 10);
	}

	if (ballCenter > pos.getX() + (espacio * 4) && ballCenter < pos.getX() + espacio * 5) {
		collVector = Vector2D(-1, 10);
	}

	if (ballCenter > pos.getX() + (espacio * 5) && ballCenter < pos.getX() + espacio * 6) {
		collVector = Vector2D(-2, 10);
	}
	
	collVector.normalize();
	return collVector;
}

void Paddle::handleEvents() {}

// Recibe y administra los eventos de teclado
void Paddle::handleEvents(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			speed = -3;
			break;
		case SDLK_RIGHT:
			speed = 3;
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			speed = 0;
			break;
		case SDLK_RIGHT:
			speed = 0;
			break;
		}
	}
}

bool Paddle::collides(const SDL_Rect* rect, Vector2D& collVector) {
	if (SDL_HasIntersection(rect, &getRect())) {
		collVector = ballCollisionVector(rect);
		return true;
	}
	return false;
}