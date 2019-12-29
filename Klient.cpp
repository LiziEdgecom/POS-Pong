#include "Klient.h"


using namespace std;


Klient::Klient()
{
	if (socket.connect(server, PORT) != sf::TcpSocket::Done)
	{
		cout << "Zlyhanie pri pripojeni na server" << endl;
	}
	else
	{
		cout << "Pripojene na server" << endl;
	}
}

Klient::~Klient()
{
}

void Klient::Citaj()
{
}

void Klient::Posli(string sprava)
{
}

