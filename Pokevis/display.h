#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;


#ifndef DISPLAY_H
#define DISPLAY_H
class Displayer {
private:
	Texture Spritesheet;
	Font Consolas;
	RenderWindow Win;

	unsigned int NameSize;
	unsigned int LvlSize;
	unsigned int ImgDim;

public:
	Displayer();
	~Displayer();
	void Draw(unsigned int dexNum, string nick, unsigned int lvl, bool alive, unsigned int partyPos);
	void Push();
};

#endif