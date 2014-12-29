#include "stdafx.h"
#include "display.h"
#include <iostream>
using namespace sf;
using namespace std;

Displayer::Displayer() : Win(VideoMode(418, 726), "Pokevis Party", Style::Default) {
	if (!Spritesheet.loadFromFile("Poke Sprites.png"))
		cout << "Failed to load spritesheet.\n";
	if(!Consolas.loadFromFile("consola.ttf"))
		cout << "Failed to load font.\n";
	NameSize = 48;
	LvlSize = 30;
	ImgDim = 96;

	Win.display();
}

Displayer::~Displayer(){
	Win.close();
}

void Displayer::Draw(unsigned int dexNum, string nick, unsigned int lvl, bool alive, unsigned int partyPos) {
	unsigned int spriteRow = (dexNum - 1) / 31;
	unsigned int spriteCol = (dexNum - 1) % 31;

	cout << "Now in Draw method.\n";

	Text* name = new Text(nick, Consolas, NameSize);
	Text* level = new Text("Lvl: " + to_string(lvl), Consolas, LvlSize);
	Sprite* icon = new Sprite(Spritesheet, IntRect(spriteCol * ImgDim, spriteRow * ImgDim, ImgDim, ImgDim));

	cout << "Element positions being set.\n";

	icon->setPosition(0, ImgDim * partyPos);
	name->setPosition(ImgDim, ImgDim * partyPos);
	level->setPosition(ImgDim, ImgDim * partyPos + 56);

	cout << "Colors being set.\n";

	level->setColor(Color(127, 127, 127, 255));

	if (!alive) {
		icon->setColor(Color(127, 127, 127, 255));
		name->setColor(Color(190, 95, 95, 255));
	}

	cout << "Drawing elements.\n";

	Win.draw(*icon);
	Win.draw(*name);
	Win.draw(*level);

	delete icon;
	delete name;
	delete level;

	cout << "Draw complete.\n";
}

void Displayer::Push() {
	//cout << "Pushing frame.\n";
	Win.display();
}