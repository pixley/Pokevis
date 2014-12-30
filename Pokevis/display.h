#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "util.h"
using namespace sf;
using namespace std;


#ifndef DISPLAY_H
#define DISPLAY_H
class Displayer {
private:
	Texture Spritesheet;
	Texture Background;
	Texture Ball;
	Font Consolas;
	RenderWindow Win;

	Util::meCout& Mecout;

	unsigned int NameSize;
	unsigned int LvlSize;
	unsigned int ImgDim;

public:
	Displayer(Util::meCout& mecout);
	~Displayer();

	void DrawBkg();
	void Draw(unsigned int dexNum, const string& nick, unsigned int lvl, bool alive, unsigned int partyPos);
	void Push();
};

#endif