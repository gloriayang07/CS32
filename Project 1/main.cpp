#include "Arena.h"
#include "History.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
using namespace std;

int main()
{
	Arena a(3, 4);
	a.addPlayer(2, 3);
	a.addZombie(2, 2);
	a.addZombie(2, 4);
	a.addZombie(1, 3);
	a.player()->moveOrAttack(RIGHT);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(RIGHT);
	a.player()->moveOrAttack(UP);
	a.history().display();
	cout << "====" << endl;
}