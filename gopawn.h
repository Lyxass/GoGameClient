#pragma once

#ifndef GOPAWN_H
#define GOPAWN_H

#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>


class MainWindow;

class GoPawn : public QPushButton
{
    Q_OBJECT
public:
    GoPawn(int x, int y,MainWindow *window);
    //GoPawn(int x, int y,QString urlj1,QString urlj2);
    void setX(int x);
    void setY(int y);
    void setNumJoueur(int numJoueur);

    int getX();
    int getY();

public slots:
    void clicked();

private:
    int x;
    int y;
    MainWindow *w;
};

#endif // GOPAWN_H
