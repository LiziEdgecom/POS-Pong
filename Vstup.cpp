#include "Vstup.h"

void Vstup::nacitanie(Klient* klient)
{
	if (_kbhit())
	{
		char klavesa;
		klavesa = _getch();
		if (klavesa == -32)
		{
			klavesa = _getch();
		}
		switch (klavesa)
		{
		default:
			break;		
		case 72:
			klient->Posli("UP");
			break;
		case 80:
			klient->Posli("DOWN");
			break;

		}
	}
}
