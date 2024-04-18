#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSNAKELENGTH 20
#define INITSIZE 3

//defines snake (Mitch)
struct snakeData{
    int alive;
    int size; 
    int x [MAXSNAKELENGTH];
    int y [MAXSNAKELENGTH];
};

//initializes snake (Mitch)
void initSnake(struct snakeData* snakeAlias){
    snakeAlias -> size = INITSIZE; 
    snakeAlias -> alive = 1;
    for(int i = 0; i < INITSIZE; i++){
        snakeAlias -> x[i] = COLS / 2 - i;
        snakeAlias -> y[i] = LINES / 2;
        move(LINES / 2, COLS / 2 - i);
        addstr("#");
    }
}

// boilerplate for curses (Emily)
void initCurses() {
    initscr();
    clear();
    curs_set(0); // hide cursor
    noecho();
}

// Emily
void drawBorders() {
    // Draw top & bottom lines
    for (int i = 0; i < COLS; i++) {
        move(0, i);
        addstr("-");
        move(LINES - 1, i);
        addstr("-");
    }

    // Draw side lines
    for (int i = 0; i < LINES; i++) {
        move(i, 0);
        addstr("|");
        move(i, COLS - 1);
        addstr("|");
    }
}

// handles key presses (Emily)
void handleInput() {
    int ch = getch();
    switch(ch) {
        case 'x':
        case 'X':
            endwin();
            exit(0);
    }
}


int main() {
    struct snakeData snake; 

    initCurses();
    drawBorders();
    initSnake(&snake);
    
    while(snake.alive){
        //TODO snake movement goes here (I Think)
        while(1) {
            handleInput();
        }
    }

    return 0;
}