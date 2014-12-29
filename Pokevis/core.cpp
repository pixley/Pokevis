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

Core::Core() : Mecout(ConLock), console(ConLock), Team(Mecout) {
	In = "N/A";
	ActIn = DEFAULT;
}

Core::~Core() {
}

bool Core::LogLoader() {
	return true;
}

bool Core::DexLoader() {
	fstream dexFile;
	dexFile.open("dex.txt");

	//the dexFile must open for functionality
	if (dexFile.fail()) {
		Mecout << "Dex file has failed to load.\n";
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
	bool load = LogLoader() && DexLoader();
	return load;
}

void Core::Loop() {
	thread conThread(&Con::input, ref(console), ref(ActIn), ref(In));
	while (Input()) {
		Display();
	}
}

bool Core::Input() {
	bool out = true;
	if (ConLock.try_lock()) {
		if (In != "N/A") {
			vector<string> substr;
			Util::strSplit(In, substr);

			switch (ActIn) {
			case DEFAULT:
				break;
			case EXIT:
				out = false;
				break;
			case CATCH:
				PC.push_back(Poke(NameToNum(substr[0]), substr[1], atoi(substr[2].c_str())));
				Team.Withdraw(&(PC.back()));
				//cout << "Poke has been logged.\n";
				break;
			}

			In = "N/A";
			ActIn = DEFAULT;
		}
		ConLock.unlock();
	}
	return out;
}

void Core::Display() {
	try {
		Team.Display();
	}
	catch (string e) {
		MessQueue << e;
		thread outThread(&Con::output, ref(console), ref(MessQueue));
	}
}