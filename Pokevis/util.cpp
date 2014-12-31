#include "stdafx.h"
#include "util.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void Util::strSplit(string str, vector<string>& tokens, char delim) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	while (getline(ss, buf, delim))
		tokens.emplace_back(buf);

	return;
}

Util::meCout::meCout(mutex& lock) : conOut(cout), Lock(lock) {

}

Util::meCout& Util::meCout::operator<<(const char* s) {
	Lock.lock();
	conOut << s;
	Lock.unlock();
	return *this;
}

Util::meCout& Util::meCout::operator<<(const int i) {
	Lock.lock();
	conOut << i;
	Lock.unlock();
	return *this;
}

Util::meCout& Util::meCout::operator<<(const stringstream& ss) {
	Lock.lock();
	conOut << ss.str();
	Lock.unlock();
	return *this;
}