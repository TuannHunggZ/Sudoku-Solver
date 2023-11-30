#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<stack>
#include<utility>
#include<SDL.h>
#include<SDL_ttf.h>
#include<Board.h>

class Solver
{
public:
	bool Init();
	void LoadVariable();
	void Close();
	void Loop();

	bool CheckMouseVsItem(const int& x_mouse, const int& y_mouse, const SDL_Rect& rect);
	void ShowAnnouncement(std::string s);
	void ShowButton(int x, int y, std::string s);
	void HandleButton();
	void HandleChangeNumber();
	void ChangeNumber();

	void JumpToNextCell();
	void JumpToPreviousCell();
	void JumpToFirstEmptyCell();
	bool CanPutNumber(int row, int column, int num);
	void SolveSudoku();

private:
	bool isRunning;
	SDL_Window* g_window;
	SDL_Renderer* g_screen;
	SDL_Event g_event;
	TTF_Font* font_number;
	TTF_Font* font_text;

	int x_mouse;
	int y_mouse;
	bool isSolving;

	Board board;

	//Use for visualizing solve process
	int error_row;
	int error_column;
	int current_row;
	int current_column;
	bool win;
	bool lose;
	std::stack<std::pair<int, int>> inSolving;

	//Use for changing number
	bool canChangeNumber;
	int numberChange;
	int rowChange;
	int columnChange;
};

#endif
