#include"chess_five.h"
idiot::idiot(int n,bool h_fir){
    if (n < 12) {
        this->n = 12;
    }
    else {
        this->n = n;
    }
    this->h_fir = h_fir;
    start();
}
idiot::~idiot() {
    delete[] board;
}
bool idiot::go(int x,int y) {
    x=x+1;
    y=y+1;
    if ((!h_fir)||(Winner!=null)||(x < 1) || (x > n) || (y < 1) || (y > n)) {
        return false;
    }
    int index = (y - 1) * n + x - 1;
    if (board[index].has != null) {

        return false;
    }
//	printf("human:[%d,%d]\n", x, y);
    board[index].has = white;
    int updt, starter,ender;
    const int upd[4] = { n - 1,n,n + 1,1 };
    for (int k = 0; k < 4; k++) {
        updt = upd[k];
        starter = index - 4 * updt;
        ender = index + 4 * updt;
        for (int i = starter; i <= ender; i = i + updt) {
            update(i, k);
        }
    }
    h_fir = false;
    return true;
}
bool idiot::get(int* x, int* y) {
    if (h_fir || (Winner != null)) {
        return false;
    }
    int temp = think();
    board[temp].has = black;
    *x = temp % n ;
    *y = (temp / n);
    int updt, starter, ender;
    const int upd[4] = { n - 1,n,n + 1,1 };
    for (int k = 0; k < 4; k++) {
        updt = upd[k];
        starter = temp - 4 * updt;
        ender = temp + 4 * updt;
        for (int i = starter; i <= ender; i = i + updt) {
            update(i, k);
        }
    }
    h_fir = true;
    return true;
}
state idiot::winner() {
    if (Winner == null) {
        return null;
    }
    return Winner;
}
