#include "Main.h"
#include "Hrac.h"
#include "Lopta.h"
#include "Hra.h"
void main(){
	int sirka = 80;
	int vyska = 20;
	Hrac* hrac1 = new Hrac(1,10,"andrej");
	Hrac* hrac2 = new Hrac(sirka-2,10,"matus");
	Lopta* lopta = new Lopta(40, 10);
	Hra* hra = new Hra(sirka, vyska, hrac1, hrac2, lopta);
	hra->vykreslenie();
}