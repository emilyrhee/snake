#include <curses.h>
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

int main() {
    return 0;
}