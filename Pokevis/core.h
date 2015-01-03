#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <sstream>
#include "party.h"
#include "ticker.h"
#include "console.h"
#include "util.h"
using namespace std;

struct dex {
	string species;
	int num;

	dex(string spec, int no);
};

bool operator< (dex lhs, dex rhs);
bool operator> (dex lhs, dex rhs);
bool operator< (string lhs, dex rhs);
bool operator> (string lhs, dex rhs);

class Core {
private:
	vector<Poke> PC;
	vector<dex> Dex;
	Party Team;

	mutex ConLock;
	string In;
	Action ActIn;

	Util::meCout Mecout;

	Con console;
	stringstream MessQueue;

	Ticker ticker;

	RenderWindow Win;
	Texture BkgTex;
	Sprite Background;
	Texture LogoTex;
	Sprite Logo;

	bool LogLoader();
	bool DexLoader();
	bool LogSaver();

	bool Input();
	//void Update();
	void Display();

	unsigned int NameToNum(string species);

	string PrintPC();

	Poke* FindPoke(string nick);
public:
	Core();
	~Core();
	__declspec(noinline) bool Init();
	void Loop();
};
