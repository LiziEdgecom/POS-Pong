
#include "Hra.h"

Hra::Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta* paLopta)
{
	sirkaPola = sirka;
	vyskaPola = vyska;
	hrac1 = player1;
	hrac2 = player2;
	lopta = paLopta;
}
