#include "mainwindow.h"

MainWindow::MainWindow(int nbPlay,int sock_C,sockaddr_in sa_S,unsigned int taille_sa_S)
{
    setFixedSize(429,520);
    this->nbPlayer = nbPlay;
    this->sock_C = sock_C;
    this->sa_S = sa_S;
    this->taille_sa_S = taille_sa_S;
    this->setFixedSize(429,429);
    this->scene = new QGraphicsScene();



    QPixmap *img = new QPixmap(":/images/Goban_9x9_.png");
    scene->addPixmap(*img);
    this->view= new QGraphicsView(scene);
    int offsetx = 0;
    int offsety = 0;
    offsety = -16;
    for(int i=0; i<9; i++){
        offsetx = -16;
        for(int o=0;o<9;o++){
           matrix[i][o] =new GoPawn(i,o,this);
           matrix[i][o]->setMinimumSize(QSize(1,1));
           matrix[i][o]->setGeometry(offsetx,offsety,52,52);
           offsetx +=51;
           matrix[i][o]->setStyleSheet("background-color: rgba(255, 25, 255, 0.0);");
//           if(i%2 == 0){
//                if(o%2 == 0){
//                    matrix[i][o]->setStyleSheet("background-color: rgba(255, 25, 255, 0.2);");
//                }
//                else{
//                    matrix[i][o]->setStyleSheet("background-color: rgba(25, 255, 255, 0.2);");
//                }
//            }
//            else{
//                if(o%2 == 0){
//                    matrix[i][o]->setStyleSheet("background-color: rgba(25, 255, 255, 0.2);");
//                }
//                else{
//                    matrix[i][o]->setStyleSheet("background-color: rgba(255, 25, 255, 0.2);");
//                }
//            }
            matrix[i][o]->setFlat(true);
            matrix[i][o]->setUpdatesEnabled(false);
            scene ->addWidget(matrix[i][o]);
        }
        offsety += 51;

    }

    scoreJ1 = new GoLabel();
    scoreJ2 = new GoLabel();

    scoreJ1->setStyleSheet("background-color: rgba(255, 255, 255, 0.0); color: white;");
    scoreJ2->setStyleSheet("background-color: rgba(255, 255, 255, 0.0); color: white;");



    scoreJ1->setText(QString("Nb of white Pawn captured : 0"));
    scoreJ2->setText(QString("Nb of black Pawn captured  : 0"));

    scoreJ1->setGeometry(0,429,300,20);
    scoreJ2->setGeometry(0,450,300,20);
    scene->addWidget(scoreJ1);
    scene->addWidget(scoreJ2);
    passButton = new GoPassButton("Skip your turn",this,this);
    passButton->setGeometry(329,429,100,41);
    passButton->setStyleSheet("background-color: rgba(255, 255, 255, 0.0); color: white;");
    passButton->setFlat(true);
    passButton->setUpdatesEnabled(false);
    scene->addWidget(passButton);


}

QGraphicsView* MainWindow::getView(){
    return view;
}

QGraphicsScene* MainWindow::getScene(){
    return scene;
}

void MainWindow::setView(QGraphicsView *view){
    this->view = view;
}

void MainWindow::setScene(QGraphicsScene *scene){
    this->scene = scene;
}

MainWindow::~MainWindow(){}

int MainWindow::getPlayerNb(){
    return nbPlayer;
}

void MainWindow::setPlayerNb(int nb){
    this->nbPlayer =nb;
}

void MainWindow::enableButton(bool b){
    for (int i = 0;i<9;i++) {
        for (int o= 0;o<9;o++) {
            matrix[i][o]->setEnabled(b);
        }
    }
    passButton->setEnabled(b);

}

void MainWindow::play(GoPawn *p){
    message[0] = p->getX() + '0';
    message[1] = ',';
    message[2] = p->getY() + '0';
    message[3] = '\000';
    sendto(sock_C, message, 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_S, taille_sa_S);

    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);
    //qDebug() << message;
    if(message[0] != 'o' || message[1] != 'k'){
        updateMap();
        QMessageBox::warning(this,"Invalid Move","Invalid move. It's your turn");
        return;
    }
    if(this->getPlayerNb() == 2){
        qDebug() << "OUI !!";
        matrix[p->getX()][p->getY()]->setIcon(QIcon(QPixmap(":/images/noir.png")));
        matrix[p->getX()][p->getY()]->setIconSize(QSize(40,40));
    }
    else if(this->getPlayerNb() == 1){
        matrix[p->getX()][p->getY()]->setIcon(QIcon(QPixmap(":/images/blanc.png")));
        matrix[p->getX()][p->getY()]->setIconSize(QSize(40,40));
    }

    enableButton(false);
    QMessageBox::information(this,"Wait","The other player is playing");
    updateMap();
    updateMap();
    QMessageBox::information(this,"Your turn","It's your turn");
    enableButton(true);


}

void MainWindow::updateMap(){
    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);
    enableButton(true);
    QString tmp(message);
    if(tmp.contains("stop")){
        enableButton(false);
        QMessageBox::information(this,"END","It's the end of the Game ! You can now count the points");
        return;
    }
    for(int o=0;o<81;o++){
        if(message[o]=='X'){
            matrix[o/9][o%9]->setIcon(QIcon(QPixmap(":/images/noir.png")));
            matrix[o/9][o%9]->setIconSize(QSize(40,40));
        }
        else if(message[o]=='O'){
            matrix[o/9][o%9]->setIcon(QIcon(QPixmap(":/images/blanc.png")));
            matrix[o/9][o%9]->setIconSize(QSize(40,40));
        }
        else if(message[o] == '#'){
            matrix[o/9][o%9]->setIcon(QIcon());
        }
        else{
           // qDebug() << "No symbol ?!";
        }

    }
    this->repaint();
    QString vJ1 = "", vJ2 = "";
    vJ1 += message[2042];
    vJ1 += message[2043];
    vJ1 += message[2044];
    vJ2 += message[2045];
    vJ2 += message[2046];
    vJ2 += message[2047];

    scoreJ1->clear();
    scoreJ1->setText("Nb of white Pawn captured : " + vJ1);
    scoreJ2->clear();
    scoreJ2->setText("Nb of black Pawn captured  : " + vJ2);


    enableButton(false);
}

void MainWindow::passTurn(){
    sendto(sock_C, "pass", 2048 * sizeof(char), 0,
           (struct sockaddr *) &sa_S, taille_sa_S);

    recvfrom(sock_C, message, 2048 * sizeof(char), 0,
             (struct sockaddr *) &sa_S, &taille_sa_S);
    if(message[0] != 'o' || message[1] != 'k'){
        updateMap();
        QMessageBox::warning(this,"Invalid Move","Invalid move. It's your turn");
        return;
    }
    enableButton(false);
    QMessageBox::information(this,"Wait","The other player is playing");
    updateMap();
    updateMap();
    QMessageBox::information(this,"Your turn","It's your turn");
    enableButton(true);

}
