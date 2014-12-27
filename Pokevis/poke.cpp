#include "stdafx.h"
#include <sstream>
#include "poke.h"
#include "util.h"
using namespace std;

string Poke::ToString() {
	stringstream stream;
	stream << boolalpha << Nickname << ' ' << to_string(DexNum) << ' ' << to_string(Level) << ' ' << Alive << ' ' << Cause;
	return stream.str();
}

Poke::Poke(unsigned int num, string name, unsigned int lvl) {
	Nickname = name;
	DexNum = num;
	Level = lvl;
	Alive = true;
	Cause = "N/A";
}

Poke::Poke(string log) {
	vector<string> info;
	Util::strSplit(log, info);

	Nickname = info[0];
	DexNum = atoi(info[1].c_str());
	Level = atoi(info[2].c_str());
	Cause = info[4];
	if (info[3] == "true")
		Alive = true;
	else if (info[3] == "false")
		Alive = false;
	else {
		Nickname = "Missingno";
		DexNum = 0;
		Level = 0;
		Cause = "Corrupt";
		Alive = false;
	}
}

void Poke::Ding() {
	if (Level < 100)
		Level++;
}

void Poke::Kill(string cod) {
	Alive = false;
	Cause = cod;
}

void Poke::Evolve(unsigned int newNum) {
	DexNum = newNum;
}

void Poke::Draw(unsigned int partyPos, Displayer& disp) {
	disp.Draw(DexNum, Nickname, Level, Alive, partyPos);
}