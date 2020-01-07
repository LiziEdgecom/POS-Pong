
#include <stdio.h> 
#include <bits/stdc++.h>
#include <iostream> 
#include <string.h> //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> //close 
#include <arpa/inet.h> //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include "Hrac.h"
#include "Lopta.h"
#include "Hra.h"
#include <string>
#include <thread>
#include <cstdio>

using namespace std;
#define TRUE 1 
#define FALSE 0 
#define PORT 12356 



int main(int argc, char *argv[]) {
   
    bool init = true;
    int initH = 0;
    bool closeH = false;
    int opt = true;
    int master_socket, addrlen, new_socket, client_socket[2],
            max_players = 2, activity, i, valread, sd;
    int max_sd;
    struct timeval tv;
    struct sockaddr_in address;
    Hrac *player1 = nullptr;
    Hrac *player0 = nullptr;
    char buffer[50];
    
    fd_set readfds;

    /*sprava*/
    char *message = "haloo skuska 123 123";
   
    //inicializovanie hráčou - nastavime na 0 - not checked 
    for (i = 0; i < max_players; i++) {
        client_socket[i] = 0;
    }

    //vytvorenie master soketu 
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //nastavenie master socketu aby prijimal viac pripojeni, 
    //malo by ist aj bez toho 
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
            sizeof (opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //nastavime typ soketu
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bindneme socket na port 12356 
    if (bind(master_socket, (struct sockaddr *) &address, sizeof (address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //printf("Listener on port %d \n", PORT); 

    //špecifukovanie čakajúcich pripojení na master socket 
    if (listen(master_socket, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //prijímanie prichádzajúcih pripojení
    addrlen = sizeof (address);
    puts("Cakanie na pripojenie ...");
    Hra *hra = nullptr;


    while (!closeH) {
        //vycisti set soketov	

        FD_ZERO(&readfds);


        //pridá mástra do file deskriptoru
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //pridá child socket do setu
        for (i = 0; i < max_players; i++) {
            //socket descriptor 
            sd = client_socket[i];

            //ak je valídny socket descripto tak ho pridá do FD_setu na citanie 
            if (sd > 0)
                FD_SET(sd, &readfds);

            //najvacsie číslo f. descriptoru,potrebne na vybratie funkcie 
            if (sd > max_sd)
                max_sd = sd;
        }

        //čaka na aktivitu na soketoch ,timeout je primarne na null cize caka stále 
        //pokial sa nenastaví tv
        activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        //ak sa niečo stane na mastrovi tak e to pokus o pripojenie
       
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket,
                    (struct sockaddr *) &address, (socklen_t*) & addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }


            //informacia o pripojeni 
            cout << "Nove pripojenie , socket fd is" << new_socket << " ip  : " << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port);

            



            //prida novy soket do pola
            for (i = 0; i < max_players; i++) {
                //ak je pozicia prazdna 
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    if (i == 0) {
                        message = "0";
                    } else {
                        message = "1";
                    }


                    //      cout << "cislo hraca " << buffer<< endl;
                    sd = client_socket[i];
                    if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
                        perror("send");
                    }

                    printf("Adding to list of sockets as %d\n", i);
                    cout << message;
                    string menoHraca = "AAAA";
                    int pX = 1;
                    int pY = 320;
                    if (initH == 0) {
                        player0 = new Hrac(pX, pY, menoHraca);
                        initH++;
                    } else {
                        pX = 783;
                        player1 = new Hrac(pX, pY, menoHraca);
                        initH++;
                    }
                    break;
                }
                //read(sd, buffer, 50);


            }

        }
        //
        if (init && initH == 2) {
            Lopta *lopticka = new Lopta(400, 320);
            hra = new Hra(800, 640, player0, player1, lopticka);
            srand(time(NULL) + rand());
            hra->getLopta()->ZmenaSmeru((eSmer) ((rand() % 6) + 1));
            init = false;
        }
        // ked mame oboch hracov
        if (initH == 2) {
            hra->getLopta()->Pohyb();
            hra->kolizie();

            //čita či je to opojenie alebo IO operacia
            for (i = 0; i < max_players; i++) {
                



                sd = client_socket[i];

                if (FD_ISSET(sd, &readfds)) {
                    
                    // skontroluje či chce zavrieť tiež prečíta read() z prichadyajucej spravy
                    if ((valread = read(sd, buffer, 49)) == 0) {

                        tv.tv_sec = 1;
                        //niekto sa odpojil tak vypis jeho udaje 
                        getpeername(sd, (struct sockaddr*) &address, \
                                (socklen_t*) & addrlen);
                        printf("Host disconnected , ip %s  /n ", inet_ntoa(address.sin_addr));

                        //zavry socket a označ cs na 0 aby sa dal znovu použiť 
                        close(sd);
                        client_socket[i] = 0;
                    }
                    else {
                        cout << string(buffer).substr(0, 4) << endl; //update polohy//

                        string sprava = string(buffer).substr(0, 4);

                        if (sprava == "48 U") {
                            hra->getHrac1()->PohybHore();
                        } else if (sprava == "48 D") {
                            hra->getHrac1()->PohybDole();
                        } else if (sprava == "49 U") {
                            hra->getHrac2()->PohybHore();
                        } else if (sprava == "49 D") {
                            hra->getHrac2()->PohybDole();
                        }
                        sprava = string(buffer).substr(0, 6);
                        if (sprava == "koniec") {

                            hra->setKoniec();
                            for (i = 0; i < sizeof (sprava); i++) {
                                buffer[i] = sprava[i];
                            }
                            if (sd = client_socket[0]) {
                                send(client_socket[0], buffer, 49, 0);
                                send(client_socket[1], buffer, 49, 0);
                            } else {
                                send(client_socket[1], buffer, 49, 0);
                                send(client_socket[0], buffer, 49, 0);
                            }
                        } else {

                            char text[50];
                            sprintf(text, "%d-%d-%d-%d-%d-%d-%d-%d-", hra->getHrac1()->getPolohaX(), hra->getHrac1()->getPolohaY(), hra->getHrac2()->getPolohaX(),
                                    hra->getHrac2()->getPolohaY(), hra->getLopta()->GetSurX(), hra->getLopta()->GetSurY(), hra->getHrac1()->getScore(), hra->getHrac2()->getScore());
                            for (i = 0; i < sizeof (text); i++) {
                                buffer[i] = text[i];
                            }




                            cout << endl;
                            printf("%s\n", buffer);
                            //  buffer[valread] = '\0';
                            if (client_socket[0] != 0 && client_socket[1] != 0) {
                                if (send(sd, buffer, 49, 0) != strlen(buffer)) {
                                    perror("SEND");
                                }
                            }
                        }
                       
                    }
                    if (client_socket[0] == 0 && client_socket[1] == 0) {

                        closeH = true;
                        close(master_socket);
                        master_socket=0;
                    }
                }
            }

        }
    }
    delete hra;
    hra = nullptr;

    return 0;
}

