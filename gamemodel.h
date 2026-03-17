#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include "chess_five.h"
#include "ai_easy.h"

 enum GameType
 {
     AI,
     MAN
 };
 enum GameStatus
 {
     PLAYING,
     WIN,
     DEAD
 };

class GameModel
{
public:
    GameModel();
    int AI_LEVEL=1;
    int BOARD_GRAD_SIZE=15;
    int MARGIN=30;
    int CHESS_RADIUS=15;
    int MARK_SIZE=6;
    int BLOCK_SIZE=40;
    int POS_OFFSET=BLOCK_SIZE*0.4;
    int AI_THINK_TIME=700;
    bool aifirst=1;
public:
    idiot * ai_m;
    ai_easy * ai_e;

    std::vector<std::vector<int>>gameMapVec;
    std::vector<std::vector<int>>scoreMapVec;

    bool playerFlag;

    GameType gameType;
    GameStatus gameStaus;   
    void startGame(GameType type);


    void calculateScore();
    void actionByPerson(int row,int col);
    void actionByAI(int &clickRow,int &clickCol);
    void updateGameMap(int row,int col);
    bool isWin(int row,int col);
    bool isDeadGame();

};

#endif // GAMEMODEL_H
