#include "stdafx.h"
#include "display.h"
#include <iostream>
using namespace sf;
using namespace std;

Displayer::Displayer(Util::meCout& mecout) : Win(VideoMode(418, 726), "Pokevis Party", Style::Titlebar), Mecout(mecout) {
	if (!Spritesheet.loadFromFile("Poke Sprites.png"))
		throw string("Failed to load spritesheet.\n");
	if(!Consolas.loadFromFile("consola.ttf"))
		throw string("Failed to load font.\n");
	if (!Background.loadFromFile("B2 Bkg.png"))
		throw string("Failed to load background.\n");
	NameSize = 48;
	LvlSize = 30;
	ImgDim = 96;

	Win.display();
}

Displayer::~Displayer(){
	Win.close();
}

void Displayer::DrawBkg() {
	//this method is also used for the event loop, which is required, else the window
	//becomes unresponsive; Pokevis doesn't use the window for any input
	Event event;
	while (Win.pollEvent(event)) {
		//nothing here; just polling events
	}
	Sprite bkg(Background);

	Win.draw(bkg);
}

void Displayer::Draw(unsigned int dexNum, const string& nick, unsigned int lvl, bool alive, unsigned int partyPos) {
	unsigned int spriteRow = (dexNum - 1) / 31;
	unsigned int spriteCol = (dexNum - 1) % 31;

	//throw "Now in Draw method.\n";

	Text* name = new Text(nick, Consolas, NameSize);
	Text* level = new Text("Lvl: " + to_string(lvl), Consolas, LvlSize);
	Sprite* icon = new Sprite(Spritesheet, IntRect(spriteCol * ImgDim, spriteRow * ImgDim, ImgDim, ImgDim));

	//throw "Element positions being set.\n";

	icon->setPosition(0, ImgDim * partyPos);
	name->setPosition(ImgDim, ImgDim * partyPos);
	level->setPosition(ImgDim, ImgDim * partyPos + 56);

	//throw "Colors being set.\n";

	level->setColor(Color(190, 190, 190, 255));

	if (!alive) {
		icon->setColor(Color(127, 127, 127, 255));
		name->setColor(Color(190, 95, 95, 255));
		level->setColor(Color(127, 127, 127, 255));
	}

	//throw "Drawing elements.\n";

	Win.draw(*icon);
	Win.draw(*name);
	Win.draw(*level);

	delete icon;
	delete name;
	delete level;

	//throw "Draw complete.\n";
}

void Displayer::Push() {
	//throw "Pushing frame.\n";
	Win.display();
}