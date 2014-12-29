#include "stdafx.h"
#include "party.h"
#include <iostream>

Party::Party() {
	Team.reserve(6);
}

Party::Party(Poke* team[6]) {
	for (unsigned int i = 0; i < 6; i++) {
		Team.push_back(team[i]);
	}
}

void Party::Display() {
	//cout << "Team size is " << Team.size() << "\n";
	for (unsigned int i = 0; i < Team.size(); i++) {
		cout << "Displaying party member " << i << "\n";
		Team[i]->Draw(i, Disp);
	}

	Disp.Push();
}

bool Party::Withdraw(Poke* mon) {
	if (Team.size() < 6) {
		Team.push_back(mon);
		//cout << mon->ToString() << "\n";
		return true;
	}
	else {
		return false;
	}
}