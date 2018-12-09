#include "MenuButton.h"



MenuButton::MenuButton(const ArkanoidObject* pParams) :
	ArkanoidObject(buttonX, buttonY, buttonW, buttonH, textura)
{
	mouseCurrentFrame = mouseOut; // start at frame 0
}
void MenuButton::render()
{
	ArkanoidObject::render(); // use the base class drawing
}
void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->getX() < (pMousePos.getX() + buttonW)
		&& pMousePos->getX() > pMousePos.getX()
		&& pMousePos->getY() < (pMousePos.getY() + buttonH)
		&& pMousePos->getY() > pMousePos.getY())
	{
		mouseCurrentFrame = mouseOver;
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			mouseCurrentFrame = isClick;
		}
	}
	else
	{
		mouseCurrentFrame = mouseOut;
	}
}

void MenuButton::clean()
{
	ArkanoidObject::~ArkanoidObject();
}
