#include <iostream>

using namespace std;
char board[3][3];
char pl;
char co;

void computerMove();
bool isOver(char brd[][3] , char c);

void turn(){
    int i;
    int j;
    cout << "Enter coords : ";
    cin >> i >> j;
    if(i >= 3 || j >= 3) return;
    if(board[i][j] == '-'){
        board[i][j] = pl;
    }
    else return;
}

bool isFull(){
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(board[i][j] == '-') return false;
        }
    }
    return true;
}

int minimax(bool maxi , char brd[][3]){
    //player wins
    if(isOver(brd , co)){
        return +10;
    }
    //computer wins
    else if(isOver(brd , pl)){
        return -10;
    }
    //draw
    else if(isFull()) {
        return 0;
    }
    if(maxi){
        int bestScore = -100;
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(brd[i][j] == '-'){
                    brd[i][j] = co;
                    int score = minimax(false, brd);
                    brd[i][j] = '-';
                    if(score > bestScore){
                        bestScore = score;
                    }
                }
            }
        } 
        return bestScore;
    }
    else {
        int bestScore = 100;
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(brd[i][j] == '-'){
                    brd[i][j] = pl;
                    int score = minimax(true, brd);
                    brd[i][j] = '-';
                    if(score < bestScore){
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

void computerMove(){
    int bestScore = -100;
    int r = 1;
    int c = 1;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            if(board[i][j] == '-'){
                board[i][j] = co;
                int score = minimax(false, board);
                board[i][j] = '-';
                if(score > bestScore){
                    bestScore = score;
                    r = i;
                    c = j;
                }
            }
        }
    }
    board[r][c] = co;
}

bool isOver(char brd[][3] , char c){
    //vertical check
    for(int i = 0;i < 3;i++){
        if(brd[0][i] == brd[1][i] && brd[0][i] == brd[2][i] && brd[0][i] != '-' && brd[0][i] == c){
            return true;
        }
    }
    //horizontal check
    for(int i = 0;i < 3;i++){
        if(brd[i][0] == brd[i][1] && brd[i][1] == brd[i][2] && brd[i][0] != '-' && brd[i][0] == c){
            return true;
        }
    }
    //diagonal check
    if(brd[0][0] == brd[1][1] && brd[0][0] == brd[2][2] && brd[0][0] != '-' && brd[0][0] == c){
        return true;
    }
    //anti diagonal check
    if(brd[1][1] == brd[0][2] && brd[2][0] == brd[1][1] && brd[1][1] != '-' && brd[1][1] == c){
        return true;
    }
    return false;
}

void draw(){
    system("cls"); 
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void init(){
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            board[i][j] = '-';
        }
    }
}

int main(){
    char p = 'y';
    while(p == 'y'){
        cout << "Select Player : ";
        cin >> pl;
        if(pl == 'x') co = 'o';
        else co = 'x';
        init();
        while(!isOver(board , 'x') && !isOver(board , 'o') && !isFull()){
            draw();
            if(pl == 'x'){
                turn();
                if(!isOver(board , pl) && !isFull()){
                    computerMove();
                }
            }
            else if(pl == 'o'){
                computerMove();
                draw();
                if(!isFull() && !isOver(board , co))
                    turn();
            }
        }
        draw();
        if(isOver(board , pl)){
            cout << "player has won\n";
        }
        else if(isOver(board , co)){
            cout << "computer won\n";
        }
        else {
            cout << "draw\n";
        }
        cout << "play again?";
        cin >> p;
    }
}
