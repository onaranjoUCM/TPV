#ifndef MovingObjectH
#define MovingObjectH

#include "ArkanoidObject.h"
#include "Vector2D.h"

class Game;
class MovingObject : public ArkanoidObject {
protected:
	Vector2D vel;
public:
	MovingObject() {}
	MovingObject(int x, int y, int w, int h, Vector2D v, Texture* t) :
		ArkanoidObject(x, y, w, h, t) {
		vel = v;
	}
	~MovingObject() { }

	void loadFromFile(ifstream& file, Game* game);
	void saveToFile(ofstream& outfile);

	Vector2D getVel();
	void setVel(Vector2D newVel);
};

#endif