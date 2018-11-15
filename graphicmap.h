#ifndef GRAPHICMAP_H
#define GRAPHICMAP_H
#include <QWidget>
#include <QPainter>
#include <QTableWidget>
class gamewindow;

class GraphicMap :public QWidget{

//friend class gamewindow;

public:
    GraphicMap(QTableWidget*,class Map*, QWidget* parent=0);
    void paintEvent(QPaintEvent* event);

private:
    Map* map;
    QTableWidget* maptable;

};

#endif // GRAPHICMAP_H
