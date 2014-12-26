#include <string>
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
	Poke(unsigned int num, string name, unsigned int lvl, bool live, string cod);
	//default constructor
	Poke();

	//level incrementer
	void Ding();
	//level getter
	unsigned int GetLvl();

	//kills the Pokemon
	void Kill(string cod);
	//living status getter
	bool Living();

	//species getter
	unsigned int Species();
	//evolver
	void Evolve(unsigned int newNum);
};