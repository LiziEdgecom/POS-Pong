#pragma once
#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#define server "frios2.fri.uniza.sk"	
#define PORT 12356	
using namespace std;

class Klient
{
private:
	sf::TcpSocket socket;
	int udaje[10];
	char cisHraca;
	bool zlyhanie = false;

public:
	Klient();
	~Klient();
	bool getZlyhanie() { return zlyhanie; };
	void Citaj();
	void Posli(string sprava);
	void hra();
};

