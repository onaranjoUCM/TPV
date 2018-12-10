#pragma once
#include "ArkanoidObject.h"
#include "Vector2D.h"

class MenuButton : public ArkanoidObject
{
private:
	enum buttonState {mouseOut = 0, mouseOver = 1, isClick = 1};
	Texture* textura;
	buttonState mouseCurrentFrame;
	int buttonX, buttonY, buttonW, buttonH;
public:
	MenuButton(const ArkanoidObject* pParams);
	virtual void render();
	virtual void update();
	virtual void clean();


	/*ArkanoidObject(int x, int y, int w, int h, Texture* t) :
		pos(x, y), w(w), h(h), texture(t) {}*/
};