#ifndef BlockH
#define BlockH

#include "Texture.h"
#include "Vector2D.h"
#include "ArkanoidObject.h"
#include "checkML.h"

class Block : public ArkanoidObject {
	private:
		int color = 0;
		int row = 0;
		int col = 0;
	public:
		Block() {}
		Block(int x, int y, int w, int h, int r, int c, int co, Texture* t) :
			ArkanoidObject(x, y, w, h, t) {
			color = co;
			row = r;
			col = c;
		}
		~Block() { limpiar(); }

		void update();
		void handleEvents();
		void limpiar();
		void render();
		void setColor(int c);
		int getR();
		int getC();
		int getColor();
};

#endif