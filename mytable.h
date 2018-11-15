#ifndef MYTABLE_H
#define MYTABLE_H
#include <QTableWidget>
#include <QPainter>

class MyTable : public QTableWidget  {

public:
    MyTable(int,int,QWidget* parent=0);

protected:

    void paintEvent(QPaintEvent* event){
        QTableWidget::paintEvent(event);
        QPainter p(this);
    }
};

#endif // MYTABLE_H
