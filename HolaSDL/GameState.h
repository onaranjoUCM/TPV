#ifndef GameStateH
#define GameStateH

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include <list>
#include <vector>
#include <stack>

using namespace std;

class Game;
class GameState {
protected:
	list<GameState*> states;
	Game* game;
public:
	~GameState() {};
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	//virtual GameState currentState();

	virtual std::string getStateID() const = 0;
};
#endif