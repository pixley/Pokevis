#include <string>
#include <vector>
#include <fstream>
#include "poke.h"
#include "display.h"
using namespace std;

class Party{
private:
	vector<Poke*> Team;
	Displayer Disp;
public:
	//default constructor; forms empty party
	Party();
	//constructor from log
	Party(Poke* team[6]);

	//initializes the display
	//bool DispInit();

	//pushes update party display
	void Display();

	//adds Poke to party, checks to ensure party is not full
	bool Withdraw(Poke* mon);
	//removes Poke from party, checks to ensure the Poke is present
	bool Deposit(string nickname);
};