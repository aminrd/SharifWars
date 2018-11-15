#include "endgame.h"
#include <cstdio>
#include <QApplication>
#include <QPoint>
#include <cstdlib>

EndGame::EndGame(int winner, QWidget* parent) : QWidget() {

    char str[100];
    Quit=new QPushButton("Quit",this);
    sprintf(str,"Team %d is winner",winner);
    label=new QLabel(str,this);

    this->resize(400,300);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QRect rect=QApplication::desktop()->screenGeometry();
    QPoint point=rect.center();
    point.setX(point.x()-this->width()/2);
    point.setY(point.y()-this->height()/2);
    this->move(point);

    QPalette p = palette();
    QPixmap pixmap1("start/3.jpg");
    QSize size(400,300);
    QPixmap pixmap(pixmap1.scaled(size));
    p.setBrush(QPalette::Background,  pixmap);
    setPalette(p);

    connect(Quit,SIGNAL(clicked()),this,SLOT(Exit()));

    QFont f("Arial", 16, QFont::Bold);
    label->setStyleSheet("QLabel { color : rgb(220,220,50); }");
    label->setFont(f);
    label->move(122,202);
    Quit->move(162,250);

}




void EndGame::Exit(){
    exit(0);
}
