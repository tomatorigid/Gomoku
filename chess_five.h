#ifndef CHESS_FIVE_H
#define CHESS_FIVE_H
enum state { null = -1, black = 0, white = 1 };
class idiot {
private:
    bool h_fir, started = false;
    int n, len;
    state Winner=null;
    void update(int index, int edge = -1) {
        int temp=0;
        if (index < 0 || index >= len) {
            return;
        }
        switch (edge) {
        case -1:
            for (int i = 0; i < 4; i++) {
                update(index, i);
            }
            return;

        case 0:
            temp = n - 1;
            break;
        case 1:
            temp = n;
            break;
        case 2:
            temp = n + 1;
            break;
        case 3:
            temp = 1;
            break;
        }
        if (board[index].dead[edge]) {
            return;
        }
        for (int i = 0; i < 5; i++) {
            dott[i] = &board[index];
            index = index + temp;
        }
        int Black = 0, White = 0, Null = 0;
        bool emp[5] = { false };
        for (int i = 0; i < 5; i++) {
            switch (dott[i]->has) {
            case black:
                Black++;
                break;
            case white:
                White++;
                break;
            default:
                emp[i] = true;
            }
        }
        if (Black == 5) {
            Winner = black;
            return;
        }
        if (White == 5) {
            Winner = white;
            return;
        }
        if (Black == 0) {
            temp = 4 - White;
            for (int i = 0; i < 5; i++) {
                if (emp[i]) {
                    dott[i]->w_threat[temp]++;
                    if (started) {
                        dott[i]->w_threat[dott[0]->w_last[edge]]--;
                    }
                }
            }
            dott[0]->w_last[edge] = temp;
        }
        if (White == 0) {
            temp = 4 - Black;
            for (int i = 0; i < 5; i++) {
                if (emp[i]) {
                    dott[i]->b_threat[temp]++;
                    if (started) {
                        dott[i]->b_threat[dott[0]->b_last[edge]]--;
                    }
                }
            }
            dott[0]->b_last[edge] = temp;
        }
        else if (Black != 0) {
            dott[0]->dead[edge] = true;
            if (started) {
                for (int i = 0; i < 5; i++) {
                    if (emp[i]) {
                        dott[i]->b_threat[dott[0]->b_last[edge]]--;
                        dott[i]->w_threat[dott[0]->w_last[edge]]--;
                    }
                }
            }
            return;
        }

        return;
    }
    void start() {
        len = n * n;
        board = new dot[len];
        for (int i = n * (n - 4); i < len; i++) {
            board[i].dead[0] = true;
            board[i].dead[1] = true;
            board[i].dead[2] = true;
        }
        int temp=0;
        for (int i = 0; i < len; i = temp) {
            temp = i + n;
            int at = i + 4;
            for (int k = i; k < at; k++) {
                if (k >= len) {

                }
                board[k].dead[0] = true;
            }
            for (int k = i + (n - 4); k < temp; k++) {
                board[k].dead[2] = true;
                board[k].dead[3] = true;
            }
        }
        for (int i = 0; i < len; i++) {
            update(i);
        }
        started = true;
    }
    int think() {
        bool* best = new bool[len];
        bool* abest = new bool[len];
        int left = 0;
        for (int i = 0; i < len; i++) {
            if (board[i].has == null) {
                best[i] = true;
                abest[i] = true;
                left++;
            }
            else {
                best[i] = false;
                abest[i] = false;
            }
        }
        int aleft = left;
        int max = 0, maxa = 0, amax = 0, maxd = 0, ttemp;
        bool dfind = true, afind = true;
        for (int now = 0; now < 5; now++) {
            /*if (now == 0) {
                dtemp=-1;
            }else{
                dtemp=0;
            }*/
            for (int i = 0; i < len; i++) {
                if (dfind && best[i]) {
                    ttemp = board[i].w_threat[now];
                    if (ttemp > max) {
                        max = ttemp;
                        for (int k = 0; k < i; k++) {
                            if (best[k]) {
                                best[k] = false;
                                left--;
                            }
                        }
                    }
                    else if (ttemp < max) {
                        best[i] = false;
                        left--;
                    }
                    if (left == 1) {
                        dfind = false;
                    }
                }
                if (afind && abest[i]) {
                    ttemp = board[i].b_threat[now];
                    if (ttemp > amax) {
                        amax = ttemp;
                        for (int k = 0; k < i; k++) {
                            if (abest[k]) {
                                abest[k] = false;
                                aleft--;
                            }
                        }
                    }
                    else if (ttemp < amax) {
                        abest[i] = false;
                        aleft--;
                    }
                    if (aleft == 1) {
                        afind = false;
                    }
                }
            }
            for (int i = 0; i < len; i++) {
                if (dfind && best[i]) {
                    ttemp = board[i].b_threat[now];
                    if (ttemp > maxa) {
                        maxa = ttemp;
                        for (int k = 0; k < i; k++) {
                            if (best[k]) {
                                best[k] = false;
                                left--;
                            }
                        }
                    }
                    else if (ttemp < maxa) {
                        best[i] = false;
                        left--;
                    }
                    if (left == 1) {
                        dfind = false;
                    }
                }
                if (afind && abest[i]) {
                    ttemp = board[i].w_threat[now];
                    if (ttemp > maxd) {
                        maxd = ttemp;
                        for (int k = 0; k < i; k++) {
                            if (abest[k]) {
                                abest[k] = false;
                                aleft--;
                            }
                        }
                    }
                    else if (ttemp < maxd) {
                        abest[i] = false;
                        aleft--;
                    }
                    if (aleft == 1) {
                        afind = false;
                    }
                }
            }
            max = 0, amax = 0, maxa = 0, maxd = 0;
        }
        afind = true;
        dfind = true;
        int dchoice = -1, achoice = -1;
        for (int i = 0; i < len; i++) {
            /*	if(abest[i]==best[i]){
                    printf("att+def:\n");
                    delete[] best,abest;
                    return i;
                }*/
            if (afind && abest[i]) {
                afind = false;
                achoice = i;
            }
            if (dfind && best[i]) {
                dfind = false;
                dchoice = i;
            }
            if ((dfind == false) && (afind == false)) {
                break;
            }
        }
    /*	printf("if defend(%d the same),computer:[%d,%d]\n", left, dchoice% n + 1, (dchoice / n) + 1);
        printf("if attack(%d the same),computer:[%d,%d]\n", aleft, achoice % n + 1, (achoice / n) + 1);*/
        for (int now = 0; now < 5; now++) {
            if (board[dchoice].w_threat[now] > board[achoice].b_threat[now]) {
            /*	printf("defend:");*/
                delete[] best, abest;
                return dchoice;
            }
            else if (board[dchoice].w_threat[now] < board[achoice].b_threat[now]) {
                //printf("attack:");
                delete[] best, abest;
                return achoice;
            }
        }
        for (int i = 0; i < len; i++) {
            if (abest[i] && best[i]) {
            //	printf("att+def:");
                delete[] best, abest;
                return i;
            }
        }
        /*
        end:;
        printf("{computer considered %d dots the same}",left);
        for(int i=0;i<len;i++){
            if(best[i]){
                delete[] best;
                return i;
            }
        }*/
        delete[] best, abest;

        return dchoice;
    }
    struct dot {
        state has = null;
        bool dead[4] = { false };
        int b_threat[5] = { 0 }, w_threat[5] = { 0 };
        int b_last[5] = { 0 }, w_last[5] = { 0 };
    };
    dot* board;
    dot* dott[5];
public:
    idiot(int n,bool h_fir);
    bool go(int x, int y);
    bool get(int* x, int* y);
    state winner();
    ~idiot();
};
#endif
