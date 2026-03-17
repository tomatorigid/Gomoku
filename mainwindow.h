#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"GameModel.h"
#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameModel *game;
    GameType game_type;

    int clickPosRow,clickPosCol;
    bool selectPos = false;

    void paintEvent(QPaintEvent*event);
    void initGame();
    void initAIGame();

    void mouseMoveEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);

    void chessOneByPerson();
    void chessOneByAI();

    void check();

    QTimer * roletimer;
};

#endif // MAINWINDOW_H
