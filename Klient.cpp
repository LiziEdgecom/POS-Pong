#include "Klient.h"

#include <cstdio>

using namespace std;


Klient::Klient()
{
	if (socket.connect(server, PORT) != sf::TcpSocket::Done)
	{
		cout << "Zlyhanie pri pripojeni na server" << endl;		
		zlyhanie = true;
	}
	else
	{
		cout << "Pripojene na server" << endl;

		cout << "priradenie cisla hracovi" << endl;
		char data[21];
		size_t recieveddata = 0;
		while (true)
		{
			if (socket.receive(data, 20, recieveddata) == sf::Socket::Done)
			{
				cout << "Server poslal: " << string(data) << endl;
				cisHraca = int(data[0]);
				break;
			}
		}

	}
	
	

}

Klient::~Klient()
{
}

void Klient::Citaj()
{
	
	/*format spravy    x1-y1-x2-y2-bx-by-s1-s2-
	 - oddelovac
	x1 y1 suradnice hraca 1
	x2 y2 suradnice hraca 2
	bx by suradnice lopty
	s1 s2 score hracov
	*/

	char data[81];
	string delimiter = "-";
	size_t recieveddata = 0;
	cout << "Klient pripraveny na citanie"<<endl;
	while (true)
	{
		cout << "cakam" << endl;
		if (socket.receive(data, 80, recieveddata) == sf::Socket::Done)
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
			break;
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


void Klient::hra()
{
	/*
	udaje[0] x1
	udaje[1] y1
	udaje[2] x2
	udaje[3] y2
	udaje[4] bx
	udaje[5] by
	udaje[6] s1
	udaje[7] s2
	*/
	thread citanie(&Citaj);

	using namespace sf;
	int i = 1;

	string s = "" + i ;
	s += "" + i;
	cout << "otvaranie hry" << endl;
	RenderWindow window(VideoMode(800, 640), "POS-PONG");
	Event event;
	CircleShape kruh(10);
	RectangleShape paddle1(Vector2f(15, 100));
	RectangleShape paddle2(Vector2f(15, 100));
	paddle1.setFillColor(Color::Black);
	paddle2.setFillColor(Color::Black);
	kruh.setFillColor(Color::Green);
	Time t = milliseconds(5);
	paddle1.setPosition(Vector2f(2, 320));
	paddle2.setPosition(Vector2f(window.getSize().x - 2 - paddle2.getSize().x, 320));
	while (window.isOpen())
	{		
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
			{
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			char sprava[50] = "";
			sprintf_s(sprava, "%d U", cisHraca);
			Posli(sprava);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			{
				char sprava[50]="";
				sprintf_s(sprava, "%d D", cisHraca);
				Posli(sprava);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::Key::Q))
				{
					Posli("koniec");
				}
			}
			
		}
		
		window.clear(Color::White);
		cout << "cita udaje" << endl;
		//Citaj();
		cout << "udaje nacitane" << endl;
		kruh.setPosition(udaje[4], udaje[5]);
		window.draw(kruh);
		paddle1.setPosition(Vector2f(udaje[0], udaje[1]));
		window.draw(paddle1);
		paddle2.setPosition(Vector2f(udaje[2], udaje[3]));
		window.draw(paddle2);
		window.display();
		sleep(t);		
	}
	citanie.join();
}

