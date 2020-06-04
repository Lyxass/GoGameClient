#ifndef GOPASSBUTTON_H
#define GOPASSBUTTON_H


#include <QPushButton>

class MainWindow;

class GoPassButton : public QPushButton
{
    Q_OBJECT
public:
    GoPassButton(QString str, QWidget *parent,MainWindow *window);

public slots:
    void onClicked();

private:
    MainWindow *w;
};

#endif // GOPASSBUTTON_H
