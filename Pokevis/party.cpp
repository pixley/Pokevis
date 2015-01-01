#include "stdafx.h"
#include "party.h"
#include <iostream>

Party::Party(Util::meCout& mecout, RenderWindow& win) : Team(), Disp(mecout, win) {
}

void Party::Display() {
	if (Team.size() > 6 || Team.size() < 0) {
		throw "Team size has become invalid.";
	}

	for (unsigned int i = 0; i < Team.size(); i++) {
		//cout << "Displaying party member " << i << "\n";
		Team[i]->Draw(i, Disp);
	}
}

bool Party::Withdraw(Poke* mon) {
	if (!mon) {
		return false;
	}
	if (InParty(mon)) {
		return false;
	}
	if (Team.size() < 6) {
		Team.emplace_back(mon);
		return true;
	}
	else {
		return false;
	}
	//cout << "Team size is now " << Team.size() << '\n';
}

bool Party::InParty(Poke* mon) {
	for (int i = 0; i < Team.size(); i++) {
		if (Team[i] == mon) {
			return true;
		}
	}
	return false;
}

bool Party::Deposit(string nickname) {
	for (int i = 0; i < Team.size(); i++) {
		if (Team[i]->CheckNick(nickname)) {
			Team.erase(Team.begin() + i);
			return true;
		}
	}
	return false;
}

string Party::ToString() {
	stringstream ss;
	for (int i = 0; i < Team.size(); i++) {
		ss << Team[i]->ToString() << "\n";
	}
	return ss.str();
}

bool Party::HatchEgg(unsigned int num, string name) {
	Poke* hatcher = NULL;
	for (int i = 0; i < Team.size(); i++) {
		if (Team[i]->CheckNick("Egg")) {
			hatcher = Team[i];
		}
	}
	if (hatcher == NULL) {
		return false;
	}
	else {
		hatcher->Hatch(num, name);
		return true;
	}
}