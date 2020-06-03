/* Socket - ClientUDP - Mode Datagramme */

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define UDP_port_S 8000
#define IP_addr_S "127.0.0.1"

using namespace std;

void receiveBoard(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S);

void play(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S);

int main() {
    int sock_C;

    struct sockaddr_in sa_S;

    unsigned int taille_sa_S;

    char message[2048];

    /* creation socket Client */
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);


    /* @IP et num port Serveur */
    bzero((char *) &sa_S, sizeof(struct sockaddr));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = inet_addr(IP_addr_S);
    sa_S.sin_port = htons(UDP_port_S);

    /* emission vers le serveur (a partir du client) */
    taille_sa_S = sizeof(struct sockaddr);
    cout << "Enter your pseudo without space. You can use _ instead : TEST" << endl;
    cin >> message;
    message[2047] = '0';


    sendto(sock_C, message, 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_S, taille_sa_S);
    perror("pseudo");

    /* reception du serveur et affichage */
    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);


    if (message[0] - '0' == 1) {
        cout << "Looking for a 2 player . . ."<< endl;
        while (1) {
            play(sock_C, sa_S, taille_sa_S);
            receiveBoard(sock_C, sa_S, taille_sa_S);
            cout << "Wait please, J2 is playing" << endl;
        }
    } else if (message[0] - '0' == 2) {

        while (1) {
            receiveBoard(sock_C, sa_S, taille_sa_S);
            cout << "Wait please, J2 is playing" << endl;
            play(sock_C, sa_S, taille_sa_S);
        }
    } else {
        cout << "Unknown Error" << endl;
    }

    /* fin */

    close(sock_C);

    exit(EXIT_SUCCESS);

}

void receiveBoard(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S) {
    char msg[2048];
    recvfrom(sock_C, msg, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);
    system("clear");
    cout << "Ce que j'ai reçu \n" << msg << endl;
}

void play(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S) {
    char msg[2048];
    receiveBoard(sock_C, sa_S, taille_sa_S);
    while (1) {

        recvfrom(sock_C, msg, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_S, &taille_sa_S);
        cout << msg << endl;
        int x, y;
        while (1) {
            scanf("%d,%d", &x, &y);
            if (x >= 0 && x <= 8 && y >= 0 && y <= 8) {
                break;
            }
            cout << "Invalid move, x and y must be greater or equal to 0 and lower or equal to 8" << endl;

        }
        msg[0] = x + '0';
        msg[1] = ',';
        msg[2] = y + '0';
        msg[3] = '\0';
        sendto(sock_C, msg, 2048 * sizeof(char), 0,
               (struct sockaddr *) &sa_S, taille_sa_S);


        recvfrom(sock_C, msg, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_S, &taille_sa_S);


        if (msg[0] = 'o' && msg[1] == 'k' && msg[2] == '\0') {
            cout << "ok bien reçu !" << endl;
            break;
        }
        else{
            receiveBoard(sock_C, sa_S, taille_sa_S);
        }


        cout << "tu es bloqué ?" << endl;
    }
}