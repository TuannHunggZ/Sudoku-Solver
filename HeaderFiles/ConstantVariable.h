#ifndef CONSTANTVARIABLE_H
#define CONSTANTVARIABLE_H

#include<string>
#include<vector>
#include<SDL.h>

//Game
const std::vector<std::vector<int>> defaultGame = { {0,4,0,0,2,0,8,6,5},
											{7,0,0,6,0,8,0,0,0},
											{1,0,0,0,0,4,7,0,2},
											{0,1,8,7,4,0,0,0,0},
											{0,0,5,2,0,9,6,0,0},
											{0,0,0,0,8,6,1,5,0},
											{9,0,1,5,0,0,0,0,6},
											{0,0,0,8,0,2,0,0,7},
											{8,7,3,0,6,0,0,2,0} };

//Screen
const int SCREEN_WIDTH = 550;
const int SCREEN_HEIGHT = 600;
const std::string WINDOW_TITLE = "Solve sudoku using backtracking";
const SDL_Color backgroundColor = { 158, 93, 117 };

//Cell
const int CELL_SIZE = 50;
const SDL_Color checkedCellColor = { 213, 155, 209 };
const SDL_Color uncheckedCellColor = { 255, 255, 255 };
const SDL_Color errorCellColor = { 113, 49, 99 };

//Board
const int BOARD_SIZE = 450;
const int LINE_THICK = 3; //To draw 3x3 square
const SDL_Color boardLineColor = { 106, 77, 107 };

//Time
const int DELAY = 300;

//Button
const SDL_Color buttonColor = { 113, 49, 99 };
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 50;
const int RESET_BUTTON_X = 100;
const int RESET_BUTTON_Y = 525;
const int SOLVE_BUTTON_X = 300;
const int SOLVE_BUTTON_Y = 525;

#endif