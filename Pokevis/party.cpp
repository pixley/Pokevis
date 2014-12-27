#include "stdafx.h"
#include "party.h"

Party::Party() {
	Team.resize(6);
}

Party::Party(Poke* team[6]) {
	for (unsigned int i = 0; i < 6; i++) {
		Team.push_back(team[i]);
	}
}

void Party::Display() {
	for (unsigned int i = 0; i < 6 && Team[i] != NULL; i++) {
		Team[i]->Draw(i, Disp);
	}
}

bool Party::Withdraw(Poke* mon) {
	if (Team.size() < 6) {
		Team.push_back(mon);
		return true;
	}
	else {
		return false;
	}
}