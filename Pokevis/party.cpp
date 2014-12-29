#include "stdafx.h"
#include "party.h"
#include <iostream>

Party::Party(Util::meCout& mecout) : Team(), Disp(mecout) {
}

Party::Party(Poke* team[6], Util::meCout& mecout) : Team(), Disp(mecout) {
	for (unsigned int i = 0; i < 6; i++) {
		Team.push_back(team[i]);
	}
}

void Party::Display() {
	//cout << "Team size is " << Team.size() << "\n";
	Disp.DrawBkg();

	if (Team.size() > 6 || Team.size() < 0) {
		throw "Team size has become invalid.";
	}

	for (unsigned int i = 0; i < Team.size(); i++) {
		//cout << "Displaying party member " << i << "\n";
		Team[i]->Draw(i, Disp);
	}

	Disp.Push();
}

bool Party::Withdraw(Poke* mon) {
	//cout << Team.size() << '\n';
	if (Team.size() < 6) {
		Team.push_back(mon);
		//cout << mon->ToString() << "\n";
		return true;
	}
	else {
		return false;
	}
}