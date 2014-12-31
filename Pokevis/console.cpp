#include "stdafx.h"
#include <vector>
#include "console.h"
#include "util.h"
#include <Windows.h>
using namespace std;

string caught(string species);
string evolve(string nick, string species);
string death(string nick);
string hatch();

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
		Util::strSplit(instr, substrs, ' ');

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
			//account for nicknames with spaces in them
			int off = 0;
			for (int i = 1; i < substrs.size(); i++) {
				if ((substrs[i] == "caught") || (substrs[i] == "dinged") || (substrs[i] == "evolved") ||
					(substrs[i] == "defeated") || (substrs[i] == "died") || (substrs[i] == "deposited") ||
					(substrs[i] == "withdrawn") || (substrs[i] == "obtained") || (substrs[i] == "hatched")){
					off = i;
				}
			}
			for (int i = 1; i < off; i++) {
				substrs[0] = substrs[0] + ' ' + substrs[i];
			}

			string& op = substrs[off];

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
			params = substrs[0] + '\t' + substrs[off + 2];
			}
			else if (op == "defeated") {
			eventOut = VICTORY;
			params = substrs[0];
			}
			else if (op == "died") {
			eventOut = DEATH;
			params = death(substrs[0]);
			}
			else if (op == "deposited") {
			eventOut = DEPOSIT;
			params = substrs[0];
			}
			else if (op == "withdrawn") {
			eventOut = WITHDRAW;
			params = substrs[0];
			}
			else if (op == "obtained" && substrs[0] == "Egg") {
				eventOut = EGG;
				params = "Egg";
			}
			else if (op == "hatched" && substrs[0] == "Egg") {
				eventOut = HATCH;
				params = hatch();
			}
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

	return species + '\t' + nick + '\t' + lvl;
}

string death(string nick) {
	string cause;

	cout << "To what did " << nick << " die? ";
	getline(cin, cause);

	return nick + '\t' + cause;
}

string hatch() {
	string species;
	string nick;

	cout << "What hatched from the egg? ";
	getline(cin, species);
	cout << "What did you nickname it? ";
	getline(cin, nick);

	return species + '\t' + nick;
}
