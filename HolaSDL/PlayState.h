#ifndef PlayStateH
#define PlayStateH

#include "GameState.h"
#include "Vector2D.h"
#include "Texture.h"

class Game;
class PlayState : public GameState
{
private:
	list<GameObject*> objects;
	static const std::string sPlayID;
public:
	~PlayState() { limpiar(); }
	void limpiar();

	virtual void update();
	virtual void render();
	virtual void handleEvents();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return sPlayID; }
};

#endif