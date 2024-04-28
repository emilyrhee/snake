# Requirements
## The Snake Pit:

- [x] The snake pit is the area where the snake can move.
- [x] The snake pit must utilize all available space of the current terminal window.
- [x] There must be a visible border delineating the snake pit.

## The Snake:

- [x] The initial length of the snake is three characters.
- [x] Initial direction of the snake's movement is chosen randomly.
- [x] The user can press one of the four arrow keys to change the direction of the snake's movement.
- [x] The snake's speed is proportional to its length.

## The Trophies:

- [x] Trophies are represented by a digit randomly chosen from 1 to 9.
- [x] There's always exactly one trophy in the snake pit at any given moment.
- [x] When the snake eats the trophy, its length is increased by the corresponding number of characters.
- [x] A trophy expires after a random interval from 1 to 9 seconds.
- [x] A new trophy is shown at a random location on the screen after the previous one has either expired or is eaten by the snake.
- [x] A new trophy is shown at a random location on the screen after the previous one has either expired,
- [x] or is eaten by the snake.
- [x] Trophies should not spawn at the same coordinates of a snake segment

## Gameplay:

The snake dies and the game ends if:
- [x] It runs into the border; or
- [x] It runs into itself; or
- [x] The user attempts to reverse the snake's direction.

The user wins if:
- [x] The snake's length grows to the length equal to half the perimeter of the border.
