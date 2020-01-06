#pragma once
#include <iostream>
#include <string.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

#define server "frios2.fri.uniza.sk"	
#define PORT 12356	
using namespace std;

class Klient
{
private:
	std::mutex mtx;
	sf::TcpSocket socket;
	int udaje[10];
	int cisHraca;
	bool zlyhanie = false;

public:
	Klient();
	~Klient();
	bool getZlyhanie() { return zlyhanie; };
	void Citaj();
	void Posli(string sprava);
	void hra();
};

