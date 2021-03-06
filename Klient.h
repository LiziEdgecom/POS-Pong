#pragma once
#include "heap_monitor.h"
#include <iostream>
#include <string>
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
	sf::Time wait = sf::milliseconds(100);
	int udaje[8];
	int cisHraca;
	bool zlyhanie = false;
	bool hraBezi = true;

public:
	Klient();
	~Klient();
	bool getZlyhanie() { return zlyhanie; };
	void Citaj();
	void Posli(string sprava);
	void hra();
};

