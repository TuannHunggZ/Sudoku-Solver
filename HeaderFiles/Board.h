#ifndef BOARD_H
#define BOARD_H

#include<Cell.h>
#include<vector>

class Board
{
public:
	void InitBoard();
	void ResetBoard();
	void DrawBoardLine(SDL_Renderer* renderer);
	void DrawBoardCell(SDL_Renderer* renderer, TTF_Font* font_number);
	void DrawBoard(SDL_Renderer* renderer, TTF_Font* font_number);
	void SetDefaultColor();
	void SetAllCheck();
	
	int GetNumber(int row, int column) { return board[row][column]->GetNumber(); }
	Cell* GetCell(int row, int column) { return board[row][column]; }

private:
	std::vector<std::vector<Cell*>> board;
};

#endif
