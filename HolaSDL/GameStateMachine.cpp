#include "GameStateMachine.h"

void GameStateMachine::update()
{
	if (!machineGameStates.empty())
	{
		machineGameStates.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!machineGameStates.empty())
	{
		machineGameStates.back()->render();
	}
}

void GameStateMachine::handleEvents()
{
	/*while (event)
	{
		if (event.type == SDL_QUIT) exit = true;
		else stateMachine->CurrentState->handleEvents(event)
	}*/
}

void GameStateMachine::pushState(GameState *pState)
{
	machineGameStates.push_back(pState);
	machineGameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!machineGameStates.empty())
	{
		if (machineGameStates.back()->onExit())
		{
			delete machineGameStates.back();
			machineGameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState *pState)
{
	if (!machineGameStates.empty())
	{
		if (machineGameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		if (machineGameStates.back()->onExit())
		{
			delete machineGameStates.back();
			machineGameStates.pop_back();
		}
	}
	// push back our new state
	machineGameStates.push_back(pState);
	// initialise it
	machineGameStates.back()->onEnter();
}