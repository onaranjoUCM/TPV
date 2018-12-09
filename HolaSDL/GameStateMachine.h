#ifndef GameStateMachineH
#define GameStateMachineH

#include "GameState.h"

class GameState;
class GameStateMachine
{
	private:
		//list<GameState*> machineGameStates; //como lo haria yo
		stack<GameState*> stack;
		std::vector<GameState*> machineGameStates; // como recomienda el libro ese
		bool exit;
	public:
		void update();
		void render();
		void handleEvents();

		void pushState(GameState* pState);
		void changeState(GameState* pState);
		void popState();
		//virtual GameState currentState() { return currentState; }
		/*void popState() {
			if (stack.empty()) {
				delete stack.top();
				stack.pop();
			}
		}*/
		/*void changeStates(GameState s) {
			popState();
			pushState(s);
		}*/
};


#endif // !GameStateMachineH

/*class Game {
	enum GameState{menu, play, end, pause};
	private:
		GameStateMachine stateMachine;
	Game::game() {
		stateMachine.pushState(new menu());
	}
	void run() {
		while (!exit) {
			handleEvents();
			stateMachine.currentState->update();
		}
	}
	void render() {
		...renderClear();
		stateMachine.currentState->render();
	}
};*/
/*class GameStateMachine
{
private:
	Stack << GameState * >> stack;
public:
	GameStateMachine();
	~GameStateMachine();

	GameStates currentState() { return ...(? ); }
	void popState() {
		if (stack.empty()) {
			delete stack.top();
			stack.pop();
		}
	}
	void changeStates(GameState s) {
		popState();
		pushState(s);
	}
	void handleEvents() {
		while (event) {
			if (event.type == SDL_QUIT) exit = true;
			else
				stateMachine.CurrentState->handleEvents(event);
		}
	}
};*/
