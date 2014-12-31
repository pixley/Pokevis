#include "stdafx.h"
#include "display.h"
#include <iostream>
using namespace sf;
using namespace std;

Displayer::Displayer(Util::meCout& mecout, RenderWindow& win) : Win(win), Mecout(mecout) {
	if (!Spritesheet.loadFromFile("Poke Sprites.png"))
		throw string("Failed to load spritesheet.\n");
	if(!Consolas.loadFromFile("consola.ttf"))
		throw string("Failed to load font.\n");
	if (!Background.loadFromFile("Bkg.png"))
		throw string("Failed to load background.\n");
	if (!Ball.loadFromFile("Ball.png"))
		throw string("Failed to load ball image.\n");
	NameSize = 32;
	LvlSize = 26;
	ImgDim = 96;
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
	Sprite* icon = new Sprite(Spritesheet, IntRect(spriteCol * ImgDim + 7, spriteRow * ImgDim, ImgDim, ImgDim));
	Sprite* ball = new Sprite(Ball);

	//throw "Element positions being set.\n";

	unsigned int pokeWidth = ImgDim + 220;

	icon->setPosition(pokeWidth * partyPos, 0);
	ball->setPosition(pokeWidth * partyPos, 0);
	name->setPosition(pokeWidth * partyPos + ImgDim, 10);
	level->setPosition(pokeWidth * partyPos + ImgDim, 46);

	//throw "Colors being set.\n";

	if (alive) {
		level->setColor(Color(190, 190, 190, 255));
		ball->setColor(Color(255, 255, 255, 127));
	}
	else {
		icon->setColor(Color(63, 63, 63, 255));
		name->setColor(Color(190, 95, 95, 255));
		level->setColor(Color(127, 127, 127, 255));
		ball->setColor(Color(255, 0, 0, 127));
	}

	//throw "Drawing elements.\n";

	Win.draw(*ball);
	Win.draw(*icon);
	Win.draw(*name);
	Win.draw(*level);

	delete icon;
	delete name;
	delete level;
	delete ball;

	//throw "Draw complete.\n";
}