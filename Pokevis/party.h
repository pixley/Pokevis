#include <string>
#include <vector>
#include <fstream>
#include "poke.h"
#include "display.h"
#include "util.h"
using namespace std;

class Party{
private:
	vector<Poke*> Team;
	Displayer Disp;
public:
	//default constructor; forms empty party
	Party(Util::meCout& mecout, RenderWindow& win);

	//initializes the display
	//bool DispInit();

	//pushes update party display
	void Display();

	//adds Poke to party, checks to ensure party is not full
	bool Withdraw(Poke* mon);
	//removes Poke from party, checks to ensure the Poke is present
	bool Deposit(string nickname);

	//spits out party's Pokes' ToString, separated by newlines
	string ToString();

	//checks whether the indicated Poke is in the party
	bool InParty(Poke* mon);

	bool HatchEgg(unsigned int num, string name);
};