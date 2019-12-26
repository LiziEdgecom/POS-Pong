#pragma once
#include "Hrac.h"
#include "Lopta.h"

class Hra
{
private:
	int sirkaPola;
	int vyskaPola;
	Hrac* hrac1;
	Hrac* hrac2;
	Lopta* lopta;
public:
	Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta* paLopta);
	~Hra();
	int getSirka() { return sirkaPola; };
	int getVyska() { return vyskaPola; };
};

