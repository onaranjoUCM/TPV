#ifndef BallH
#define BallH

#include "Texture.h"
#include "Vector2D.h"
#include "MovingObject.h"
#include "checkML.h"

class Game;
class Ball : public MovingObject{
private:
	Game* game;
public:
	Ball() {}
	Ball(int x, int y, int w, int h, Vector2D v, Texture* t, Game* g) :
		//pos(x, y), w(w), h(h), vel(vx, vy), texture(t), game(g) {}
		MovingObject(x, y, w, h, v, t) {
		game = g;
	}
	~Ball() { limpiar(); }
	void limpiar();

	void update();
	void handleEvents();
};

#endif