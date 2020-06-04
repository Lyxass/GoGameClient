#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gopawn.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QMessageBox>
#include <QLabel>
#include <golabel.h>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(int nbPlay,int sock_C,sockaddr_in sa_S,unsigned int taille_sa_S);
    QGraphicsScene* getScene();
    QGraphicsView* getView();
    int getPlayerNb();
    void setPlayerNb(int nb);
    void setScene(QGraphicsScene* scene);
    void setView(QGraphicsView* view);
    void enableButton(bool b);
    void updateMap();
    void play(GoPawn *p);
    ~MainWindow();
private:
    GoPawn *matrix[9][9];
    QIcon blackPawn;
    QIcon whitePawn;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int nbPlayer;

    int sock_C;
    struct sockaddr_in sa_S;
    unsigned int taille_sa_S;

    GoLabel *scoreJ1;
    GoLabel *scoreJ2;

    char message[2048];

};

#endif // MAINWINDOW_H
