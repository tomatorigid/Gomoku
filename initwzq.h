#ifndef INITWZQ_H
#define INITWZQ_H

#include <QWidget>
#include <QString>
#include "gamemodel.h"
namespace Ui {
class initwzq;
}

class initwzq : public QWidget
{
    Q_OBJECT

public:
    explicit initwzq(QWidget *parent = 0);
    ~initwzq();
    void get(GameType* mode_,int* board_size_,int* board_gargin_size_,bool* aifirst_,int* ailevel_);
    void start();
    bool isok=0;
private slots:
    void on_start_clicked();

    void on_AI_mode_clicked();

    void on_about_clicked();

private:
    Ui::initwzq *ui;
    GameType* mode;
    int* board_size;
    int* board_gargin_size;
    bool* aifirst;
    int *ailevel;
    QString str="可以选择双人也可以开启AI模式\n"
                "其实不是AI，只是我和同学研究的一个算法\n"
                "难度高的算法是他写的\n"
                "创作于高一";
};

#endif // INITWZQ_H
