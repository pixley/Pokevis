#include <iostream>
#include <string>
using namespace std;

enum Event {
	DEFAULT,
	CATCH,
	DING,
	EVOLVE,
	VICTORY,
	DEATH,
	DEPOSIT,
	WITHDRAW
};

namespace Con {
	string input(Event& eventOut);
}