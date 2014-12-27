#include <iostream>
#include <string>
using namespace std;

enum Action {
	DEFAULT,
	CATCH,
	DING,
	EVOLVE,
	VICTORY,
	DEATH,
	DEPOSIT,
	WITHDRAW,
	EXIT
};

namespace Con {
	string input(Action& eventOut);
}