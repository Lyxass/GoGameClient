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

using namespace std;

void receiveBoard(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S);

void play(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S);

bool ipIsValid(string *ip);

int main() {
    int sock_C;

    struct sockaddr_in sa_S;

    unsigned int taille_sa_S;

    char message[2048];

    /* creation socket Client */
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);

    string ip;
    while(1){system("clear");
        cout << "Enter the server's ip address (example : 157.12.155.154)\n";
        cin >> ip;
        if(ipIsValid(&ip)){
            break;
        }
        cout << "Wrong IP" << endl;
    }



    /* @IP et num port Serveur */
    bzero((char *) &sa_S, sizeof(struct sockaddr));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = inet_addr(ip.c_str());
    sa_S.sin_port = htons(UDP_port_S);

    /* emission vers le serveur (a partir du client) */
    taille_sa_S = sizeof(struct sockaddr);
    cout << "Enter your nickname without space. You can use '_' instead : " << endl;
    cin >> message;
    message[2047] = '0';


    sendto(sock_C, message, 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_S, taille_sa_S);
    perror("pseudo");

    /* reception du serveur et affichage */
    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);


    if (message[0] - '0' == 1) {
        cout << "Looking for a 2 player . . ." << endl;
        while (true) {
            play(sock_C, sa_S, taille_sa_S);
            receiveBoard(sock_C, sa_S, taille_sa_S);
            cout << "Wait please, J2 is playing" << endl;
        }
    } else if (message[0] - '0' == 2) {

        while (true) {
            receiveBoard(sock_C, sa_S, taille_sa_S);
            cout << "Wait please, J1 is playing" << endl;
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
    string str(msg);
    if (str.substr(0, 4) == "stop") {
        cout << "End of the game ! You can count the points !" <<endl;
        close(sock_C);
        exit(EXIT_SUCCESS);
    } else {
        system("clear");
        cout << msg << endl;
    }
}

void play(int sock_C, sockaddr_in sa_S, unsigned int taille_sa_S) {
    char msg[2048];
    receiveBoard(sock_C, sa_S, taille_sa_S);
    while (1) {

        recvfrom(sock_C, msg, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_S, &taille_sa_S);
        cout << msg << endl;
        int x, y;
        string input;
        while (1) {
            cin >> input;
            x = input[0] - '0';
            y = input[2] - '0';

            string tmp = input.substr(0, 4);
            if (tmp == "pass" && input.size() == 4) {
                sendto(sock_C, tmp.c_str(), 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_S, taille_sa_S);
                break;
            }
            if (x <= 8 && x >= 0 && y <= 8 && y >= 0 && input[1] == ',' && input.size() == 3) {
                msg[0] = x + '0';
                msg[1] = ',';
                msg[2] = y + '0';
                msg[3] = '\0';
                sendto(sock_C, msg, 2048 * sizeof(char), 0,
                       (struct sockaddr *) &sa_S, taille_sa_S);
                break;
            }
            cout << "Invalid move, x and y must be greater or equal to 0 and lower or equal to 8" << endl;

        }
        recvfrom(sock_C, msg, 2048 * sizeof(char), 0,
                 (struct sockaddr *) &sa_S, &taille_sa_S);


        if (msg[0] == 'o' && msg[1] == 'k' && msg[2] == '\0') {
            break;
        } else {
            receiveBoard(sock_C, sa_S, taille_sa_S);
        }
    }
}

bool ipIsValid(string *ip){
    int w,x,y,z;
    int nb = sscanf(ip->c_str(),"%d.%d.%d.%d",&w,&x,&y,&z);
    cout << w  << x << y << z;
    cout << nb << endl;
    return nb == 4 && w >= 0 && w <= 255 && x >= 0 && x <= 255 && y >= 0 && y <= 255 && z >= 0 && z <= 255;
}