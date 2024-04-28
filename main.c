#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "cutScreens.h"

#define MAXSNAKELENGTH 50

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

//defines snake (Mitch)
typedef struct {
    Direction direction;
    bool isAlive;
    int size;
    int speed;
    int x[MAXSNAKELENGTH];
    int y[MAXSNAKELENGTH];
} SnakeData;

//defines trophy (Mitch)
typedef struct {
    bool isAlive;
    int time;
    int size; 
    int X;
    int Y;
} TrophyData;

int randomRange(int lowerBound, int upperBound){
    srand(time(NULL));
    return (rand() % (upperBound - lowerBound + 1) + lowerBound);
}

//initializes snake (Mitch)
void initSnake(SnakeData* snake, int size, int speed){
    
    snake -> size = size; 
    snake -> isAlive = true;
    snake -> speed = speed;
    snake -> direction = randomRange(0, 3);
    switch (snake->direction) {
        case UP: 
            for(int i = 0; i < size; i++){
                snake -> x[i] = COLS / 2;
                snake -> y[i] = LINES / 2 + i;
                move(LINES / 2 +i , COLS / 2 );
                addstr("#");
            }  
            break;
        case DOWN:
            for(int i = 0; i < size; i++){
                snake -> x[i] = COLS / 2;
                snake -> y[i] = LINES / 2 - i;
                move(LINES / 2 - i, COLS / 2);
                addstr("#");
            }
            break;
        case LEFT:
            for(int i = 0; i < size; i++){
                snake -> x[i] = COLS / 2 + i;
                snake -> y[i] = LINES / 2;
                move(LINES / 2, COLS / 2 + i);
                addstr("#");
            }
            break;
        case RIGHT:
            for(int i = 0; i < size; i++){
                snake -> x[i] = COLS / 2 - i;
                snake -> y[i] = LINES / 2;
                move(LINES / 2, COLS / 2 - i);
                addstr("#");
            }
            break;
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
        mvaddstr(0, i, "-");
        mvaddstr(LINES - 1, i, "-");
    }

    // Draw side lines
    for (int i = 0; i < LINES; i++) {
        mvaddstr(i, 0, "|");
        mvaddstr(i, COLS - 1, "|");
    }
}

int targetScore() {
    return COLS + LINES;
}

// handles key presses (Emily)
void handleInput(SnakeData* snake) {
    int ch = getch();
    keypad(stdscr, TRUE);
    switch(ch) {
        case KEY_UP:
            if(snake->direction == DOWN){
                snake->isAlive = FALSE;
            }
            snake->direction = UP;
            break;
        case KEY_DOWN:
            if(snake->direction == UP){
                snake->isAlive = FALSE;
            }
            snake->direction = DOWN;
            break;
        case KEY_LEFT:
            if(snake->direction == RIGHT){
                snake->isAlive = FALSE;
            }
            snake->direction = LEFT;
            break;
        case KEY_RIGHT:
            if(snake->direction == LEFT){
                snake->isAlive = FALSE;
            }
            snake->direction = RIGHT;
            break;
        case 'x':
        case 'X':
            endwin();
            exit(0);
            break;
    }
}

// Checks if snake's coordinates are equal to trophy's (Emily)
bool isCollidingTrophy(SnakeData* snake, TrophyData* trophy) {
    return (snake->x[0] == trophy->X && snake->y[0] == trophy->Y);
}

//Checks if snake collides with self (mitch)
void isCollidingSnake(SnakeData* snake){
    bool collides = FALSE;
    for(int i = 1; i < snake->size; i++ ){
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            snake->isAlive = FALSE;
        }
    }
}

//moves snake (Mitch)
void snakeMovement(SnakeData* snake){
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

    // Redraw snake from head to end of tail (Emily)
    for (int i = 0; i < snake->size; i++) {
        move(snake->y[i], snake->x[i]);
        addstr("#");
    }

    //delete body at (LastY, LastX)
    move(lastY, lastX);
    addstr(" ");
}

// Check if snake's head collides w/border (Emily)
bool isSnakeOutOfBounds(SnakeData* snake) {
    return (
        !snake->x[0]
        || snake->x[0] == COLS - 1
        || !snake->y[0]
        || snake->y[0] == LINES - 1
    );
}



//Create random trophy (Mitch)
void spawnTrophy(TrophyData* trophy, SnakeData* snake){
    //delete  previous trophy
    move(trophy->Y, trophy->X);
    addstr(" ");

    //get random numbers
    int ranTrophy = 0, ranX = 0, ranY = 0, ranWait=0; 
    ranTrophy = randomRange(1, 9);
    ranX = randomRange(1, COLS - 2);
    ranY = randomRange(1, LINES - 2);
    ranWait = randomRange(1, 9);

    //fill trophy data
    trophy -> isAlive = TRUE;
    trophy -> size = ranTrophy;
    trophy -> time = ranWait;
    trophy -> X = ranX;
    trophy -> Y = ranY;

    //create trophy
    for(int i = 0; i < snake->size; i++){
        if (snake->x[i] == ranX && snake->y[i] == ranY){
            spawnTrophy(trophy, snake);
            return;
        }
    }
    move(ranY, ranX);
    printw("%d",ranTrophy);
}

// Sets values for snake coordinates after obtaining trophy (Emily)
void growSnake(SnakeData* snake, TrophyData* trophy) {
    int newSize = snake->size + trophy->size;
    if (newSize > MAXSNAKELENGTH) newSize = MAXSNAKELENGTH;
    for (int i = snake->size; i < newSize; i++) {
        snake->x[i] = snake->x[snake->size - 1];
        snake->y[i] = snake->y[snake->size - 1];
    }
    snake->size = newSize;
}

// Emily
void printCenteredMsg(const char* message) {
    int messageLen = strlen(message);
    // Calculate center position based on message length and window size
    mvaddstr(LINES / 2, (COLS - messageLen) / 2, message);
    refresh();
    sleep(2);
}


int main() {
    SnakeData snake;
    TrophyData trophy;
    int trophyClock = 0;
    int size = 5;
    int speed = 200000;
    
    //initDirection(&snake);
    initCurses();
    drawBorders();
    //startScreen();
    drawBorders();
    initSnake(&snake, size, speed);
    
    //initalize trophy outside bounds
    trophy.X = -1;
    trophy.Y = -1;
    spawnTrophy(&trophy, &snake);

    while(snake.isAlive){
        int speed = 0;
        handleInput(&snake);
        if(snake.direction == UP || snake.direction == DOWN){
            speed = snake.speed*.66;
        }else{
            speed = snake.speed;
        }
        snakeMovement(&snake);
        
        usleep(snake.speed);

        if (isSnakeOutOfBounds(&snake)) {
            snake.isAlive = false;
        }

        if (isCollidingTrophy(&snake, &trophy)) {
            trophy.isAlive = false;
            snake.speed *= .9;
            growSnake(&snake, &trophy);
        }
        isCollidingSnake(&snake);

        if (trophyClock > trophy.time*1000000 || !trophy.isAlive){
            spawnTrophy(&trophy, &snake);
            trophyClock = 0;
        }
        trophyClock += snake.speed;

        if (snake.size >= targetScore()) {
            clear();
            printCenteredMsg("You won! :D");
            break;
        }
    }

    endwin();
    return 0;
}