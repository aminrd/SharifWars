#include "startwindow.h"
#include <QRect>
#include <QPoint>
#include <QApplication>
#include <cstdio>
#include <cstdlib>
#include <QIcon>
#include <windows.h>


StartWindow::StartWindow(QWidget* _q, QWidget* parent): QDesktopWidget(){

    q=_q;
    this->resize(600,500);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QRect rect=QApplication::desktop()->screenGeometry();
    QPoint point=rect.center();
    point.setX(point.x()-this->width()/2);
    point.setY(point.y()-this->height()/2);
    this->move(point);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Exit()));
    timer->start(2200);
    QIcon icon("start/2.jpg");
    this->setWindowIcon(icon);

    QPalette p = palette();
    QPixmap pixmap1("start/2.jpg");
    QSize size(600,500);
    QPixmap pixmap(pixmap1.scaled(size));
    p.setBrush(QPalette::Background,  pixmap);
    setPalette(p);

}

void StartWindow::Exit(){
    this->close();
    q->showMaximized();
}

StartWindow::~StartWindow(){

}
