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
	
	/*format spravy    x1-y1-x2-y2-bx-by-s1-s2-H-W
	 - oddelovac
	x1 y1 suradnice hraca 1
	x2 y2 suradnice hraca 2
	bx by suradnice lopty
	s1 s2 score hracov
	H - vyska hracieho pola
	W - sirka hracieho pola
	*/

	char data[21];
	int udaje[10];
	string delimiter = "-";
	size_t recieveddata = 0;
	while (true)
	{
		if (socket.receive(data, 20, recieveddata) == sf::Socket::Done)
		{
			cout << "Server poslal: " << string(data) << endl;

			//rozdelenie stringu
			size_t pos_start = 0, pos_end, delim_len = delimiter.length();
			string slovo;
			vector<string> res;

			while ((pos_end = string(data).find(delimiter, pos_start)) != string::npos) {
				slovo = string(data).substr(pos_start, pos_end - pos_start);
				pos_start = pos_end + delim_len;
				res.push_back(slovo);
			}

			res.push_back(string(data).substr(pos_start));
			for (int i = 0; i < 8; i++)
			{
				udaje[i] = stoi(res[i]);
			}
			update(udaje); // poslat ziskane udaje na vypisanie/vykreslenie

			
		}
	}
}

void Klient::Posli(string sprava)
{
	// sprava bude obsahovat znak pre pohyb hraca dole/hore (UP pre hore, DOWN pre dole)
	if (socket.send(sprava.c_str(), sprava.length() + 1) != sf::TcpSocket::Done)
	{
		cout << "Odoslanie zlyhalo" << endl;
	}
	else
	{
		cout << "Odoslane serveru: " << sprava << endl;
	}
}

void Klient::update(int udaje[])
{
	// zobrazenie udajov
	
	system("cls");
	//vypis skore
	cout << endl;
	cout << "\t\t\t";
	cout << udaje[6];
	cout << " : ";
	cout << udaje[7];
	cout << endl;

	//vypis plochy
	for (int i = 0; i < udaje[8]; i++) // y suradnica
	{
		for (int j = 0; j < udaje[9]; j++) // x suradnica
		{
			if (i == 0 || j == 0 || j == udaje[9] - 1 || i == udaje[8] - 1) // ak su to okraje
			{
				cout << "\xB2";
			}
			else {
				if (i == udaje[5] && j == udaje[4]) // ak su to suradnice lopty
				{
					cout << "O";
				}
				else
				{
					if ((i == udaje[1] - 2 && j == udaje[0]) ||  // ak su tu suradnice hracovych dosiek
						(i == udaje[1] - 1 && j == udaje[0]) ||
						(i == udaje[1] && j == udaje[0]) ||
						(i == udaje[1] + 1 && j == udaje[0]) ||
						(i == udaje[1] + 2 && j == udaje[0]) ||
						(i == udaje[3] - 2 && j == udaje[2]) ||
						(i == udaje[3] - 1 && j == udaje[2]) ||
						(i == udaje[3] && j == udaje[2]) ||
						(i == udaje[3] + 1 && j == udaje[2]) ||
						(i == udaje[3] + 2 && j == udaje[2]))
					{
						cout << "\xDB";
					}
					else		// ak je to prazdne policko							
					{
						cout << " ";
					}
				}
			}



		}
		cout << endl;

	}


}

