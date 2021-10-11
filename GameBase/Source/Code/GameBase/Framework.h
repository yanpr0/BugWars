#pragma once
#include "Point.h"

struct GameBase;
struct TTF_FontWrapper;
struct SDL_Window;
struct SDL_Renderer;

struct Framework
{
	Framework();
	~Framework();

	void Run(GameBase& game);

	void RenderText(const std::string& text, const Point& position);

	TTF_FontWrapper* font = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Point screenSize;
	bool lock60fps = false;
};