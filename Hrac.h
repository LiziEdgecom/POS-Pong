#pragma once
#include <string>
using namespace std;
class Hrac {

private:
	int polohaX;
	int polohaY;
	int pociatocneX;
	int pociatocneY;
	int score;
	string meno;
	
public:
	Hrac(int x, int y, string paMeno);
	~Hrac();
	void PohybHore();
	void PohybDole();
	void Reset();
	void Score();
	void setY(int y) { polohaY = y; };
	int getPolohaX() { return polohaX; };
	int getPolohaY() { return polohaY; };
	int getScore() { return score; };
	string getMeno() { return meno; };
};


