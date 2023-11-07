# Snake-C
Snake-C is a simple implementation of the classic Snake Game in C for Linux. This project serves as both a learning exercise and an enjoyable game.

![Snake Game Screenshot](https://github.com/Chewbaccaun/Snake-C/blob/main/screenshot.png)

## Installation

To play Snake-C, you need a C compiler. On Ubuntu or Debian, you can install `gcc` by running:

```
sudo apt install gcc
```

## Compilation

After installing the C compiler, navigate to the project's root directory and compile the game using the following command:
```
gcc -o snake snake.c
```
This command compiles the source code in `snake.c` into an executable named `snake`. 

## Controls

Snake-C uses the following controls:

- `w` to move up
- `a` to turn left
- `d` to turn right
- `s` to move down

## Usage

To play the game, simply launch it using `./snake` in terminal and use the specified controls to guide the snake and collect food while avoiding collisions with the boundaries or the snake itself.

## License

Snake-C is open-source software and is distributed under the GPL-3.0 license, which means that you are free to use and modify the code as long as you adhere to the terms of the license.
