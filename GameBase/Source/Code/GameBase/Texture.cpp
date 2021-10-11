#include "pch.h"
#include "Texture.h"
#include "Globals.h"

Texture::Texture(std::string_view path, SDL_Renderer* renderer)
{
	auto surface = IMG_Load(path.data());
	if (!surface)
	{
		Log("Unable to load an image {}. Error code = {}", path, IMG_GetError());
		return;
	}
	size = Point(surface->w, surface->h);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		Log("Unable to create a texture. Error code = {}", SDL_GetError());
	}
	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	if (texture)
		SDL_DestroyTexture(texture);
}