#include<Solver.h>
#include<ConstantVariable.h>
#include<Text.h>

bool Solver::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (g_screen == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);

				//Init font
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}
				else
				{
					font_number = TTF_OpenFont("VNIWIN.TTF", 24);
					font_text = TTF_OpenFont("VNIWIN.TTF", 35);
					if (font_number == NULL || font_text == NULL)
					{
						printf("SDL_ttf could not initialize!\n");
						return false;
					}
				}
			}
		}
	}
	return true;
}

void Solver::Close()
{
	SDL_DestroyRenderer(g_screen);
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	g_screen = NULL;

	SDL_Quit();
}

void Solver::LoadVariable()
{
	isRunning = true;
	x_mouse = 0;
	y_mouse = 0;
	isSolving = false;
	board.InitBoard();
	error_row = 0;
	error_column = 0;
	current_row = 0;
	current_column = 0;
	win = false;
	lose = false;
	canChangeNumber = false;
	numberChange = -1;
	rowChange = 0;
	columnChange = 0;
}

bool Solver::CheckMouseVsItem(const int& x_mouse, const int& y_mouse, const SDL_Rect& rect)
{
	if (x_mouse > rect.x && x_mouse < rect.x + rect.w && y_mouse > rect.y && y_mouse < rect.y + rect.h) {
		return true;
	}
	return false;
}

void Solver::ShowAnnouncement(std::string s)
{
	Text text;
	text.SetText(s);
	text.SetColor(Text::BLACK);
	text.LoadTexture(font_text, g_screen);
	text.SetRectX((SCREEN_WIDTH - text.GetRect().w) / 2);
	text.SetRectY((50 - text.GetRect().h) / 2);
	text.ShowText(font_text, g_screen);
}

void Solver::HandleButton()
{
	if (g_event.type == SDL_MOUSEMOTION)
	{
		x_mouse = g_event.motion.x;
		y_mouse = g_event.motion.y;
	}
	else if (g_event.type == SDL_MOUSEBUTTONDOWN)
	{		
		SDL_Rect reset = { RESET_BUTTON_X, RESET_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
		SDL_Rect solve = { SOLVE_BUTTON_X, SOLVE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
		if (CheckMouseVsItem(x_mouse, y_mouse, solve))
		{
			isSolving = true;
		}
		
		if (CheckMouseVsItem(x_mouse, y_mouse, reset))
		{
			board.ResetBoard();
			isSolving = false;
			JumpToFirstEmptyCell();
			win = false;
			lose = false;
			while (!inSolving.empty())
			{
				inSolving.pop();
			}
		}
	}
}

void Solver::HandleChangeNumber()
{
	//Cannot change number when it is in solving
	if (isSolving)
	{
		return;
	}

	if (g_event.type == SDL_MOUSEMOTION)
	{
		x_mouse = g_event.motion.x;
		y_mouse = g_event.motion.y;
		rowChange = (y_mouse - 50) / 50;
		columnChange = (x_mouse - 50) / 50;
		SDL_Rect board_rect = { 50, 50 , BOARD_SIZE , BOARD_SIZE };		
		if (CheckMouseVsItem(x_mouse, y_mouse, board_rect))
		{
			canChangeNumber = true;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (i == rowChange && j == columnChange)
					{
						board.GetCell(i, j)->SetCellColor(errorCellColor);
					}
					else
					{
						board.GetCell(i, j)->SetDefaultCellColor();
					}
				}
			}
		}
		else
		{
			canChangeNumber = false;
			board.SetDefaultColor();
		}
	}
	if (g_event.type == SDL_KEYDOWN)
	{
		switch (g_event.key.keysym.sym)
		{
		case (SDLK_0):
			numberChange = 0;
			break;
		case (SDLK_1):
			numberChange = 1;
			break;
		case (SDLK_2):
			numberChange = 2;
			break;
		case (SDLK_3):
			numberChange = 3;
			break;
		case (SDLK_4):
			numberChange = 4;
			break;
		case (SDLK_5):
			numberChange = 5;
			break;
		case (SDLK_6):
			numberChange = 6;
			break;
		case (SDLK_7):
			numberChange = 7;
			break;
		case (SDLK_8):
			numberChange = 8;
			break;
		case (SDLK_9):
			numberChange = 9;
			break;
		default:
			numberChange = -1;
			break;
		}
	}
	else if (g_event.type == SDL_KEYUP)
	{
		numberChange = -1;
	}
}

void Solver::ChangeNumber()
{
	if (canChangeNumber == true)
	{
		if (numberChange != -1)
		{
			if (numberChange == 0)
			{
				board.GetCell(rowChange, columnChange)->SetNumber(0);
				board.GetCell(rowChange, columnChange)->SetCheck(false);
				JumpToFirstEmptyCell();
			}
			else if (numberChange != board.GetNumber(rowChange, columnChange))
			{
				if (CanPutNumber(rowChange, columnChange, numberChange))
				{
					board.GetCell(rowChange, columnChange)->SetNumber(numberChange);
					board.GetCell(rowChange, columnChange)->SetCheck(true);
					JumpToFirstEmptyCell();
				}
				else
				{
					ShowAnnouncement("INVALID NUMBER");
					board.GetCell(error_row, error_column)->SetCellColor(errorCellColor);
				}
			}
		}
		else
		{
			board.GetCell(error_row, error_column)->SetDefaultCellColor();
			if (rowChange == error_row && columnChange == error_column)
			{
				board.GetCell(error_row, error_column)->SetCellColor(errorCellColor);
			}
		}
	}
}

void Solver::ShowButton(int x, int y, std::string s)
{
	SDL_Rect rect;
	rect.w = BUTTON_WIDTH;
	rect.h = BUTTON_HEIGHT;
	rect.x = x;
	rect.y = y;

	SDL_SetRenderDrawColor(g_screen, buttonColor.r, buttonColor.g, buttonColor.b, 255);
	SDL_RenderFillRect(g_screen, &rect);

	//Draw border
	SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
	SDL_RenderDrawLine(g_screen, x, y, x + 150, y);
	SDL_RenderDrawLine(g_screen, x + 150, y, x + 150, y + 50);
	SDL_RenderDrawLine(g_screen, x, y, x, y + 50);
	SDL_RenderDrawLine(g_screen, x, y + 50, x + 150, y + 50);

	//Show text
	Text text;
	text.SetText(s);
	text.SetColor(Text::BLACK);
	if (CheckMouseVsItem(x_mouse, y_mouse, rect))
	{
		text.SetColor(Text::WHITE);
	}
	text.LoadTexture(font_text, g_screen);
	text.SetRectX(x + (BUTTON_WIDTH - text.GetRect().w) / 2);
	text.SetRectY(y + (BUTTON_HEIGHT - text.GetRect().h) / 2);
	text.ShowText(font_text, g_screen);
}

void Solver::JumpToNextCell()
{
	while (board.GetNumber(current_row, current_column) != 0)
	{
		if (current_column < 8) //Next column
		{
			current_column++;
		}
		else if (current_column == 8 && current_row < 8) //Next row
		{
			current_column = 0;
			current_row++;
		}
		else if (current_row == 8 && current_column == 8) //Win
		{
			win = true;
			isSolving = false;
			return;
		}
	}
}

void Solver::JumpToPreviousCell()
{
	if (inSolving.empty()) //Lose
	{
		lose = true;
		isSolving = false;
		return;
	}
	current_row = inSolving.top().first;
	current_column = inSolving.top().second;
	inSolving.pop();
}

void Solver::JumpToFirstEmptyCell()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board.GetNumber(i, j) == 0)
			{
				current_row = i;
				current_column = j;
				return ;
			}
		}
	}
	win = true;
}

bool Solver::CanPutNumber(int row, int column, int num)
{
	if (num != 0)
	{
		for (int i = 0; i < 9; i++)
		{
			//Check column
			if (board.GetNumber(i, column) == num)
			{
				error_row = i;
				error_column = column;
				return false;
			}
			//Check row
			if (board.GetNumber(row, i) == num)
			{
				error_row = row;
				error_column = i;
				return false;
			}
			//Check 3x3 square
			if (board.GetNumber(3 * (row / 3) + i / 3, 3 * (column / 3) + i % 3) == num)
			{
				error_row = 3 * (row / 3) + i / 3;
				error_column = 3 * (column / 3) + i % 3;
				return false;
			}
		}
	}
	return true;
}

void Solver::SolveSudoku()
{
	if (win || lose)
		return;
	int num = board.GetNumber(current_row, current_column);
	if (num != 9)
	{
		if (CanPutNumber(current_row, current_column, num + 1))
		{
			std::pair<int, int> coordinate = std::make_pair(current_row, current_column);
			inSolving.push(coordinate);
			board.GetCell(current_row, current_column)->SetNumber(num + 1);
			JumpToNextCell();
		}
		else
		{
			board.GetCell(current_row, current_column)->SetNumber(num + 1);
			board.GetCell(current_row, current_column)->SetCellColor(errorCellColor);
			board.GetCell(error_row, error_column)->SetCellColor(errorCellColor);
		}
	}
	else
	{
		board.GetCell(current_row, current_column)->SetNumber(0);
		JumpToPreviousCell();
	}
}

void Solver::Loop()
{
	if (!Init())
		return;

	LoadVariable();
	while (isRunning)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			HandleButton();
			HandleChangeNumber();
		}

		//Clear Screen
		SDL_SetRenderDrawColor(g_screen, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
		SDL_RenderClear(g_screen);

		if (!isSolving && !win && !lose)
		{
			ChangeNumber();
		}

		if (isSolving)
		{
			SolveSudoku();
		}

		board.DrawBoard(g_screen, font_number);

		ShowButton(RESET_BUTTON_X, RESET_BUTTON_Y, "Reset");
		ShowButton(SOLVE_BUTTON_X, SOLVE_BUTTON_Y, "Solve");

		if (win)
		{
			board.SetAllCheck();
			board.SetDefaultColor();
			while (!inSolving.empty())
			{
				inSolving.pop();
			}
			isSolving = false;
			ShowAnnouncement("FINISH");
		}
		else if (lose)
		{
			isSolving = false;
			while (!inSolving.empty())
			{
				inSolving.pop();
			}
			ShowAnnouncement("CAN'T SOLVE");
		}

		//Update Screen
		SDL_RenderPresent(g_screen);
		if (isSolving)
		{
			SDL_Delay(DELAY);
			board.SetDefaultColor();
		}	
	}

	Close();
}