#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include "util.h"
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

class Con {
private:
	mutex& ConLock;
public:
	Con(mutex& conLock);
	void input(Action& eventOut, string& params);
	void output(stringstream& messages);
};