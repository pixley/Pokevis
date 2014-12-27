#include "stdafx.h"
#include "util.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void Util::strSplit(string str, vector<string>& tokens) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	while (getline(ss, buf, '\s'))
		tokens.push_back(buf);

	return;
}