#include "stdafx.h"
#include "display.h"
using namespace sf;
using namespace std;

Displayer::Displayer() : Win(VideoMode(408, 726), "Pokevis Party", Style::None) {
	Spritesheet.loadFromFile("Poke Sprites.png");
	Consolas.loadFromFile("consola.ttf");
	NameSize = 48;
	LvlSize = 30;
	ImgDim = 96;


}

Displayer::~Displayer(){
	Win.close();
}

void Displayer::Draw(unsigned int dexNum, string nick, unsigned int lvl, bool alive, unsigned int partyPos) {
	unsigned int spriteRow = (dexNum - 1) / 31;
	unsigned int spriteCol = (dexNum - 1) % 31;

	Text name(nick, Consolas, NameSize);
	Text level("Lvl: " + to_string(lvl), Consolas, LvlSize);
	Sprite icon(Spritesheet, IntRect(spriteRow * ImgDim, spriteCol * ImgDim, ImgDim, ImgDim));

	icon.setPosition(0, 96 * partyPos);
	name.setPosition(96, 96 * partyPos + 8);
	level.setPosition(96, 96 * partyPos + 56);

	level.setColor(Color(127, 127, 127, 255));

	if (!alive) {
		icon.setColor(Color(127, 127, 127, 255));
		name.setColor(Color(190, 95, 95, 255));
	}

	Win.draw(icon);
	Win.draw(name);
	Win.draw(level);
}

void Displayer::Push() {
	Win.display();
}