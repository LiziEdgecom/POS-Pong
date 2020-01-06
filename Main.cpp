#include "Main.h"
#include "Hrac.h"
#include "Lopta.h"
#include "Hra.h"
#include "Klient.h"
#include <random>
#include <time.h>
#include <cstdio>

int main(){	
	

	Klient* klient = new Klient();
	if (!klient->getZlyhanie())
	{
		klient->hra();
	}

	//int sirka = 800;
	//int vyska = 640;
	//Hrac* hrac1 = new Hrac(2,315,"andrej");
	//Hrac* hrac2 = new Hrac(sirka-17,315,"matus");
	//Lopta* lopta = new Lopta(400, 320);
	//Hra* hra = new Hra(sirka, vyska, hrac1, hrac2, lopta);
	//hra->zobrazenie();	
	////hra->vykreslenie();
		
	return 0;

}