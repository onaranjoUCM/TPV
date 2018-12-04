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
	return 0;
}

// PREGUNTAS
// Por que niveles.lenght() es 19?

// TAREAS PENDIENTES
/*
- Arreglar parche de blocksMaps.loadFromFile()
- Error al sobreescribir archivo de guardado
- Guardar los rewards en el fichero
- Mejorar menú
- Implementar excepciones
- Mejorar bucles anidados de blockAt()
- Revisar destructores
- Retocar velocidad paddle
*/