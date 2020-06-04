#include "gopawn.h"
#include "mainwindow.h"


void GoPawn::clicked(){
    w->play(this);
}


GoPawn::GoPawn(int x,int y, MainWindow *window){
    this->x = x;
    this->y = y;
    QObject::connect(this, &QPushButton::clicked, this, &GoPawn::clicked);
    this->w = window;
}

void GoPawn::setX(int x){
    this->x = x;
}
void GoPawn::setY(int y){
    this->y = y;
}


int GoPawn::getX(){
    return x;
}
int GoPawn::getY(){
    return y;
}




