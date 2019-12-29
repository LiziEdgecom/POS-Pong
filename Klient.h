#pragma once
#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#define server "frios2.fri.uniza.sk"	
#define PORT 12356	

class Klient
{
private:
	sf::TcpSocket socket;
public:
	Klient();
	~Klient();
	void Citaj();
	void Posli(string sprava);
};

