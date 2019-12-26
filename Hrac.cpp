
#include "Hrac.h"

Hrac::Hrac(int x, int y, string paMeno)
{
	polohaX = x;
	polohaY = y;
	pociatocneX = x;
	pociatocneY = y;
	score = 0;
	meno = paMeno;
}
Hrac::~Hrac()
{
}

void Hrac::PohybHore()
{
	polohaY--;
}

void Hrac::PohybDole()
{
	polohaY++;
}

void Hrac::Reset()
{
	polohaX = pociatocneX;
	polohaY = pociatocneY;
}

void Hrac::Score()
{
	score++;
}
