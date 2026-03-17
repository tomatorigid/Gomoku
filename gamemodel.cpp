#include"GameModel.h"
GameModel::GameModel()
{


}
void GameModel::startGame(GameType type)
{
    gameType=type;

    gameMapVec.clear();
    for (int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int> lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
         }
if (gameType==AI)
{
    scoreMapVec.clear();
    for (int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int> linescores;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            linescores.push_back(0);
        gameMapVec.push_back(linescores);
  }
}

    playerFlag=true;
    /*
    int tx,ty;
    if(gameType==AI){
        if(aifirst==1){
        ai->get(&tx,&ty);
        updateGameMap(tx,ty);
        }
    }
    */

    if(gameType==AI){
        ai_m=new idiot(BOARD_GRAD_SIZE-1,!aifirst);
        ai_e=new ai_easy(BOARD_GRAD_SIZE-1,aifirst);
    }
}

void GameModel::actionByPerson(int row, int col)
{
    int tx=row,ty=col;
    updateGameMap(row,col);
    if(gameType==AI){
        if(AI_LEVEL==0){
            ai_e->go(tx-1,ty-1);
            ai_e->get(&tx,&ty);
            tx+=1;
            ty+=1;
        }
        else if(AI_LEVEL==1){
            ai_m->go(tx-1,ty-1);
            ai_m->get(&tx,&ty);
            tx+=1;
            ty+=1;
        }/*
        else if(AI_LEVEL==2){
            ai_h->go(tx,ty);
            ai_h->get(&tx,&ty);
        }*/
        updateGameMap(tx,ty);
    }

}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col]=1;
    else
        gameMapVec[row][col]=-1;

    playerFlag=!playerFlag;

}

bool GameModel::isWin(int row, int col)
{
    for (int i = 0; i < 5; i++)
    {
        if (col - i > 0 &&col - i + 4 < BOARD_GRAD_SIZE &&
        gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
        gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
        gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
        gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
        return true;
}
    for (int i = 0; i < 5; i++)
    {
    if (row - i > 0 &&
        row - i + 4 < BOARD_GRAD_SIZE &&
        gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
        gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
        gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
        gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
        return true;
}
    for (int i = 0; i < 5; i++)
    {
    if (row + i <BOARD_GRAD_SIZE&&
            row + i - 4 > 0 &&
            col - i > 0 &&
            col - i + 4 <BOARD_GRAD_SIZE&&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col- i + 1] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col- i + 2] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col- i + 3] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col- i + 4] )

        return true;
    }

    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&row - i + 4 <BOARD_GRAD_SIZE&&col - i > 0 &&col - i + 4 <BOARD_GRAD_SIZE&&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col-i + 1] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col-i + 2] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col-i + 3] &&
                gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col-i + 4])

            return true;
    }
                return false;
}









