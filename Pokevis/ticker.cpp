#include "stdafx.h"
#include "ticker.h"
#include <algorithm>

Ticker::Ticker(RenderWindow& win) : Win(win) {
	if (!BkgTex.loadFromFile("Ticker Bkg.png"))
		throw string("Failed to load ticker background.\n");
	if (!Consolas.loadFromFile("consola.ttf"))
		throw string("Failed to load font.\n");
	if (!LogoTex.loadFromFile("Logo.png"))
		throw string("Failed to load Logo\n");

	FontSize = 16;

	Background.setTexture(BkgTex);
	Background.setPosition(1320, 96);

	Logo.setTexture(LogoTex);
	Logo.setPosition(1320, 96);
}

void Ticker::LoadLog(string log){
	log.pop_back();
	Util::strSplit(log, Events, '\n');
}

Ticker::~Ticker() {
	Win.close();
}

void Ticker::AddEvent(string* act) {
	//add timestamp to the event
	time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm uTime;
	tm* utcTime = &uTime;
	gmtime_s(utcTime, &time);
	int m = utcTime->tm_mon;
	int d = utcTime->tm_mday;
	int h = utcTime->tm_hour;
	int min = utcTime->tm_min;

	char c_stamp[21];

	sprintf_s(c_stamp, "[%2d-%2d,%2d:%2dZ]", m + 1, d, h, min);

	string stamp(c_stamp);

	replace(stamp.begin(), stamp.end(), ' ', '0');

	Events.emplace_back(string(stamp + " " + *act));
}

void Ticker::AddEvent(string* act, Ticker& t) {
	//add timestamp to the event
	time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm uTime;
	tm* utcTime = &uTime;
	gmtime_s(utcTime, &time);
	int m = utcTime->tm_mon;
	int d = utcTime->tm_mday;
	int h = utcTime->tm_hour;
	int min = utcTime->tm_min;

	char c_stamp[21];

	sprintf_s(c_stamp, "[%2d-%2d,%2d:%2dZ]", m + 1, d, h, min);

	string stamp(c_stamp);

	replace(stamp.begin(), stamp.end(), ' ', '0');

	t.Events.emplace_back(string(stamp + " " + *act));
}

void Ticker::Display() {
	//this method is also used for the event loop, which is required, else the window
	//becomes unresponsive; Pokevis doesn't use the window for any input
	Event event;
	while (Win.pollEvent(event)) {
		//nothing here; just polling events
	}

	//draw the background
	Win.draw(Background);
	Win.draw(Logo);

	//draw the 24 most recent event strings
	for (int i = 1; (i < 25) && ((int)(Events.size() - i) >= 0); i++) {
		Text act(Events[Events.size() - i], Consolas, FontSize);
		act.setPosition(1325, (FontSize) * (i - 1) + 266);
		Win.draw(act);
	}
}

string Ticker::ToString() {
	stringstream ss;
	for (int i = 0; i < Events.size(); i++) {
		ss << Events[i] << '\n';
	}

	return ss.str();
}