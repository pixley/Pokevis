#include "stdafx.h"
#include <vector>
#include "console.h"
#include "util.h"
using namespace std;

string caught(string species);
//string dinged(string nick);
//string evolve(string nick, string species);
//string victor(string name);
//string death(string nick);
//string deposit(string nick);
//string wthdrw(string nick);

void badSyntax() {
	cout << "Bad command entered.  Please try again.\n";
	cin.clear();
}

string Con::input(Action& eventOut){
	cout << ">";
	cin.clear();
	string instr;
	getline(cin, instr);
	cin.clear();

	vector<string> substrs;
	Util::strSplit(instr, substrs);

	if (substrs[0] == "exit") {
		eventOut = EXIT;
		return "exiting";
	}

	else if (substrs.size() < 2) {
		cout << substrs.size() << '\n';
		cin.clear();
		badSyntax();
		eventOut = DEFAULT;
		return "bad cmd";
	}

	string& op = substrs[1];

	if (op == "caught") {
		eventOut = CATCH;
		return caught(substrs[0]);
	}
	/*
	else if (op == "dinged") {
		eventOut = DING;
		return dinged(substrs[0]);
	}
	else if (op == "evolved") {
		if (substrs.size() < 4) {
			badSyntax();
			eventOut = DEFAULT;
			return "bad cmd";
		}
		eventOut = EVOLVE;
		return evolve(substrs[0], substrs[3]);
	}
	else if (op == "defeated") {
		eventOut = VICTORY;
		return victor(substrs[0]);
	}
	else if (op == "died") {
		eventOut = DEATH;
		return death(substrs[0]);
	}
	else if (op == "deposited") {
		eventOut = DEPOSIT;
		return deposit(substrs[0]);
	}
	else if (op == "withdrawn") {
		eventOut = WITHDRAW;
		return wthdrw(substrs[0]);
	}
	*/
	else {
		eventOut = DEFAULT;
		return "bad cmd";
	}
}

string caught(string species) {
	string lvl;
	string nick;

	cout << "What level? ";
	cin >> lvl;

	//atoi has overall undefined behavior when receiving bad input
	//this solution may only work on Windows, MSFT's implementation returns 0
	while (atoi(lvl.c_str()) < 1 || atoi(lvl.c_str()) > 100) {
		cout << "A valid level has not been entered.  Please enter a value from 1 to 100. ";
		cin >> lvl;
	}

	cout << "What did you nickname it? ";
	cin >> nick;

	while (nick.length() < 1 || nick.length() > 12) {
		cout << "Invalid nickname entered.  There is a 12-character mex.  Please try again. ";
		cin >> nick;
	}

	return species + ' ' + nick + ' ' + lvl;
}