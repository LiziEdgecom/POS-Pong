#include "Lopta.h"

Lopta::Lopta(int x, int y)
{
	surX = x;
	surY = y;
	povodneX = x;
	povodneY = y;
	smer = STOP;
}

Lopta::~Lopta()
{
}

void Lopta::Pohyb()
{
	switch (smer) 
	{
	case RIGHT:
		surX++;
		break;
	case UPRIGHT:
		surX++;
		surY--;
		break;
	case DOWNRIGHT:
		surX++;
		surY++;
		break;
	case LEFT:
		surX--;
		break;
	case UPLEFT:
		surX--;
		surY--;
		break;
	case DOWNLEFT:
		surX--;
		surY++;
		break;
	default:
		break;
	}
}

void Lopta::Reset()
{
	surX = povodneX;
	surY = povodneY;
	smer = STOP;
}

void Lopta::ZmenaSmeru(eSmer s)
{
	smer = s;
}
