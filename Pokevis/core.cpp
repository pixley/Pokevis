#include "stdafx.h"
#include "core.h"
#include "util.h"
#include <algorithm>
using namespace std;

dex::dex(string spec, int no) {
	species = spec;
	num = no;
}

bool operator< (dex lhs, dex rhs) {
	return lhs.species < rhs.species;
}

bool operator>(dex lhs, dex rhs) {
	return lhs.species > rhs.species;
}

bool operator< (string lhs, dex rhs) {
	return lhs < rhs.species;
}

bool operator> (string lhs, dex rhs) {
	return lhs > rhs.species;
}

int binary_search(const vector<dex>& sorted_vec, string key) {
	size_t mid, left = 0;
	size_t right = sorted_vec.size(); // one position passed the right end
	while (left < right) {
		mid = left + (right - left) / 2;
		if (key > sorted_vec[mid]){
			left = mid + 1;
		}
		else if (key < sorted_vec[mid]){
			right = mid;
		}
		else {
			return sorted_vec[mid].num;
		}
	}

	return 0;
}

bool Core::LogLoader() {
	return true;
}

bool Core::DexLoader() {
	fstream dexFile;
	dexFile.open("dex.txt");

	//the dexFile must open for functionality
	if (dexFile.fail()) {
		return false;
	}

	string line;
	unsigned int i = 1;
	
	//push all (species, num) pairs into the Dex vector
	while (!dexFile.eof()) {
		getline(dexFile, line, '\n');
		Dex.push_back(dex(line, i));
		i += 1;
	}

	//sort the dex entries into alphabetical order for faster search
	sort(Dex.begin(), Dex.end());

	return true;
}

bool Core::LogSaver() {
	return false;
}

unsigned int Core::NameToNum(string species) {
	//cout << "Species to name conversion initiated.\n";
	return binary_search(Dex, species);
}

bool Core::Init() {
	return LogLoader() && DexLoader();
}

void Core::Loop() {
	Display();
	while (Input()) {
		Display();
	}
}

bool Core::Input() {
	Action act;
	string input = Con::input(act);
	vector<string> substr;
	Util::strSplit(input, substr);

	switch (act) {
	case DEFAULT:
		return true;
	case EXIT:
		return false;
	case CATCH:
		PC.push_back(Poke(NameToNum(substr[0]), substr[1], atoi(substr[2].c_str())));
		Team.Withdraw(&(PC.back()));
		//cout << "Poke has been logged.\n";
		break;
	}
	return true;
}

void Core::Display() {
	Team.Display();
}