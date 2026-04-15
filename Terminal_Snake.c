#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Pair {
    int first;
    int second;
} Pair;

#define rows 25
#define cols 25

int score = 0;

char board[rows][cols];
int GameOver = 0;
Pair move_dir = {0, -1};

int snakex = 10;
int snakey = 10;

int fruitx = -1;
int fruity = -1;

Pair snake_body[rows * cols];
int body = 0;

void spawn_fruit(){
    if(fruitx == -1 && fruity == -1){
        Pair snake[rows*cols];
        int count = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(board[i][j] == ' '){
                    Pair p;
                    p.first = i;
                    p.second = j;
                    snake[count] = p;
                    count++;
                }
            }
        }

        int idx = rand() % count;
        fruitx = snake[idx].first;
        fruity = snake[idx].second;
        board[fruitx][fruity] = '*';
    }else{
        board[fruitx][fruity] = '*';
    }
}

void grow(Pair p){
    snake_body[body] = p;
    body++;
}

void make_board(){
    printf("--------Score = %i--------\n", score);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(i == 0 || j == 0 || i == rows - 1 || j == cols - 1) board[i][j] = '#';
            else board[i][j] = ' ';
        }
    }
}

void print_board(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            putch(board[i][j]);
        }
        putch('\n');
    }
}

void make_snake(){
    board[snakex][snakey] = '@';
    if(body > 0){
        for(int i = 0; i < body; i++){
            board[snake_body[i].first][snake_body[i].second] = 'o';
        }
    }
}

void move(int x, int y){

    Pair p = {snakex, snakey};
    if(body > 0){
        p = snake_body[body - 1];
        for(int i = body - 1; i >= 0; i--){
            if(i == 0){
                snake_body[i].first = snakex;
                snake_body[i].second = snakey;
            }else{
                snake_body[i] = snake_body[i-1];
            }
        }
    }

    snakex += x;
    snakey += y;

    move_dir.first = x;
    move_dir.second = y;

    if(snakex == fruitx && snakey == fruity){
        fruitx = -1;
        fruity = -1;
        score ++;
        grow(p);
    }
}

void keyboard_input(){
    if (kbhit()) {
        char c = _getch();

        if(c == 'd') move_dir = (Pair){0,1};
        else if(c == 'a') move_dir = (Pair){0,-1};
        else if(c == 's') move_dir = (Pair){1,0};
        else if(c == 'w') move_dir = (Pair){-1,0};
        else if(c == 'q') GameOver = 1;
    }

    move(move_dir.first, move_dir.second);
}

void isover(){
    if(snakex == 0 || snakey == 0 || snakex == rows-1 || snakey == cols-1) GameOver = 1;
    for(int i = 0; i < body; i++){
        if(snake_body[i].first == snakex && snake_body[i].second == snakey){
            GameOver = 1;
            break;
        }
    }
}

void reset_cursor(){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void hidecursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main(){
    system("cls");
    hidecursor();
    while(!GameOver){
        reset_cursor();
        make_board();
        make_snake();
        spawn_fruit();
        print_board();
        keyboard_input();
        isover();

        Sleep(100);
    }

    printf("Game Over\n");
    return 0;
}
