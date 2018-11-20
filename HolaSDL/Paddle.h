#ifndef PaddleH
#define PaddleH

#include "Texture.h"
#include "Vector2D.h"
#include "MovingObject.h"
#include "checkML.h"

class Paddle : public MovingObject {
private:
	int speed = 0;
public:
	Paddle() {}
	Paddle(int x, int y, int w, int h, Texture* t) :
		MovingObject(x, y, w, h, Vector2D(0,0), t) {}
	~Paddle() {  limpiar();  }
	void limpiar();

	void update();
	void handleEvents();
	void handleEvents(SDL_Event event);
	Vector2D ballCollisionVector(const SDL_Rect* ballRect);
};

#endif