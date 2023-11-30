#include<Board.h>

void Board::InitBoard()
{
	for (int i = 0; i < 9; i++)
	{
		std::vector<Cell*> cell_list(9, nullptr);
		for (int j = 0; j < 9; j++)
		{
			Cell* newCell = new Cell();
			newCell->SetNumber(defaultGame[i][j]);
			newCell->SetRow(i);
			newCell->SetColumn(j);
			if (newCell->GetNumber() != 0)
			{
				newCell->SetCheck(true);
			}
			newCell->SetDefaultCellColor();
			cell_list[j] = newCell;
		}
		board.push_back(cell_list);
	}
}

void Board::ResetBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j]->SetNumber(defaultGame[i][j]);
			if (board[i][j]->GetNumber() == 0)
			{
				board[i][j]->SetCellColor(uncheckedCellColor);
				board[i][j]->SetCheck(false);
			}
			else
			{
				board[i][j]->SetCellColor(checkedCellColor);
				board[i][j]->SetCheck(true);
			}
		}
	}
}

void Board::SetDefaultColor()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j]->SetDefaultCellColor();
		}
	}
}

void Board::SetAllCheck()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j]->SetCheck(true);
		}
	}
}

void Board::DrawBoardCell(SDL_Renderer* renderer, TTF_Font* font_number)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j]->DrawCell(renderer, font_number);
		}
	}
}

void Board::DrawBoardLine(SDL_Renderer* renderer)
{
	SDL_Rect vertical;
	SDL_Rect horizontal;
	SDL_SetRenderDrawColor(renderer, boardLineColor.r, boardLineColor.g, boardLineColor.b, 255);
	for (int i = 0; i <= BOARD_SIZE; i += CELL_SIZE) {
		if (i % (CELL_SIZE * 3) == 0) { // Draw thick lines to distinguish 3x3 squares
			vertical = { i + 50 - LINE_THICK / 2, 50, LINE_THICK, BOARD_SIZE };
			SDL_RenderFillRect(renderer, &vertical);
			horizontal = { 50, i + 50 - LINE_THICK / 2, BOARD_SIZE, LINE_THICK };
			SDL_RenderFillRect(renderer, &horizontal);
		}
		else {
			SDL_RenderDrawLine(renderer, i + 50, 50, i + 50, BOARD_SIZE + 50);
			SDL_RenderDrawLine(renderer, 50, i + 50, BOARD_SIZE + 50, i + 50);
		}
	}
}

void Board::DrawBoard(SDL_Renderer* renderer, TTF_Font* font_number)
{
	DrawBoardCell(renderer, font_number);
	DrawBoardLine(renderer);
}