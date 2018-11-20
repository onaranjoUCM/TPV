#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include "checkML.h"

using namespace std;

int main(int argc, char* argv[]){
	//_CrtSetDbgFlag(CRTDBG ALLOC MEM DF | CRTDBG LEAK CHECK DF);

	Game game = Game();
	game.run();
	//delete game;
	return 0;
}

// PREGUNTAS
/*
- Vector velIni
- Colisión de la bola
*/

// TAREAS PENDIENTES
/*
- Llevarse más colisiones de Game.collides() a <Objeto>.collides()
- Destruir blocksMap correctamente al cargar un nuevo nivel (método limpiar)
- Mejorar bucles anidados de blockAt()
- Eliminar valores inmediatos
*/