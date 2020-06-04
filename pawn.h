#ifndef PAWN_H
#define PAWN_H


#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>


class Pawn : public QPushButton
{
    Q_OBJECT
public:
    Pawn(int x, int y);
    void setX(int x);
    void setY(int y);
    void setNumJoueur(int numJoueur);
    void setImg(QIcon *img);

    int getX();
    int getY();
    int getNumJoueur();
    QIcon* getImg();
public slots:
    void changePicture();
private:
    int x;
    int y;
    QIcon *imgJ1;
    QIcon *imgJ2;
    int numJoueur;
};

#endif // PAWN_H
