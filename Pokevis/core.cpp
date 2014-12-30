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

	PC.reserve(100);
}

Core::~Core() {
}

bool Core::LogLoader() {
	fstream save("save.txt", ios_base::in);

	if (!save.is_open())
		return false;

	string line;
	getline(save, line);

	if (line != "Party")
		return false;

	getline(save, line);
	while (line != "PC") {
		PC.emplace_back(Poke(line));
		Team.Withdraw(&(PC.back()));
		getline(save, line);
	}

	while (!save.eof()) {
		getline(save, line);
		PC.emplace_back(Poke(line));
	}
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
		Dex.emplace_back(dex(line, i));
		i += 1;
	}

	//sort the dex entries into alphabetical order for faster search
	sort(Dex.begin(), Dex.end());

	return true;
}

bool Core::LogSaver() {
	fstream save("save.txt", ios_base::trunc | ios_base::out);

	if (!save.is_open())
		return false;

	save << "Party\n" << Team.ToString();

	save << "PC";
	for (int i = 0; i < PC.size(); i++) {
		if (!Team.InParty(&(PC[i]))) {
			save << '\n' << PC[i].ToString();
		}
	}

	save.close();

	return true;
}

unsigned int Core::NameToNum(string species) {
	//cout << "Species to name conversion initiated.\n";
	return binary_search(Dex, species);
}

bool Core::Init() {
	if (!LogLoader()) {
		cout << "No save data found.  Creating new run.  Good luck.\n";
	}
	else {
		cout << "Save data found.  Welcome back and good luck.\n";
	}
	bool load = DexLoader();
	return load;
}

void Core::Loop() {
	thread conThread(&Con::input, ref(console), ref(ActIn), ref(In));
	while (Input()) {
		Display();
	}

	LogSaver();
	conThread.join();
}

bool Core::Input() {
	bool out = true;
	if (ConLock.try_lock()) {
		if (In != "N/A") {
			vector<string> substr;
			Util::strSplit(In, substr, '\t');

			switch (ActIn) {
			case DEFAULT:
				break;
			case EXIT:
				out = false;
				break;
			case CATCH:
				PC.emplace_back(Poke(NameToNum(substr[0]), substr[1], atoi(substr[2].c_str())));
				Team.Withdraw(&(PC.back()));
				break;
			case DING:
				FindPoke(substr[0])->Ding();
				break;
			case EVOLVE:
				FindPoke(substr[0])->Evolve(NameToNum(substr[1]));
				break;
			case DEATH:
				FindPoke(substr[0])->Kill("Because reasons.");
				break;
			case VICTORY:
				break;
			case DEPOSIT:
				Team.Deposit(substr[0]);
				break;
			case WITHDRAW:
				Team.Withdraw(FindPoke(substr[0]));
				break;
			}

			cout << "New party lineup:\n" << Team.ToString();
			cout << "New PC lineup:\n" << PrintPC();

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

string Core::PrintPC() {
	stringstream ss;
	for (int i = 0; i < PC.size(); i++) {
		ss << PC[i].ToString() << "\n";
	}
	return ss.str();
}

Poke* Core::FindPoke(string nick) {
	for (int i = 0; i < PC.size(); i++) {
		if (PC[i].CheckNick(nick)) {
			return &(PC[i]);
		}
	}
	return NULL;
}