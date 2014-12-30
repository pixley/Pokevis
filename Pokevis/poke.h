#include <string>
#include "display.h"
using namespace std;

class Poke{
private:
	string Nickname;
	unsigned int DexNum;
	unsigned int Level;
	bool Alive;
	string Cause;

public:
	//catch constructor
	Poke(unsigned int num, string name, unsigned int lvl);
	//load constructor
	Poke(string log);

	//level incrementer
	void Ding();

	//kills the Pokemon
	void Kill(string cod);

	//evolver
	void Evolve(unsigned int newNum);

	//string representation of the Poke for saving
	string ToString();

	//initiates drawing of Poke status to screen
	void Draw(unsigned int partyPos, Displayer& disp);

	bool CheckNick(string nick);
};