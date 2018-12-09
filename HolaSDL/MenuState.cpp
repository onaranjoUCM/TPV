#include "MenuState.h"

void limpiar(){}

void MenuState::update()
{
	for (int i = 0; i < menuGameObjects.size(); i++)
	{
		menuGameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < menuGameObjects.size(); i++)
	{
		menuGameObjects[i]->render();
	}
}

void MenuState::handleEvents() {}

bool MenuState::onEnter()
{
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	std::cout << "exiting MenuState\n";
	return true;
}