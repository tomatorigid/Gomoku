#include "ai_easy.h"

ai_easy::ai_easy(int n_, bool ai_first_)
{
    n=n_;
    ai_first=ai_first_;
    mb=new board(n);
}
void ai_easy::firstgo(int x, int y){
    //mb->b[y][x]=bw;
    putChess(mb,point(x,y),0);
    calValue(mb,1);
    calValue(mb,0);
}
void ai_easy::go(int x, int y){
    putChess(mb,point(x,y),1);
    calValue(mb,1);
    calValue(mb,0);
}
void ai_easy::get(int *x, int *y){
    calValue(mb,1);
    calValue(mb,0);
    points def=findClosedPoints(mb,1,findMaxValue(mb,1));
    points att=findClosedPoints(mb,0,findMaxValue(mb,0));
    point final=findValuestPoint(mb,def,att);
    putChess(mb,final,0);

    *x=final.x;
    *y=final.y;
}
