#include "Main.h"
#include "Hrac.h"
#include "Lopta.h"
#include "Hra.h"
#include "Klient.h"
#include <random>
#include <time.h>
int main(){	
	int sirka = 40;
	int vyska = 20;
	Hrac* hrac1 = new Hrac(1,10,"andrej");
	Hrac* hrac2 = new Hrac(sirka-2,10,"matus");
	Lopta* lopta = new Lopta(20, 10);
	Hra* hra = new Hra(sirka, vyska, hrac1, hrac2, lopta);
	hra->vykreslenie();
	srand(time(NULL)+rand());
	hra->getLopta()->ZmenaSmeru((eSmer) ((rand() % 6) + 1));
	while (!hra->getKoniec())
	{
		lopta->Pohyb();
		hra->vstupy();
		hra->kolizie();
		hra->vykreslenie();
		
	}
	return 0;
}