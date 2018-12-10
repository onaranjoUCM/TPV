#ifndef BallH
#define BallH

#include "Texture.h"
#include "Vector2D.h"
#include "MovingObject.h"
#include "checkML.h"

class Game;
class Ball : public MovingObject{
private:
	Vector2D posIni;
	Vector2D velIni;
	Game* game;
public:
	Ball() {}
	Ball(int x, int y, int w, int h, Vector2D v, Texture* t, Game* g) :
		MovingObject(x, y, w, h, v, t) {
		game = g;
		posIni = Vector2D(x, y);
		velIni = v;
	}
	~Ball() { limpiar(); }
	void limpiar();

	void update();
	void handleEvents();
};

#endif