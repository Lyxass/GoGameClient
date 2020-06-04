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
    this->blackPawn = QIcon("/home/lyxas/GoGameCleintGui/noir.png");
    this->whitePawn = QIcon("/home/lyxas/GoGameCleintGui/blanc.png");

    QPixmap *img = new QPixmap("/home/lyxas/GoGameCleintGui/Goban_9x9_.png");
    scene->addPixmap(*img);
    this->view= new QGraphicsView(scene);
    int offsetx = 0;
    int offsety = 0;
    int x = 0;
    int y = 0;
    offsety = -8;
    for(int i=0; i<9; i++){
        x = 0;
        offsetx = -8;
        for(int o=0;o<9;o++){
           matrix[i][o] =new GoPawn(i,o,this);
           matrix[i][o]->setMinimumSize(QSize(1,1));
            x+=1;
            matrix[i][o]->setGeometry(x+offsetx,y+offsety,45,45);
            offsetx +=49;
            if(i%2 == 0){
                if(o%2 == 0){
                    matrix[i][o]->setStyleSheet("background-color: rgba(255, 25, 255, 0.2);");
                }
                else{
                    matrix[i][o]->setStyleSheet("background-color: rgba(25, 255, 255, 0.2);");
                }
            }
            else{
                if(o%2 == 0){
                    matrix[i][o]->setStyleSheet("background-color: rgba(25, 255, 255, 0.2);");
                }
                else{
                    matrix[i][o]->setStyleSheet("background-color: rgba(255, 25, 255, 0.2);");
                }
            }
            matrix[i][o]->setFlat(true);
            matrix[i][o]->setUpdatesEnabled(false);
            scene ->addWidget(matrix[i][o]);
        }
        y += 1;
        offsety += 49;


    }

    scoreJ1 = new GoLabel();
    scoreJ2 = new GoLabel();

    scoreJ1->setStyleSheet("background-color: rgba(255, 255, 255, 0.0);");
    scoreJ2->setStyleSheet("background-color: rgba(255, 255, 255, 0.0);");

    scoreJ1->setText(QString("Nb J1 : 0"));
    scoreJ2->setText(QString("Nb  J2 : 0"));

    scoreJ1->setGeometry(0,429,429,20);
    scoreJ2->setGeometry(0,450,429,20);
    scene->addWidget(scoreJ1);
    scene->addWidget(scoreJ2);
    QPushButton test("Skip your turn");
    scene->addWidget(&test);

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
}

void MainWindow::play(GoPawn *p){
    message[0] = p->getX() + '0';
    message[1] = ',';
    message[2] = p->getY() + '0';
    message[3] = '\000';
    qDebug() << message << endl;
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
        matrix[p->getX()][p->getY()]->setIcon(QIcon(QPixmap("/home/lyxas/GoGameCleintGui/noir.png")));
    }
    else if(this->getPlayerNb() == 1){
        matrix[p->getX()][p->getY()]->setIcon(QIcon(QPixmap("/home/lyxas/GoGameCleintGui/blanc.png")));
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
    qDebug() << message;
    for(int o=0;o<81;o++){
        if(message[o]=='X'){
            matrix[o/9][o%9]->setIcon(QIcon(QPixmap("/home/lyxas/GoGameCleintGui/noir.png")));
           // matrix[o/9][o%9]->setIconSize(QSize(20,20));
        }
        else if(message[o]=='O'){
            matrix[o/9][o%9]->setIcon(QIcon(QPixmap("/home/lyxas/GoGameCleintGui/blanc.png")));
            //matrix[o/9][o%9]->setIconSize(QSize(20,20));
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
    qDebug() << vJ1;

    vJ2 += message[2045];
    vJ2 += message[2046];
    vJ2 += message[2047];
    qDebug() << vJ1;
    scoreJ1->clear();
    scoreJ1->setText("Nb Pawn captured by J1 : " + vJ1);
    scoreJ2->clear();
    scoreJ2->setText("Nb Pawn captured by J2 : " + vJ2);


    enableButton(false);
}

