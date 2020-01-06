#include <stdio.h> 
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
//
using namespace std;
#define TRUE 1 
#define FALSE 0 
#define PORT 12356 

/*    string UpdateHraca(){
        return string g = "aa";
    }
 */



int main(int argc, char *argv[]) {
    bool init = true;
    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[2],
            max_players = 2, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[50]; //data buffur 50 znakov

    //set  socketových descriptorov
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

    //accept the incoming connection 
    addrlen = sizeof (address);
    puts("Cakanie na pripojenie ...");
    Hra *hra = nullptr;
    while (TRUE) {
        //vycisti set soketov	
        FD_ZERO(&readfds);


        //add master socket to set 
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //pridá child socket do setu
        for (i = 0; i < max_players; i++) {
            //socket descriptor 
            sd = client_socket[i];

            //if valid socket descriptor then add to read list 
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function 
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }
        Hrac *player1 = nullptr;
        Hrac *player0 = nullptr;
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket,
                    (struct sockaddr *) &address, (socklen_t*) & addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }


            //informacia o pripojeni 
            cout << "New connection , socket fd is" << new_socket << " ip is :" << inet_ntoa(address.sin_addr) << " port : " << ntohs(address.sin_port);

            //Posle uvitaciu spravu 
            //if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
            //  perror("send");
            //}

            puts("Welcome message sent successfully");

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

                    break;
                }
                read(sd, buffer, 50);
                string menoHraca = buffer;
                int pX = 1;
                int pY = 320;
                if (i != 0) {
                    pX = 798;
                    player1 = new Hrac(pX, pY, menoHraca);
                } else {
                    player0 = new Hrac(pX, pY, menoHraca);
                }

            }
        }
        //
        if (init) {
            Lopta *lopticka = new Lopta(400, 320);
            hra = new Hra(800, 640, player0, player1, lopticka);
            srand(time(NULL) + rand());
            hra->getLopta()->ZmenaSmeru((eSmer) ((rand() % 6) + 1));
            init = false;
        }
        hra->getLopta()->Pohyb();
        hra->kolizie();
        //čita či je to opojenie alebo IO operacia
        for (i = 0; i < max_players; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                //Check if it was for closing , and also read the 
                //incoming message 
                // skontroluje či chce zavrieť tiež prečíta read() y prichadyajucej spravy
                if ((valread = read(sd, buffer, 50)) == 0) {


                    //Somebody disconnected , get his details and print 
                    getpeername(sd, (struct sockaddr*) &address, \
                            (socklen_t*) & addrlen);
                    // printf("Host disconnected , ip %s , port  %d \n",
                    //       inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse 
                    close(sd);
                    client_socket[i] = 0;
                }//Echo back the message that came in 
                else {
                    //update polohy//
                    valread = read(sd, buffer, 50);
                    string sprava = string(buffer).substr(0, 2);

                    if (sprava == "0U") {
                        hra->getHrac1()->PohybHore();
                    } else if (sprava == "0D") {
                        hra->getHrac1()->PohybDole();
                    } else if (sprava == "1U") {
                        hra->getHrac2()->PohybHore();
                    } else if (sprava == "1D") {
                        hra->getHrac2()->PohybDole();
                
            /*    message = "" + hra->getHrac1()->getPolohaX();
                message += "-";
                message += hra->getHrac1()->getPolohaY();
                message += "-";
                message += hra->getHrac2()->getPolohaX();
                message += "-";
                message += hra->getHrac2()->getPolohaY();
                message += "-";
                message += hra->getLopta()->GetSurX();
                message += "-";
                message += hra->getLopta()->GetSurY();
                message += "-";
                message += hra->getHrac1()->getScore();
                message += "-";
                message += hra->getHrac2()->getScore();*/



                client_socket[0]
                        //client_socket[1]

                        //set the string terminating NULL byte on the end 
                        //of the data read 
                        printf("%s\n", buffer);
                buffer[valread] = '\0';
                send(client_socket[0], message, strlen(message), 0);
                send(client_socket[1], message, strlen(message), 0);

            }
        }
    }

}

return 0;
} 