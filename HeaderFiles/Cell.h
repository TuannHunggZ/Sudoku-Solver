#ifndef CELL_H
#define CELL_H

#include<ConstantVariable.h>
#include<SDL.h>
#include<SDL_ttf.h>

class Cell
{
public:
	Cell();

	void SetNumber(const int& x) { number = x; }
	int GetNumber() { return number; }
	void SetRow(const int& r) { row = r; }
	int GetRow() { return row; }
	void SetColumn(const int& c) { column = c; }
	int GetColumn() { return column; }
	void SetCellColor(const SDL_Color& color) { cell_color = color; }
	void SetCheck(const bool& c) { check = c; }
	bool GetCheck() { return check; }
	
	void SetDefaultCellColor();
	void DrawCell(SDL_Renderer* renderer, TTF_Font* font_number);

private:
	int number;
	SDL_Color cell_color;
	int row;
	int column;
	bool check;
};

#endif
