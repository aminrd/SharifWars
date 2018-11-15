#ifndef ENDGAME_H
#define ENDGAME_H
#include <QWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>

class EndGame : public QWidget{

    Q_OBJECT
public:
    EndGame(int,QWidget* parent=0);

private:
    QPushButton* Quit;
    QLabel* label;

public slots:
    void Exit();


};

#endif // ENDGAME_H
