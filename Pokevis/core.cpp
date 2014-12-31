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

Core::Core() : Mecout(ConLock), console(ConLock),
Win(VideoMode(1920, 96 + 648), "Pokevis Display", Style::None), ticker(Win), Team(Mecout, Win) {
	In = "N/A";
	ActIn = DEFAULT;

	PC.reserve(100);

	Win.setPosition(Vector2i(0, 0));
}

Core::~Core() {
}

bool Core::LogLoader() {
	ifstream save("save.txt");

	if (!save.is_open()) {
		cout << "Just checking that there isn't a file!\n";
		return false;
	}

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

	getline(save, line);
	while (line != "Events" && !save.eof()) {
		PC.emplace_back(Poke(line));
		getline(save, line);
	}

	if (save.eof()) {
		string begin("Game begun!");
		ticker.AddEvent(&begin);
		return true;
	}

	string act;
	stringstream acts;
	while (!save.eof()) {
		getline(save, act);
		acts << act << '\n';
	}
	ticker.LoadLog(acts.str());
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

	save << "\nEvents\n";
	save << ticker.ToString();

	save.close();

	return true;
}

unsigned int Core::NameToNum(string species) {
	//cout << "Species to name conversion initiated.\n";
	return binary_search(Dex, species);
}

__declspec(noinline) bool Core::Init() {
	cout << "Welcome to Pokevis, a Nuzlocke stream visualizer tool.\n";

	string loaded("Game resumed!");
	string begin("Game begun!");

	if (!LogLoader()) {
		cout << "No save data found.  Creating new run.  Good luck.\n";
		ticker.AddEvent(&begin);
	}
	else {
		cout << "Save data loaded.  Welcome back and good luck.\n";
		ticker.AddEvent(&loaded);
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
	string act;
	Poke* subject;
	if (ConLock.try_lock()) {
		if (In != "N/A") {
			vector<string> substr;
			Util::strSplit(In, substr, '\t');

			switch (ActIn) {
			case DEFAULT:
				break;
			case EXIT:
				out = false;
				act = "Session ended.";
				break;
			case CATCH:
				PC.emplace_back(Poke(NameToNum(substr[0]), substr[1], atoi(substr[2].c_str())));
				Team.Withdraw(&(PC.back()));
				act = "Caught a level " + substr[2] + " " + substr[0] + " named " + substr[1] + ".";
				break;
			case DING:
				subject = FindPoke(substr[0]);
				if (subject) {
					subject->Ding();
					act = substr[0] + " leveled up!";
				}
				break;
			case EVOLVE:
				subject = FindPoke(substr[0]);
				if (subject) {
					subject->Evolve(NameToNum(substr[1]));
					act = substr[0] + " evolved into " + substr[1] + "!";
				}
				break;
			case DEATH:
				subject = FindPoke(substr[0]);
				if (subject) {
					subject->Kill(substr[1]);
					act = substr[0] + " died to " + substr[1] + ".";
				}
				break;
			case VICTORY:
				act = substr[0] + " was defeated!";
				break;
			case DEPOSIT:
				if (Team.Deposit(substr[0]))
					act = substr[0] + " has been deposited.";
				break;
			case WITHDRAW:
				if (Team.Withdraw(FindPoke(substr[0])))
					act = substr[0] + " has been withdrawn.";
				break;
			case EGG:
				PC.emplace_back(Poke(650, "Egg", 0));
				Team.Withdraw(&(PC.back()));
				act = "Received an egg!";
				break;
			case HATCH:
				if (Team.HatchEgg(NameToNum(substr[0]), substr[1])) {
					act = "Egg hatched into " + substr[0] + "!  Nickname is " + substr[1] + "!";
				}
				break;
			}

			//cout << "New party lineup:\n" << Team.ToString();
			//cout << "New PC lineup:\n" << PrintPC();

			In = "N/A";
			ActIn = DEFAULT;
		}
		ConLock.unlock();
		if (act.length() > 0)
			ticker.AddEvent(&act);
	}
	return out;
}

void Core::Display() {
	try {
		Team.Display();
		ticker.Display();
		Win.display();
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