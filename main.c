#include <curses.h>
#include <stdlib.h>

void initCurses() { // Emily
    initscr(); // boilerplate for curses
    clear();
    curs_set(0); // hide cursor
    noecho();
}

void drawBorders() { // Emily
    for (int i = 0; i < COLS; i++) { // Draw top & bottom lines
        move(0, i);
        addstr("-");
        move(LINES - 1, i);
        addstr("-");
    }

    for (int i = 0; i < LINES; i++) { // Draw side lines
        move(i, 0);
        addstr("|");
        move(i, COLS - 1);
        addstr("|");
    }
}

void handleInput() { // Emily
    int ch = getch();
    switch(ch) { // handles key presses
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