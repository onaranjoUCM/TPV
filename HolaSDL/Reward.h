#ifndef RewardH
#define RewardH

#include "MovingObject.h"
#include "Paddle.h"
#include "Vector2D.h"
#include "Texture.h"
#include <list>

class Game;
class Reward : public MovingObject {
private:
	int rewardType;
	Paddle* paddle;
	bool spent = false;
	Game* game;
	list<ArkanoidObject*>::iterator indVector;	// NUEVO

	int animationSpeed = 200;
	int animationFrame = 0;
	int lastAnimationTime;
public:
	Reward() {}
	Reward(int x, int y, int w, int h, int rt, Vector2D v, Texture* t, Paddle* p, Game* g, list<ArkanoidObject*>::iterator i) :
		MovingObject(x, y, w, h, v, t) {
		rewardType = rt;
		paddle = p;
		game = g;
		lastAnimationTime = SDL_GetTicks();
		indVector = i;
	}
	~Reward() { limpiar(); }
	void limpiar();

	void render();
	void update();
	void handleEvents();
	void doEffect();
};

#endif