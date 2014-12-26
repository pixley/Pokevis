#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "poke.h"
using namespace std;

class Party{
private:
	vector<Poke*> Team;
public:
	//no default constructor
	Party(vector<Poke*>);

	//pushes update party display
	void Display();

	//adds Poke to party, checks to ensure party is not full
	bool Withdraw(Poke* mon);
	//removes Poke from party, checks to ensure the Poke is present
	bool deposit(string nickname);
}