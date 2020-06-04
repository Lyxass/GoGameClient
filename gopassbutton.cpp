#include "gopassbutton.h"
#include "mainwindow.h"

GoPassButton::GoPassButton(QString str, QWidget *parent,MainWindow *window)
{
    this->setText(str);
    w = window;
    QObject::connect(this,&QPushButton::clicked,this,&GoPassButton::onClicked);
}


void GoPassButton::onClicked(){
    w->passTurn();
}
