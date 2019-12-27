#include <iostream>
#include "Hra.h"

using namespace std;

Hra::Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta* paLopta)
{
	sirkaPola = sirka;
	vyskaPola = vyska;
	hrac1 = player1;
	hrac2 = player2;
	lopta = paLopta;
}

void Hra::vykreslenie()
{
	//vypis skore
	cout << endl;
	cout << "\t\t\t";
	cout << hrac1->getMeno() << " " << hrac1->getScore();
	cout << " : ";
	cout << hrac2->getScore() << " " << hrac2->getMeno();
	cout << endl;

	//vypis plochy
	for (int i = 0; i < vyskaPola; i++) // y suradnica
	{
		for (int j = 0; j < sirkaPola; j++) // x suradnica
		{
			if (i == 0 || j == 0 || j == sirkaPola - 1 || i == vyskaPola - 1) // ak su to okraje
			{
				cout << "\xB2";
			}
			else {
				if (i == lopta->GetSurY() && j == lopta->GetSurX()) // ak su to suradnice lopty
				{
					cout << "O";
				}
				else
				{
					if ( (i == hrac1->getPolohaY()-2 && j == hrac1->getPolohaX()) ||  // ak su tu suradnice hracovych dosiek
						 (i == hrac1->getPolohaY()-1 && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()   && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()+1 && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()+2 && j == hrac1->getPolohaX()) || 
						 (i == hrac2->getPolohaY()-2 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()-1 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()   && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()+1 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()+2 && j == hrac2->getPolohaX()) )
					{
						cout << "\xDB";
					}
					else		// ak je to prazdne policko							
					{
						cout << " ";
					}
				}
			}

			

		}
		cout << endl;

	}
}

void Hra::kolizie()
{
}
