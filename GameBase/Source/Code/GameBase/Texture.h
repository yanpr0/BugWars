#pragma once
#include "Log.h"
#include "Point.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

struct Texture
{
	Texture(std::string_view path, SDL_Renderer* renderer);
	~Texture();

	SDL_Texture* texture = nullptr;
	Point size;
};