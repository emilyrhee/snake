# Requirements
## The Snake Pit:

- [x] The snake pit is the area where the snake can move.
- [x] The snake pit must utilize all available space of the current terminal window.
- [x] There must be a visible border delineating the snake pit.

## The Snake:

- [x] The initial length of the snake is three characters.
- [x] Initial direction of the snake's movement is chosen randomly.
- [x] The user can press one of the four arrow keys to change the direction of the snake's movement.
- [ ] The snake's speed is proportional to its length.

## The Trophies:

- [x] Trophies are represented by a digit randomly chosen from 1 to 9.
- [x] There's always exactly one trophy in the snake pit at any given moment.
- [ ] When the snake eats the trophy, its length is increased by the corresponding number of characters.
- [x] A trophy expires after a random interval from 1 to 9 seconds.
<<<<<<< HEAD
- [ ] A new trophy is shown at a random location on the screen after the previous one has either expired or is eaten by the snake.
=======
- [x] A new trophy is shown at a random location on the screen after the previous one has either expired,
- [ ] or is eaten by the snake.
>>>>>>> a749a6722b2f241fea2031b8814267a403c23fd8

## Gameplay:

The snake dies and the game ends if:
- [x] It runs into the border; or
- [ ] It runs into itself; or
- [x] The user attempts to reverse the snake's direction.

The user wins if:
- [ ] The snake's length grows to the length equal to half the perimeter of the border.
