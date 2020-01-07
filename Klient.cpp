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
		delete data;

	}
}

Klient::~Klient()
{
	delete udaje;
	mtx.~mutex();
	socket.~TcpSocket();
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

	size_t recieveddata = 0;
	cout << "Klient pripraveny na citanie" << endl;
	char data[50];
	while (hraBezi)
	{
		while (true)
		{

			cout << "cakam" << endl;
			if (socket.receive(data, 49, recieveddata) == sf::Socket::Done)
			{
				cout << "Server poslal: " << string(data) << endl;

				//rozdelenie stringu
				size_t pos = 0;
				string s = data;
				string token;
				string delimiter = "-";
				mtx.lock();
				for (int i = 0; i < 8; i++)
				{
					pos = s.find(delimiter);
					token = s.substr(0, pos);
					udaje[i] = stoi(token);
					s.erase(0, pos + delimiter.length());
				}
				mtx.unlock();

				break;
			}
		}
	}
	delete data;
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

	/*sf::Time t = sf::milliseconds(2);
	sf::sleep(t);*/
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


	using namespace sf;
	cout << "otvaranie hry" << endl;
	RenderWindow window(VideoMode(800, 640), "POS-PONG");

	thread citanie(&Klient::Citaj, this);

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
				char sprava[50] = "";
				sprintf_s(sprava, "%d D", cisHraca);
				Posli(sprava);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::Key::Q))
				{
					Posli("koniec");
					hraBezi = false;
					citanie.join();
					cout << "Koniec hry!" << endl;
				}
				else {
					if (hraBezi)
					{
						Posli("Cakam na hraca");
					}
				}
			}

		}

		window.clear(Color::White);
		mtx.lock();
		kruh.setPosition(udaje[4], udaje[5]);
		window.draw(kruh);
		paddle1.setPosition(Vector2f(udaje[0], udaje[1]));
		window.draw(paddle1);
		paddle2.setPosition(Vector2f(udaje[2], udaje[3]));
		mtx.unlock();
		window.draw(paddle2);
		window.display();
		sleep(t);
	}
	
	citanie.~thread();	


}

