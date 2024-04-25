#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAXSNAKELENGTH 20
#define INITSIZE 3
#define INITSPEED 300000

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

//defines snake (Mitch)
struct snakeData{
    Direction direction;
    bool isAlive;
    int size;
    int speed;
    int x [MAXSNAKELENGTH];
    int y [MAXSNAKELENGTH];
};

struct trophyData{
    bool isAlive;
    int time;
    int size; 
    int X;
    int Y;
};


//initializes snake (Mitch)
//TODO fill x, y arrays with zeros
void initSnake(struct snakeData* snake){
    snake -> size = INITSIZE; 
    snake -> isAlive = true;
    snake -> speed = INITSPEED;
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

//moves snake (mitch)
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

// sets a random initial direction (Emily)
void initDirection(struct snakeData* snake) {
    srand(time(NULL));
    snake->direction = rand() % 4;
}

// Check if snake's head collides w/border (Emily)
bool isSnakeOutOfBounds(struct snakeData* snake) {
    return (
        !snake->x[0]
        || snake->x[0] == COLS - 1
        || !snake->y[0]
        || snake->y[0] == LINES - 1
    );
}


int randomRange(int lowerBound, int upperBound){
    return (rand() % (upperBound - lowerBound + 1) + lowerBound);
}

//Create random trophy (Mitch)
void spawnTrophy(struct trophyData* trophy){
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
    move(ranY, ranX);
    printw("%d",ranTrophy);
}

int main() {
    struct snakeData snake;
    struct trophyData trophy;
    int trophyClock = 0;
    
    initDirection(&snake);
    initCurses();
    drawBorders();
    initSnake(&snake);
    
    //initalize trophy outside bounds
    trophy.X = -1;
    trophy.Y = -1;
    spawnTrophy(&trophy);

    while(snake.isAlive){
        handleInput(&snake);
        snakeMovement(&snake);
        
        usleep(snake.speed);

        if (isSnakeOutOfBounds(&snake)) {
            snake.isAlive = false;
        }
        if(trophyClock > trophy.time*1000000 || trophy.isAlive == FALSE){
            spawnTrophy(&trophy);
            trophyClock = 0;
        }
        trophyClock += snake.speed;
    }

    endwin();
    return 0;
}