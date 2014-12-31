#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <ctime>
#include <cwchar>
#include "util.h"
using namespace sf;
using namespace std;

class Ticker {
private:
	unsigned int FontSize;
	RenderWindow Win;
	Texture BkgTex;
	Sprite Background;
	Font Consolas;
	vector<string> Events;

public:
	Ticker();
	~Ticker();
	void AddEvent(string* act);
	static void AddEvent(string* act, Ticker& t);
	string ToString();
	void Display();
	void LoadLog(string log);
};