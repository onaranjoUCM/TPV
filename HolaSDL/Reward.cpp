#include "Reward.h"
#include "Game.h"
#include "checkML.h"

using namespace std;

void Reward::limpiar() {
	game = nullptr;
}

void Reward::update() {
	pos = pos + vel;
	if (SDL_HasIntersection(&getRect(), &paddle->getRect()) && !spent) {
		spent = true;
		doEffect();
	}
	if (getY() > WIN_HEIGHT) {
		game->deleteReward(this);
	}
}

void Reward::handleEvents() { }

void Reward::render() {
	if (SDL_GetTicks() > lastAnimationTime + animationSpeed) {
		animationFrame++;
		lastAnimationTime = SDL_GetTicks();
		if (animationFrame == 7) {
			animationFrame = 0;
		}
	}
	renderFrame(rewardType, animationFrame);
}

void Reward::doEffect() {
	paddle->resetW();
	switch (rewardType) {
	case 0:
		game->nextLevel();
		break;
	case 1:
		paddle->expandW();
		break;
	case 3:
		paddle->reduceW();
		break;
	case 4:
		game->ganaVida();
		break;
	}
	game->deleteReward(this);
}