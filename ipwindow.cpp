#include "ipwindow.h"

IpWindow::IpWindow()
{
    setFixedSize(300,100);
    ip1 = new QLineEdit();
    ip2 = new QLineEdit();
    ip3 = new QLineEdit();
    ip4 = new QLineEdit();

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(new QLabel("Please, enter the server's ip address"),0,0,1,7);
    lay->addWidget(ip1,1,0);
    lay->addWidget(new QLabel("."),1,1);
    lay->addWidget(ip2,1,2);
    lay->addWidget(new QLabel("."),1,3);
    lay->addWidget(ip3,1,4);
    lay->addWidget(new QLabel("."),1,5);
    lay->addWidget(ip4,1,6);

    bt = new QPushButton("ok");
    lay->addWidget(bt,2,6);

    ip1->setValidator(new QIntValidator(0, 255, this));
    ip2->setValidator(new QIntValidator(0, 255, this));
    ip3->setValidator(new QIntValidator(0, 255, this));
    ip4->setValidator(new QIntValidator(0, 255, this));

    QObject::connect(bt,&QPushButton::clicked,this,&IpWindow::onClicked);
    erreur = 0;

    ip = new QString();

    this->setLayout(lay);

}

void IpWindow::onClicked(){
    int w,x,y,z;

    w = QString(ip1->text()).toInt(NULL,10);
    x = QString(ip1->text()).toInt(NULL,10);
    y = QString(ip1->text()).toInt(NULL,10);
    z = QString(ip1->text()).toInt(NULL,10);

    if(w>255 || w<0 ||x>255 || x<0 || y>255 || y<0 || z>255 || z<0 ){
        QMessageBox::warning(this,"IP invalid","Wrong Ip address");
        this->close();
        erreur = 1;
        return;
    }
    else{
        erreur = 0;
        this->close();
        *ip = QString::number(w) + QString(".") +QString::number(x) + QString(".") +QString::number(y) + QString(".") +QString::number(z);
    }
}

QString IpWindow::getIp(){
    return *ip;
}

bool IpWindow::getError(){
        return erreur;
}
