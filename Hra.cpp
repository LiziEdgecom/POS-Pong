#include <iostream>
#include <conio.h>
#include "Hra.h"

using namespace std;

Hra::Hra(int sirka, int vyska, Hrac* player1, Hrac* player2, Lopta* paLopta)
{
	sirkaPola = sirka;
	vyskaPola = vyska;
	hrac1 = player1; //hrac na lavej strane
	hrac2 = player2; //hrac na pravej strane
	lopta = paLopta;
	koniec = false;
}

void Hra::vykreslenie()
{
	system("cls");
	//vypis skore
	cout << endl;
	cout << "\t\t\t";
	cout << hrac1->getMeno() << " " << hrac1->getScore();
	cout << " : ";
	cout << hrac2->getScore() << " " << hrac2->getMeno();
	cout << endl;

	//vypis plochy
	for (int i = 0; i < vyskaPola; i++) // y suradnica
	{
		for (int j = 0; j < sirkaPola; j++) // x suradnica
		{
			if (i == 0 || j == 0 || j == sirkaPola - 1 || i == vyskaPola - 1) // ak su to okraje
			{
				cout << "\xB2";
			}
			else {
				if (i == lopta->GetSurY() && j == lopta->GetSurX()) // ak su to suradnice lopty
				{
					cout << "O";
				}
				else
				{
					if ( (i == hrac1->getPolohaY()-2 && j == hrac1->getPolohaX()) ||  // ak su tu suradnice hracovych dosiek
						 (i == hrac1->getPolohaY()-1 && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()   && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()+1 && j == hrac1->getPolohaX()) || 
						 (i == hrac1->getPolohaY()+2 && j == hrac1->getPolohaX()) || 
						 (i == hrac2->getPolohaY()-2 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()-1 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()   && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()+1 && j == hrac2->getPolohaX()) || 
						 (i == hrac2->getPolohaY()+2 && j == hrac2->getPolohaX()) )
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

void Hra::zobrazenie()
{
	using namespace sf;
	RenderWindow window(VideoMode(800, 400), "POS-PONG");
	Event event;
	CircleShape kruh(10);
	RectangleShape paddle1(Vector2f(15,100));
	RectangleShape paddle2(Vector2f(15,100));
	paddle1.setFillColor(Color::Black);
	paddle2.setFillColor(Color::Black);
	kruh.setFillColor(Color::Green);
	int x = 0;
	Time t = milliseconds(5);
	paddle1.setPosition(Vector2f(2, 120));
	paddle2.setPosition(Vector2f(window.getSize().x - 2 - paddle2.getSize().x, 120));
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
			{
				window.close();
			}
		}
		window.clear(Color::White); 
		kruh.setPosition(x, 0);
		window.draw(kruh);		
		window.draw(paddle1);
		if (Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			paddle2.setPosition(Vector2f(window.getSize().x - 2 - paddle2.getSize().x, paddle2.getPosition().y - 1));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			paddle2.setPosition(Vector2f(window.getSize().x - 2 - paddle2.getSize().x, paddle2.getPosition().y + 1));
		}
		window.draw(paddle2);
		window.display();
		x++;
		sleep(t);

	}
}

void Hra::kolizie()
{
	
	if (lopta->GetSurX() == sirkaPola-3 && (lopta->GetSurY() == hrac2->getPolohaY() - 2 || lopta->GetSurY() == hrac2->getPolohaY() - 1 ||
											lopta->GetSurY() == hrac2->getPolohaY() || lopta->GetSurY() == hrac2->getPolohaY() + 1 ||
											lopta->GetSurY() == hrac2->getPolohaY() + 2) ) // ak sa lopta dotyka dosky hraca2
	{
		lopta->ZmenaSmeru((eSmer)((rand() % 3) + 4)); // nahodny smer smerom dolava
	}

	if (lopta->GetSurX() == 2 && (lopta->GetSurY() == hrac1->getPolohaY() - 2 || lopta->GetSurY() == hrac1->getPolohaY() - 1 ||
							     lopta->GetSurY() == hrac1->getPolohaY() || lopta->GetSurY() == hrac1->getPolohaY() + 1 ||
								lopta->GetSurY() == hrac1->getPolohaY() + 2)) // ak sa lopta dotyka dosky hraca1
	{
		lopta->ZmenaSmeru((eSmer)((rand() % 3) + 1)); // nahodny smer smerom doprava
	}

	if (lopta->GetSurY() == 1)  // ak sa lopta dotkne hornej steny
	{
		lopta->GetSmer() == UPRIGHT ? lopta->ZmenaSmeru(DOWNRIGHT) : lopta->ZmenaSmeru(DOWNLEFT);
	}

	if (lopta->GetSurY() == vyskaPola-2)  // ak sa lopta dotkne dolnej steny
	{
		lopta->GetSmer() == DOWNRIGHT ? lopta->ZmenaSmeru(UPRIGHT) : lopta->ZmenaSmeru(UPLEFT);
	}

	if (lopta->GetSurX() == sirkaPola - 3 && !(lopta->GetSurY() == hrac2->getPolohaY() - 2 || lopta->GetSurY() == hrac2->getPolohaY() - 1 ||
												lopta->GetSurY() == hrac2->getPolohaY() || lopta->GetSurY() == hrac2->getPolohaY() + 1 ||
												lopta->GetSurY() == hrac2->getPolohaY() + 2)) // ak hrac2 nechyti loptu
	{
		hrac1->Score();
		lopta->Reset();
		vykreslenie();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}

	if (lopta->GetSurX() == 2 && !(lopta->GetSurY() == hrac1->getPolohaY() - 2 || lopta->GetSurY() == hrac1->getPolohaY() - 1 ||
								lopta->GetSurY() == hrac1->getPolohaY() || lopta->GetSurY() == hrac1->getPolohaY() + 1 ||
								lopta->GetSurY() == hrac1->getPolohaY() + 2)) // ak hrac1 nechyti loptu
	{
		hrac2->Score();
		lopta->Reset();
		vykreslenie();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}

	if (lopta->GetSurX() >= sirkaPola)
	{
		hrac1->Score();
		lopta->Reset();
		vykreslenie();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}

	if (lopta->GetSurX() <= 0)
	{
		hrac2->Score();
		lopta->Reset();
		vykreslenie();
		lopta->ZmenaSmeru((eSmer)((rand() % 6) + 1));
	}


	//osetrenie aby dosky nepresli do steny
	if (hrac1->getPolohaY() < 3)
	{
		hrac1->setY(hrac1->getPolohaY() + 1);
	}
	if (hrac2->getPolohaY() < 3)
	{
		hrac2->setY(hrac2->getPolohaY() + 1);
	}

	if (hrac1->getPolohaY() > vyskaPola-4)
	{
		hrac1->setY(hrac1->getPolohaY() - 1);
	}
	if (hrac2->getPolohaY() > vyskaPola - 4)
	{
		hrac2->setY(hrac2->getPolohaY() - 1);
	}

}

void Hra::vstupy()
{
	if (_kbhit())
	{
		char klavesa;
		klavesa = _getch();
		if (klavesa == -32)
		{
			klavesa = _getch();
		}
		switch (klavesa)
		{
		default:
			break;
		case 'w':
			hrac1->PohybHore();
			break;
		case 's':
			hrac1->PohybDole();
			break;
		case 72:
			hrac2->PohybHore();
			break;
		case 80:
			hrac2->PohybDole();
			break;
		case 'q':
			koniec = true;
			break;

		}
	}
	
	
}
