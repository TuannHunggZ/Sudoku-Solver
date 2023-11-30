#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>

class Text
{
public:
	enum TextColor
	{
		WHITE,
		BLACK,
	};

	void SetText(const std::string& txt) { text = txt; }
	void SetColor(const int& type);
	SDL_Rect GetRect() { return textRect; }
	void SetRect(const SDL_Rect& rect) { textRect = rect; }
	void SetRectX(const int& x) { textRect.x = x; }
	void SetRectY(const int& y) { textRect.y = y; }
	void LoadTexture(TTF_Font* font, SDL_Renderer* screen);
	void ShowText(TTF_Font* font, SDL_Renderer* screen);

private:
	std::string text;
	SDL_Color textColor;
	SDL_Rect textRect;
	SDL_Texture* texture;
};

#endif

