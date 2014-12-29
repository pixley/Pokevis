#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include "party.h"
#include "ticker.h"
#include "console.h"
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

	bool LogLoader();
	bool DexLoader();
	bool LogSaver();

	bool Input();
	//void Update();
	void Display();

	unsigned int NameToNum(string species);
public:
	Core();
	bool Init();
	void Loop();
};
