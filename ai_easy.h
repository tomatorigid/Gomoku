#ifndef AI_EASY_H
#define AI_EASY_H

#include <windows.h>
#define bm '+'
#define bb 'X'
#define bw 'O'
typedef signed char bt;
struct point
{
    int x,y;
    point(int x_,int y_)
    {
        x=x_;
        y=y_;
    }
    point()
    {
        point(0,0);
    }
};
struct board
{
    int n=0;//width and length
    char b[100][100]= {}; //board value
    int def[100][100]= {}; //defend value
    int att[100][100]= {}; //attack value
    board(int n_)
    {
        n=n_;
        for(int i=0; i<(n); i++)for(int j=0; j<(n); j++)b[i][j]=bm;
    }
    board()
    {
        board(0);
    }
};
struct points
{
    int n=0;
    point P[10000];
    points(int n_)
    {
        n=n_;
    }
    points()
    {
        points(0);
    }
};

class ai_easy
{
private:
    bt iswin=-1;
    int findmaxint(int a,int b,int c,int d)
    {
        a=a>b?a:b;
        c=c>d?c:d;
        return a>c?a:c;
    }
    int max(int a,int b){return a>b?a:b;}
    int n;
    bool ai_first;
    void putChess(board* mb,point P,bool flag/*machine is white(0),human is black(1)*/)
    {
        if(mb->b[P.y][P.x]==bm)
            mb->b[P.y][P.x]=flag?bb:bw;
        else
            MessageBox(0,L"用户尝试落子于已有位置",L"错误",0);
    }
    bt helpCalLine(board* mb,point P,bt a,bt b,bool flag)
    {
        bt mbt1=0,mbt2=0,tx,ty;
        //cout<<"flag:"<<(flag?'@':'0')<<endl;
        for(int i=-4; i<=0; i++)
        {
            tx=P.x+b*i;
            ty=P.y+a*i;
            //cout<<(int)tx<<" "<<(int)ty<<";";
            if(ty<0||ty>(mb->n-1)||tx<0||tx>(mb->n-1))
                continue;
            if(mb->b[ty][tx]==(flag?bw:bb)){
                mbt1=0;continue;
            }
            if(mb->b[ty][tx]==(flag?bb:bw))
                ++mbt1;

        }
        for(int i=4; i>=0; i--)
        {
            tx=P.x+b*i;
            ty=P.y+a*i;
            //cout<<(int)tx<<" "<<(int)ty<<";";
            if(ty<0||ty>(mb->n-1)||tx<0||tx>(mb->n-1))
                continue;
            if(mb->b[ty][tx]==(flag?bw:bb)){
                mbt2=0;continue;
            }
            if(mb->b[ty][tx]==(flag?bb:bw))
                ++mbt2;

        }
        bt mbt=max(mbt1,mbt2);
        if(mbt>=5)
        {
            //MessageBox(0,flag?"人类胜利":"机器胜利","游戏结束",0);
            iswin=flag?1:0;
        }
        return mbt;
    }
    void calValue(board* mb,bool flag/*calculate the defend(1)/attack(0) value,*/)
    {
        for(int i=0; i<(mb->n); i++)
        {
            for(int j=0; j<(mb->n); j++)
            {
                //int temp=helpCalLine(mb,point(j,i),0,1,flag)+
                //    helpCalLine(mb,point(j,i),1,0,flag)+
                //    helpCalLine(mb,point(j,i),1,1,flag)+
                //    helpCalLine(mb,point(j,i),-1,1,flag);
                int temp=findmaxint(helpCalLine(mb,point(j,i),0,1,flag),helpCalLine(mb,point(j,i),1,0,flag),helpCalLine(mb,point(j,i),1,1,flag),helpCalLine(mb,point(j,i),-1,1,flag));
                //cout<<"temp:"<<temp<<endl;
                if(mb->b[i][j]!=bm)
                {
                    temp=-temp;
                    //cout<<"qin ling:"<<j<<","<<i<<endl;
                }

                if(flag)
                    mb->def[i][j]=temp;
                else
                    mb->att[i][j]=temp;

            }
        }
    }
    points findClosedPoints(board* mb,bool flag,points Ps)
    {
        points nps;//new points
        for(int i=0; i<(Ps.n); i++)
        {
            if(mb->b[Ps.P[i].y][Ps.P[i].x+1]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y][Ps.P[i].x-1]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y+1][Ps.P[i].x]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y-1][Ps.P[i].x]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y+1][Ps.P[i].x+1]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y+1][Ps.P[i].x-1]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y-1][Ps.P[i].x+1]==(flag?bb:bw)
                    ||mb->b[Ps.P[i].y-1][Ps.P[i].x-1]==(flag?bb:bw))
            {
                nps.P[nps.n++]=Ps.P[i];
            }
        }
        if(nps.n==0){
            nps.P[nps.n++]=Ps.P[0];
        }
        return nps;
    }
    points findIntersection(board* mb,points A,points B)
    {
        points nps;
        bool flag=0;
        for(int i=0; i<A.n; i++)
        {
            for(int j=0; j<B.n; j++)
            {
                if(A.P[i].x==B.P[j].x&&A.P[i].y==B.P[j].y)
                {
                    for(int k=0; k<nps.n; k++)
                    {
                        if(nps.P[k].x==A.P[i].x&&nps.P[k].y==A.P[i].y)
                        {
                            flag=1;
                        }
                    }
                    if(flag)
                    {
                        flag=0;
                        continue;
                    }
                    else
                    {
                        if(mb->b[A.P[i].y][A.P[i].x]!=bm)
                            continue;
                        nps.P[nps.n++]=A.P[i];
                    }
                }

            }
        }
        if(nps.n==0)
            nps.P[nps.n++]=A.P[0];
        return nps;
    }
    points findMaxValue(board* mb,bool flag/*calculate the defend(1)/attack(0) value,*/,points Ps)
    {
        points Ps_;
        bt maxValue=0;
        for(int i=0; i<=Ps.n; i++)
        {
            bt x=Ps.P[i].x,y=Ps.P[i].y;
            bt temp=(flag?(mb->def[y][x]):(mb->att[y][x]));
            if(temp>maxValue)
            {
                maxValue=temp;
            }
        }
        for(int i=0; i<=Ps.n; i++)
        {
            bt x=Ps.P[i].x,y=Ps.P[i].y;
            bt temp=(flag?(mb->def[y][x]):(mb->att[y][x]));
            if(temp=maxValue)
            {
                Ps_.P[Ps_.n++]=Ps.P[i];
            }
        }

        return Ps_;
    }
    points findMaxValue(board* mb,bool flag/*calculate the defend(1)/attack(0) value,*/)
    {
        point maxPoint;
        bt maxValue=0;
        points Ps;
        for(int i=0; i<(mb->n); i++)
        {
            for(int j=0; j<(mb->n); j++)
            {
                if((flag?(mb->def[i][j]):(mb->att[i][j]))>maxValue)
                {
                    maxPoint=point(j,i);
                    maxValue=(flag?(mb->def[i][j]):(mb->att[i][j]));
                }
            }
        }
        for(int i=0; i<(mb->n); i++)
            for(int j=0; j<(mb->n); j++)
                if((flag?(mb->def[i][j]):(mb->att[i][j]))==maxValue)
                    Ps.P[Ps.n++]=point(j,i);
        return Ps;
    }
    points helpfindValuestPoint(board* mb,points Ps,bool flag){
        bt temp[100],j=0;
        points tp;
        for(int i=0;i<Ps.n;i++){
            temp[i]=helpCalLine(mb,Ps.P[i],0,1,flag)+helpCalLine(mb,Ps.P[i],1,0,flag)+helpCalLine(mb,Ps.P[i],1,1,flag)+helpCalLine(mb,Ps.P[i],-1,1,flag);
        }
        for(int i=0;i<Ps.n;i++){
            if(temp[i]>temp[j]){
                j=i;
            }
        }
        for(int i=0;i<Ps.n;i++){
            if(temp[i]==temp[j]){
                tp.P[tp.n++]=Ps.P[i];
            }
        }
        return tp;
    }
    point findValuestPoint(board* mb,points def,points att){
        int defMax=mb->def[def.P[0].y][def.P[0].x];
        int attMax=mb->att[att.P[0].y][att.P[0].x];
        if(defMax==3&&attMax<4){
            return def.P[0];
            //return helpfindValuestPoint(mb,def,1).P[0];
        }
        if(defMax<=attMax){
            return att.P[0];
            //return helpfindValuestPoint(mb,att,0).P[0];
        }
        else{
            return def.P[0];
            //return helpfindValuestPoint(mb,def,1).P[0];
        }
    }
    board* mb;
    int times=0;
public:
    ai_easy(int n_,bool ai_first_);
    void go(int x,int y);
    void get(int *x,int *y);
    bt winner(){return iswin;}
    void firstgo(int x,int y);
};

#endif // AI_EASY_H
