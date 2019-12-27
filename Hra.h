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
	bool koniec;
public:
	Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta* paLopta);
	~Hra();

	void vykreslenie();
	void kolizie();
	void vstupy();

	int getSirka() { return sirkaPola; };
	int getVyska() { return vyskaPola; };
	bool getKoniec() { return koniec; };
	Hrac* getHrac1() { return hrac1; };
	Hrac* getHrac2() { return hrac2; };
	Lopta* getLopta() { return lopta; };
};

