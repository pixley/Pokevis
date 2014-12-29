#include <iostream>
#include <string>
#include <mutex>
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
	void input(Action& eventOut, string& params, mutex& conLock);
}