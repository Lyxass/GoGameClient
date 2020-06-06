#ifndef IPWINDOW_H
#define IPWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QLayout>
#include <QIntValidator>
#include <QPushButton>

class IpWindow : public QDialog
{
public:
    IpWindow();
    QString getIp();
    bool getError();

public slots:
    void onClicked();

private:
    bool erreur;
    QLineEdit *ip1;
    QLineEdit *ip2;
    QLineEdit *ip3;
    QLineEdit *ip4;
    QLabel *point;
    QString *ip;
    QPushButton *bt;
};

#endif // IPWINDOW_H
