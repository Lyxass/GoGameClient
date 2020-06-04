#ifndef BUTTON_H
#define BUTTON_H

#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QPushButton>
#include "mainwindow.h"

class Button : public QPushButton
{

public:
    Button(const QString& text, QWidget* parent = 0,int x =0,int y = 0);
    void setX(int x);
    void setY(int y);
    void setNumJoueur(int numJoueur);
    void setImg(QIcon *img);

    int getX();
    int getY();
    int getNumJoueur();
    QIcon* getImg();

private:
    int x;
    int y;
    QIcon *img;
    int numJoueur;
};

#endif // BUTTON_H
