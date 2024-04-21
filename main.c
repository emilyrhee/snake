#include <curses.h>
#include <stdbool.h>
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
//TODO fill x, y arrays with zeros
void initSnake(struct snakeData* snake){
    snake -> size = INITSIZE; 
    snake -> alive = 1;
    for(int i = 0; i < INITSIZE; i++){
        snake -> x[i] = COLS / 2 - i;
        snake -> y[i] = LINES / 2;
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
    nodelay(stdscr, TRUE);
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
// TODO get direction input. Should return char or int? 
void handleInput() {
    int ch = getch();
    switch(ch) {
        case 'x':
        case 'X':
            endwin();
            exit(0);
    }
}

//snake goes zoooooo0o()()oom!!(mitch)
//TODO get direction and pray code still works. 
void snakeMovement(struct snakeData* snake, int direction){
    //rotate snake body array [(y,x newLocation), (y,x[index-1]), (y,x[index-1]), ...]
    int prevX = 0;
    int prevY = 0;
    int tempX = 0;
    int tempY = 0;
    int i = 0;
    prevX = snake->x[0];
    prevY = snake ->y[0];
    while(snake->x[i] != 0 && snake->y[i] != 0){
        tempX = snake->x[i+1];
        tempY = snake->y[i+1];
        snake->x[i+1] = prevX;
        snake->y[i+1] = prevY;
        prevX = tempX;
        prevY = tempY;
        i++;
    }

    //Get print body at (nextY, nextX)) 
    int nextX = snake->x[0];
    int nextY = snake->y[0];
    switch (direction) {
        case 1: 
            nextX +=1;
    }
    snake->x[0] = nextX;
    snake->y[0] = nextY;
    move(nextY, nextX); 
    addstr("#");

    //delete body at (LastY, LastX)
    int lastX = snake->x[snake->size];
    int lastY = snake->y[snake->size];
    move(lastY, lastX); 
    addstr(" ");

    refresh();
}

int main() {
    struct snakeData snake; 
    int direction = 1;

    initCurses();
    drawBorders();
    initSnake(&snake);
    
    while(snake.alive){
        snakeMovement(&snake, direction);
        handleInput();
        usleep(600000);
    }
    return 0;
}