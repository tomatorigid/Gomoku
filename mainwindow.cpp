#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chess_five.h"
#include"GameModel.h"
#include"ai_easy.h"
#include "initwzq.h"
#include<QPainter>
#include<QMouseEvent>
#include<math.h>
#include<QMessageBox>
#include<QTime>
#include<qtimer.h>
#include<iostream>
#include<QPixmap>
#include<QWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->hide();

    ui->setupUi(this);
  setMouseTracking(true);
  this->hide();
    game = new GameModel;
    //设置窗口大小
    setFixedSize(

              (game->MARGIN)*2+(game->BLOCK_SIZE)*(game->BOARD_GRAD_SIZE),
              (game->MARGIN)*2+(game->BLOCK_SIZE)*(game->BOARD_GRAD_SIZE)
              );

    this->hide();

           initGame();
}
void MainWindow::check(){
    if(game->gameType==AI){
    int flag;
    if(game->AI_LEVEL==1){
        flag=game->ai_m->winner();
        if(game->aifirst==1){
            if(flag==black){
                flag=white;
            }
            else if(flag==white){
                flag=black;
            }

        }
    }
    else if(game->AI_LEVEL==0)
        flag=game->ai_e->winner();
    //else if(game->AI_LEVEL==2)
        //flag=game->ai_h->winner();
    if(flag==black){
        //update();
        QMessageBox::information(this, "五子棋", " 白棋胜利!");
        this->~MainWindow();
    }
    else if(flag==white){
        //update();
        QMessageBox::information(this, "五子棋"," 黑棋胜利!");
        this->~MainWindow();
    }
    }
    if(game->gameType==MAN)
 {
 //判断输赢
    if (clickPosRow > 0 && clickPosRow < game->BOARD_GRAD_SIZE &&
         clickPosCol > 0 && clickPosCol < game->BOARD_GRAD_SIZE &&
    (
         game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
         game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
      if (game->isWin(clickPosRow, clickPosCol) && game->gameStaus==PLAYING)
    {
               game->gameStaus = WIN;
             //QSound::play(":sound/win.wav");
    QString str;
      if  (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                 str ="黑棋";

    else if  (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str ="白棋";
      QMessageBox::StandardButton btnValue =QMessageBox::information(this, "五子棋决战", str + " 胜利!");
      if (btnValue == QMessageBox::Ok)
      {
             //game->startGame(game_type);
             //game->gameStaus = PLAYING;
             this->~MainWindow();
         }
      }
      }

 }

}
MainWindow::~MainWindow()
{
    delete game;
    delete ui;
}
//绘制棋盘
void MainWindow::paintEvent(QPaintEvent *event)
{
   QPixmap pixmap = QPixmap(":/wooden_2.bmp").scaled(this->size());
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.drawPixmap(this->rect(), pixmap);
   for(int i=0;i<=(game->BOARD_GRAD_SIZE);i++)
   {
       //shu
       painter.drawLine(game->MARGIN+(game->BLOCK_SIZE)*i,game->MARGIN,
                        game->MARGIN+(game->BLOCK_SIZE)*i,size().height()-game->MARGIN);
       //heng
       painter.drawLine(game->MARGIN,game->MARGIN+(game->BLOCK_SIZE)*i,
                        size().width()-game->MARGIN,game->MARGIN+(game->BLOCK_SIZE)*i);
 }
   //绘制选中点
   QBrush brush;
   brush.setStyle(Qt::SolidPattern);

   if (clickPosRow>0&&clickPosRow<(game->BOARD_GRAD_SIZE)&&
       clickPosCol>0&&clickPosCol<(game->BOARD_GRAD_SIZE)&&
       game->gameMapVec[clickPosRow][clickPosCol]==0)
   {
       if (game->playerFlag)
           brush.setColor(Qt::black);
       else
           brush.setColor(Qt::white);
       painter.setBrush(brush);
      painter.drawRect(game->MARGIN+(game->BLOCK_SIZE)*clickPosCol-(game->MARK_SIZE)/2,game->MARGIN+(game->BLOCK_SIZE)*clickPosRow-(game->MARK_SIZE)/2,6,6);
   }
//绘制棋子
   for (int i=0;i<(game->BOARD_GRAD_SIZE);i++)
       for (int j=0;j<(game->BOARD_GRAD_SIZE);j++)
       {
           if (game->gameMapVec[i][j]==1)
           {
               brush.setColor(Qt::black);

               painter.setBrush(brush);
               painter.drawEllipse(game->MARGIN+(game->BLOCK_SIZE)*j-game->CHESS_RADIUS,game->MARGIN+game->BLOCK_SIZE*i-game->CHESS_RADIUS,24,24);

           }

           else if (game->gameMapVec[i][j]==-1)
           {
               brush.setColor(Qt::white);

               painter.setBrush(brush);
               //painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,24,24);
               //painter.drawEllipse(game->MARGIN+(game->BLOCK_SIZE)*j-game->CHESS_RADIUS,game->MARGIN+game->BLOCK_SIZE*i-game->CHESS_RADIUS,24,24);
                painter.drawEllipse(game->MARGIN+(game->BLOCK_SIZE)*j-game->CHESS_RADIUS,game->MARGIN+game->BLOCK_SIZE*i-game->CHESS_RADIUS,24,24);
           }
        }
   if(game->gameType==MAN)
{
//判断输赢
   if (clickPosRow > 0 && clickPosRow < game->BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosCol < game->BOARD_GRAD_SIZE &&
   (
        game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
        game->gameMapVec[clickPosRow][clickPosCol] == -1))
   {
     if (game->isWin(clickPosRow, clickPosCol) && game->gameStaus==PLAYING)
   {
              game->gameStaus = WIN;
            //QSound::play(":sound/win.wav");
   QString str;
     if  (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str ="黑棋";

   else if  (game->gameMapVec[clickPosRow][clickPosCol] == -1)
               str ="白棋";
     QMessageBox::StandardButton btnValue =QMessageBox::information(this, "五子棋决战", str + " 胜利!");
     if (btnValue == QMessageBox::Ok)
     {
            //game->startGame(game_type);
            //game->gameStaus = PLAYING;
            this->~MainWindow();
        }
     }
     }

}

}
void MainWindow::initGame()
{
    //game = new GameModel;
    this->hide();
    initAIGame();
}

   void MainWindow::initAIGame()
{
       initwzq* in=new initwzq();
       in->get(&(game->gameType),&(game->BOARD_GRAD_SIZE),&(game->MARGIN),&(game->aifirst),&(game->AI_LEVEL));
       in->start();
       while(!(in->isok)){
           QEventLoop loop;
           QTimer::singleShot(10,&loop,SLOT(quit()));
           loop.exec();
       }
       delete in;

       if(game->gameType==MAN){
           setWindowTitle("游戏中，PVP");
       }
       else{
           setWindowTitle(("游戏中"));
       }
       this->show();
       game_type=game->gameType;
       game->gameStaus=PLAYING;
       game->startGame(game_type);
       //update();
       if(game->aifirst&&game->gameType==AI){
            game->updateGameMap(game->BOARD_GRAD_SIZE/2,game->BOARD_GRAD_SIZE/2);
            if(game->AI_LEVEL==1)
                game->ai_m->go(game->BOARD_GRAD_SIZE/2,game->BOARD_GRAD_SIZE/2);
            else if(game->AI_LEVEL==0)
                game->ai_e->firstgo(game->BOARD_GRAD_SIZE/2,game->BOARD_GRAD_SIZE/2);
            //else if(game->AI_LEVEL==2)
                //game->ai_h->go(game->BOARD_GRAD_SIZE/2,game->BOARD_GRAD_SIZE/2);
       }
       roletimer=new QTimer;
       roletimer->start(1000/20);
       connect(roletimer,&QTimer::timeout,this,&MainWindow::check);

   }

   void MainWindow:: mouseMoveEvent(QMouseEvent*event)
 {
   int x=event->x();
   int y=event->y();
 if (x>=game->MARGIN + (game->BLOCK_SIZE)/2 &&
   x< size().width()-game->MARGIN -(game->BLOCK_SIZE)/2 &&
   y>=game->MARGIN+(game->BLOCK_SIZE)/2&&
   y<size().height()-game->MARGIN-(game->BLOCK_SIZE)/2)
{
     int col=(x-game->MARGIN)/(game->BLOCK_SIZE);
     int row=(y-game->MARGIN)/(game->BLOCK_SIZE);

   int leftTopPosX=game->MARGIN+(game->BLOCK_SIZE)*col;
   int leftTopPosY=game->MARGIN+(game->BLOCK_SIZE)*row;

   clickPosRow=-1;
   clickPosCol=-1;
   int len=0;

   selectPos=false;

   len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
   if(len<(game->POS_OFFSET))
   {
       clickPosRow=row;
       clickPosCol=col;
       if(game->gameMapVec[clickPosRow][clickPosCol]==0)
       {
           selectPos=true;
       }
 }
    len=sqrt((x-leftTopPosX-game->BLOCK_SIZE)*(x-leftTopPosX-game->BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));

 if(len<(game->POS_OFFSET))
 {
     clickPosRow=row;
     clickPosCol=col+1;
     if(game->gameMapVec[clickPosRow][clickPosCol]==0)
     {
         selectPos=true;
     }
 }
   len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-game->BLOCK_SIZE)*(y-leftTopPosY-game->BLOCK_SIZE));

if(len<(game->POS_OFFSET))
{
    clickPosRow=row+1;
    clickPosCol=col;
    if(game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        selectPos=true;
    }
}
  len=sqrt((x-leftTopPosX-game->BLOCK_SIZE)*(x-leftTopPosX-game->BLOCK_SIZE)+(y-leftTopPosY-game->BLOCK_SIZE)*(y-leftTopPosY-game->BLOCK_SIZE));

if(len<(game->POS_OFFSET))
{
    clickPosRow=row+1;
    clickPosCol=col+1;
    if(game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        selectPos=true;
    }
}

 }
   update();
   //判断输赢
      if (clickPosRow > 0 && clickPosRow < game->BOARD_GRAD_SIZE &&
           clickPosCol > 0 && clickPosCol < game->BOARD_GRAD_SIZE &&
      (
           game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
           game->gameMapVec[clickPosRow][clickPosCol] == -1))
      {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStaus==PLAYING)
      {
                 game->gameStaus = WIN;
               //QSound::play(":sound/win.wav");
      QString str;
        if  (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                   str ="黑棋";

      else if  (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                  str ="白棋";
        QMessageBox::StandardButton btnValue =QMessageBox::information(this, "五子棋决战", str + " 胜利!");
        if (btnValue == QMessageBox::Ok)
        {
               //game->startGame(game_type);
               //game->gameStaus = PLAYING;
               this->~MainWindow();
           }
        }
        }

   }
//落子
void MainWindow::mouseReleaseEvent(QMouseEvent*event)
{
    if(selectPos==false)
        return;
    else
        selectPos=false;
    chessOneByPerson();
}
void MainWindow::chessOneByPerson()
{
    if (clickPosRow!=-1&&clickPosCol!=-1&&game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        game->actionByPerson(clickPosRow,clickPosCol);

        update();
    }
}
