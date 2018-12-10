#include "PlayState.h"
#include "Game.h"
#include "checkML.h"
#include <fstream>

using namespace std;

const std::string PlayState::sPlayID = "PLAY";

void PlayState::limpiar() {}

void PlayState::update() {}

void PlayState::render() {}

void PlayState::handleEvents() {}

bool PlayState::onEnter() {
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() {
	std::cout << "exiting PlayState\n";
	return true;
}
