#include "initwzq.h"
#include "ui_initwzq.h"
#include <QMessageBox>
initwzq::initwzq(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::initwzq)
{
    ui->setupUi(this);
    ui->AI_first->hide();
    ui->ai_level->hide();
    ui->label_ailevel->hide();
    setWindowTitle("开始游戏");
}

initwzq::~initwzq()
{
    delete ui;
}
void initwzq::get(GameType *mode_, int *board_size_, int *board_gargin_size_, bool *aifirst_, int *ailevel_){
    mode=mode_;
    board_size=board_size_;
    board_gargin_size=board_gargin_size_;
    aifirst=aifirst_;
    ailevel=ailevel_;
}
void initwzq::start(){
    this->show();

}

void initwzq::on_start_clicked()
{
    if(ui->AI_mode->isChecked()){
        *mode=AI;
    }
    else{
        *mode=MAN;
    }
    *aifirst=ui->AI_first->isChecked();
    *board_size=ui->board_size->value()+1;
    *board_gargin_size=ui->board_margin_size->value();
    *ailevel=ui->ai_level->value()-1;
    isok=1;
    this->hide();
    //this->~initwzq();
}

void initwzq::on_AI_mode_clicked()
{
    if(ui->AI_mode->isChecked()){
        ui->AI_first->show();
        ui->ai_level->show();
        ui->label_ailevel->show();
    }
    else{
        ui->AI_first->hide();
        ui->ai_level->hide();
        ui->label_ailevel->hide();
    }
}

void initwzq::on_about_clicked()
{
    QMessageBox::information(this, "about", str);
}
