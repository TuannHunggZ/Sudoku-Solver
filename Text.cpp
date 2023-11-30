#include<Text.h>

void Text::SetColor(const int& type)
{
	if (type == WHITE)
	{
		textColor = { 255, 255, 255 };
	}
	else if (type == BLACK)
	{
		textColor = { 0,0,0 };
	}
}

void Text::LoadTexture(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface)
	{
		texture = SDL_CreateTextureFromSurface(screen, textSurface);
		if (texture)
		{
			textRect.w = textSurface->w;
			textRect.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void Text::ShowText(TTF_Font* font, SDL_Renderer* screen)
{
	LoadTexture(font, screen);
	SDL_RenderCopy(screen, texture, NULL, &textRect);	
	SDL_DestroyTexture(texture);
}