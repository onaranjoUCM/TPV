#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Game.h"
#include "Menu.h"
#include "checkML.h"

using namespace std;

int main(int argc, char* argv[]){
	//_CrtSetDbgFlag(CRTDBG ALLOC MEM DF | CRTDBG LEAK CHECK DF);
	Menu menu = Menu();
	menu.run();
	//Game game = Game();
	//game.run();
	//delete game;
	return 0;
}

// PREGUNTAS

// TAREAS PENDIENTES
/*
- Llevarse más colisiones de Game.collides() a <Objeto>.collides()
- Destruir blocksMap correctamente al cargar un nuevo nivel (método limpiar)
- Mejorar bucles anidados de blockAt()
- Revisar destructores
*/