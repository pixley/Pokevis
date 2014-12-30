#include "stdafx.h"
#include <vector>
#include "console.h"
#include "util.h"
#include <Windows.h>
using namespace std;

string caught(string species);
string evolve(string nick, string species);

void badSyntax() {
	cout << "Bad command entered.  Please try again.\n";
	cin.ignore(100, '\n');
}

Con::Con(mutex& conLock) : ConLock(conLock) {
}

void Con::output(stringstream& messages) {
	ConLock.lock();
	cout << messages.str();
	ConLock.unlock();
}

void Con::input(Action& eventOut, string& params){
	while (true) {
		ConLock.lock();

		cout << ">";
		string instr;
		getline(cin, instr);

		bool blank = false;

		if (instr.size() == 0)
			blank = true;

		//cout << params;

		vector<string> substrs;
		Util::strSplit(instr, substrs);

		if (blank) {
			eventOut = DEFAULT;
			params = "N/A";
		}

		else if (substrs[0] == "exit") {
			eventOut = EXIT;
			params = "exiting";
			ConLock.unlock();
			break;
		}

		else if (substrs.size() < 2) {
			cout << substrs.size() << '\n';
			cin.ignore(100, '\n');
			badSyntax();
			eventOut = DEFAULT;
			params = "N/A";
		}

		else {

			string& op = substrs[1];

			if (op == "caught") {
				eventOut = CATCH;
				params = caught(substrs[0]);
			}
			else if (op == "dinged") {
			eventOut = DING;
			params = substrs[0];
			}
			else if (op == "evolved") {
			if (substrs.size() < 4) {
				badSyntax();
				eventOut = DEFAULT;
				params = "bad cmd";
				}
			eventOut = EVOLVE;
			params = substrs[0] + ' ' + substrs[3];
			}
			/*
			else if (op == "defeated") {
			eventOut = VICTORY;
			params = victor(substrs[0]);
			}
			*/
			else if (op == "died") {
			eventOut = DEATH;
			params = substrs[0];
			}
			/*
			else if (op == "deposited") {
			eventOut = DEPOSIT;
			params = deposit(substrs[0]);
			}
			else if (op == "withdrawn") {
			eventOut = WITHDRAW;
			params = wthdrw(substrs[0]);
			}
			*/
			else {
				eventOut = DEFAULT;
				params = "N/A";
			}

		}

		ConLock.unlock();

		//sleep for one second to allow main thread to access the new data
		Sleep(1000);
	}
}

string caught(string species) {
	string lvl;
	string nick;

	cout << "What level? ";
	getline(cin, lvl);

	//atoi has overall undefined behavior when receiving bad input
	//this solution may only work on Windows, MSFT's implementation returns 0
	while (atoi(lvl.c_str()) < 1 || atoi(lvl.c_str()) > 100) {
		cout << "A valid level has not been entered.  Please enter a value from 1 to 100. ";
		getline(cin, lvl);
	}

	cout << "What did you nickname it? ";
	getline(cin, nick);

	while (nick.length() < 1 || nick.length() > 12) {
		cout << "Invalid nickname entered.  There is a 12-character max.  Please try again. ";
		getline(cin, nick);
	}

	return species + ' ' + nick + ' ' + lvl;
}
