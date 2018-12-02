#include "SDL_image.h"
#include "Texture.h"
#include "checkML.h"

const int MENU_WIDTH = 800;
const int MENU_HEIGHT = 600;

class Menu {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect titleRect;
	Texture* titleText;

	// boton para jugar
	SDL_Rect playButtonRect;
	Texture* playButtonText;
	//boton para cargar archivo
	SDL_Rect loadButtonRect;
	Texture* loadButtonText;
	//boton para salir del juego
	SDL_Rect endButtonRect;
	Texture* endButtonText;

	bool exit = false;
public:
	Menu();
	~Menu();
	void run();
	void update();
	void render();
	void handleEvents();
};