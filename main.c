#include <curses.h>
#include <stdlib.h>

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
    initCurses();

    drawBorders();
    
    while(1) {
        handleInput();
    }

    return 0;
}