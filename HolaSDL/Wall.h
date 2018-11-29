#ifndef WallH
#define WallH

#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"
#include "ArkanoidObject.h"

class Wall : public ArkanoidObject {
private:
	string wallPosition;
public:
	Wall() {}
	Wall(string p, int x, int y, int w, int h, Texture* t) :
		ArkanoidObject(x, y, w, h, t) {
		wallPosition = p; 
	}
	~Wall() { }

	void update();
	void handleEvents();
	bool collides(const SDL_Rect* rect, Vector2D& collVector);
};

#endif