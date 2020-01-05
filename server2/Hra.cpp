#include "Hra.h"

#include <iostream>


using namespace std;

Hra::Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta * paLopta)
{
	sirkaPola = sirka;
	vyskaPola = vyska;
	hrac1 = player1; //hrac na lavej strane
	hrac2 = player2; //hrac na pravej strane
	lopta = paLopta;
	koniec = false;
        
        
}


void Hra::kolizie()
{
	
	if (lopta->GetSurX()+10 == 783 && (lopta->GetSurY() >= hrac2->getPolohaY() && lopta->GetSurY() <= hrac2->getPolohaY() + 15) ) // ak sa lopta dotyka dosky hraca2
	{
		lopta->ZmenaSmeru((eSmer)((rand() % 3) + 4)); // nahodny smer smerom dolava
	}

	if (lopta->GetSurX() == 16 && (lopta->GetSurY() >= hrac2->getPolohaY() && lopta->GetSurY() <= hrac2->getPolohaY() + 15)) // ak sa lopta dotyka dosky hraca1
	{
		lopta->ZmenaSmeru((eSmer)((rand() % 3) + 1)); // nahodny smer smerom doprava
	}

	if (lopta->GetSurY() == 1)  // ak sa lopta dotkne hornej steny
	{
		lopta->GetSmer() == UPRIGHT ? lopta->ZmenaSmeru(DOWNRIGHT) : lopta->ZmenaSmeru(DOWNLEFT);
	}

	if (lopta->GetSurY() == vyskaPola-2-10)  // ak sa lopta dotkne dolnej steny
	{
		lopta->GetSmer() == DOWNRIGHT ? lopta->ZmenaSmeru(UPRIGHT) : lopta->ZmenaSmeru(UPLEFT);
	}

	if (lopta->GetSurX()+10 == sirkaPola - 1 && !(lopta->GetSurY() >= hrac2->getPolohaY() && lopta->GetSurY() <= hrac2->getPolohaY() + 15)) // ak hrac2 nechyti loptu
	{
		hrac1->Score();
		lopta->Reset();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}

	if (lopta->GetSurX() == 1 && !(lopta->GetSurY() >= hrac2->getPolohaY() && lopta->GetSurY() <= hrac2->getPolohaY() + 15)) // ak hrac1 nechyti loptu
	{
		hrac2->Score();
		lopta->Reset();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}


	//ak nahodou prejde mimo plan
	if (lopta->GetSurX() >= sirkaPola)
	{
		hrac1->Score();
		lopta->Reset();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}

	if (lopta->GetSurX() <= 0)
	{
		hrac2->Score();
		lopta->Reset();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}


	//osetrenie aby hraci nepresli do steny
	if (hrac1->getPolohaY() < 1)
	{
		hrac1->setY(hrac1->getPolohaY() + 1);
	}
	if (hrac2->getPolohaY() < 1)
	{
		hrac2->setY(hrac2->getPolohaY() + 1);
	}

	if (hrac1->getPolohaY()+15 > vyskaPola-1)
	{
		hrac1->setY(hrac1->getPolohaY() - 1);
	}
	if (hrac2->getPolohaY()+15 > vyskaPola - 1)
	{
		hrac2->setY(hrac2->getPolohaY() - 1);
	}

}

