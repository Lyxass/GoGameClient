#include "button.h"

Button::Button(const QString &text, QWidget *parent, int x, int y) : QPushButton(text,parent)
{
    QPushButton();
    this->x = x;
    this->y = y;

}

int Button::getX(){
    return x;
}

int Button::getY(){
    return y;
}

void Button::setX(int x){
    this->x = x;
}

void Button::setY(int y){
    this->y = y;
}

QIcon* Button::getImg(){
    return img;
}

void Button::setImg(QIcon* img){
    this->img = img;
}

int Button::getNumJoueur(){
    return numJoueur;
}

void Button::setNumJoueur(int numJoueur){
    this->numJoueur = numJoueur;
}
