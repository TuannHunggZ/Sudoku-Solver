#include<Cell.h>
#include<Text.h>

Cell::Cell()
{
	number = 0;
	cell_color = uncheckedCellColor;
	row = 0;
	column = 0;
	check = false;
}

void Cell::SetDefaultCellColor()
{
	if (check)
	{
		SetCellColor(checkedCellColor);
	}
	else
	{
		SetCellColor(uncheckedCellColor);
	}
}

void Cell::DrawCell(SDL_Renderer* renderer, TTF_Font* font_number)
{
	//Coordinate of cell
	SDL_Rect rect;
	rect.w = CELL_SIZE;
	rect.h = CELL_SIZE;
	rect.x = column * CELL_SIZE + 50;
	rect.y = row * CELL_SIZE + 50;

	// Fill background's color of cells  
	SDL_SetRenderDrawColor(renderer, cell_color.r, cell_color.g, cell_color.b, 255);
	SDL_RenderFillRect(renderer, &rect);

	//Show number
	if (number != 0)
	{
		Text numberText;
		numberText.SetColor(Text::BLACK);
		numberText.SetText(std::to_string(number));
		numberText.LoadTexture(font_number, renderer);
		numberText.SetRectX(rect.x + (CELL_SIZE - numberText.GetRect().w) / 2);
		numberText.SetRectY(rect.y + (CELL_SIZE - numberText.GetRect().h) / 2);
		numberText.ShowText(font_number, renderer);
	}
}