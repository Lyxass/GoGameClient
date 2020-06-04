#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "mainwindow.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QMessageBox>

#define UDP_port_S 8000
#define IP_addr_S "127.0.0.1"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *vue;
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
    message[0] = 'G';
    message[1] = 'u';
    message[2] = 'i';
    message[3] = '1';
    message[4] = '\000';
    message[2047] = '1';
    qDebug() << "test Socket";
    sendto(sock_C, message, 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_S, taille_sa_S);

    /* reception du serveur et affichage */
    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);

    if(message[0] - '0' == 1){
        vue = new MainWindow(1,sock_C,sa_S,taille_sa_S);
        QGraphicsView *tst =vue->getView();
        tst->show();
        QMessageBox::information(vue,"Wait","Waiting another player");
        vue->updateMap();
        QMessageBox::information(vue,"Your turn","It's your turn");
        vue->enableButton(true);
    }
    else if(message[0] - '0' == 2){
        vue = new MainWindow(2,sock_C,sa_S,taille_sa_S);
        QGraphicsView *tst =vue->getView();
        tst->show();
        QMessageBox::information(vue,"Wait","The other player is playing");
        vue->updateMap();
        vue->updateMap();
        QMessageBox::information(vue,"Your turn","It's your turn");
        vue->enableButton(true);


    }

    return a.exec();
}
