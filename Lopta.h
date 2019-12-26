#pragma once

enum eSmer { STOP = 0, RIGHT = 1, UPRIGHT = 2, DOWNRIGHT = 3, LEFT = 4, DOWNLEFT = 5, UPLEFT = 6 };
class Lopta
{
private:
	int surX;
	int surY;
	int povodneX;
	int povodneY;	
	eSmer smer;
public:
	Lopta(int x, int y);
	~Lopta();
	void Pohyb();
	void Reset();
	void ZmenaSmeru(eSmer s);
	int GetSurX() { return surX; };
	int GetSurY() { return surY; };

};

