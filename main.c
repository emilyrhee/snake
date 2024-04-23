#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXSNAKELENGTH 20
#define INITSIZE 5

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

//defines snake (Mitch)
struct snakeData{
    Direction direction;
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
void handleInput(struct snakeData* snake) {
    int ch = getch();
    keypad(stdscr, TRUE);
    switch(ch) {
        case KEY_UP:
            snake->direction = UP;
            break;
        case KEY_DOWN:
            snake->direction = DOWN;
            break;
        case KEY_LEFT:
            snake->direction = LEFT;
            break;
        case KEY_RIGHT:
            snake->direction = RIGHT;
            break;
        case 'x':
        case 'X':
            endwin();
            exit(0);
            break;
    }
}

//snake goes zoooooo0o()()oom!!(mitch)
void snakeMovement(struct snakeData* snake){
    //rotate snake body array [(y,x newLocation), (y,x[index-1]), (y,x[index-1]), ...]
    int prevX = 0;
    int prevY = 0;
    int tempX = 0;
    int tempY = 0;
    int i = 0;
    int lastX = snake->x[snake->size - 1];
    int lastY = snake->y[snake->size - 1];

    prevX = snake->x[0];
    prevY = snake->y[0];
    while(snake->x[i] != 0 && snake->y[i] != 0 && i < snake->size - 1){
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
    // increment/decrement coordinates according to input (Emily)
    switch(snake->direction) {
        case RIGHT:
            nextX++;
            break;
        case UP:
            nextY--;
            break;
        case LEFT:
            nextX--;
            break;
        case DOWN:
            nextY++;
            break;
    }
    snake->x[0] = nextX;
    snake->y[0] = nextY;
    move(nextY, nextX); 
    addstr("#");

    //delete body at (LastY, LastX)
    move(lastY, lastX); 
    addstr(" ");

    refresh();
}

int main() {
    struct snakeData snake; 
    snake.direction = RIGHT;

    initCurses();
    drawBorders();
    initSnake(&snake);
    
    while(snake.alive){
        snakeMovement(&snake);
        handleInput(&snake);
        usleep(100000);
    }
    return 0;
}