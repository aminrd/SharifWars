#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include <QWidget>
#include <QDesktopWidget>
#include <QTimer>

class StartWindow : public QDesktopWidget{

    Q_OBJECT

public:
    StartWindow(QWidget*,QWidget* parent=0);
    ~StartWindow();
    QTimer* timer;

private:
    QWidget* q;

public slots:
    void Exit();


};

#endif // STARTWINDOW_H
