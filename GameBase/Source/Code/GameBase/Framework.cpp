#include "pch.h"
#include "Framework.h"
#include "Point.h"
#include "Globals.h"
#include "Texture.h"
#include "Log.h"
#include "GameBase.h"
#include "TankBase.h"

struct TTF_FontWrapper
{
	TTF_Font* font;
};

Framework::Framework()
{
	SDL_SetMainReady();
	Log("Welcome to Bug Wars!");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log("Can't initialize SDL. Error code = {}", SDL_GetError());
		return;
	}

	SDL_DisplayMode display_mode;
	if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0)
	{
		Log("Can't get desktop display mode. Error code = ", SDL_GetError());
		return;
	}

	screenSize = Point(display_mode.w, display_mode.h);
	auto window = SDL_CreateWindow("Bug Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display_mode.w, display_mode.h, SDL_WINDOW_SHOWN);
	if (!window)
	{
		Log("Can't create a window. Error code = {}", SDL_GetError());
		return;
	}
	SDL_SetWindowBordered(window, SDL_FALSE);
	SDL_SetWindowPosition(window, 0, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		Log("Can't create a renderer. Error code = {}", SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(renderer, 20, 150, 39, 255);
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		Log("Can't initialize SDL image. Error code = {}", SDL_GetError());
		return;
	}

	if (TTF_Init() < 0)
	{
		Log("Can't initialize TTF. Error code = {}", SDL_GetError());
		return;
	}

	const char* font_name = "Source/Data/Roboto-Regular.ttf";
	auto ttf_font = TTF_OpenFont(font_name, 24);
	if (!ttf_font)
	{
		Log("Can't initialize TTF {}. Error code = {}", font_name, SDL_GetError());
		return;
	}
	font = new TTF_FontWrapper{ ttf_font };
}

Framework::~Framework()
{
	if (font)
	{
		TTF_CloseFont(font->font);
		delete font;
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Framework::Run(GameBase& game)
{
	game.Init(*this);

	bool done = false;
	SDL_Event sdl_event;

	using namespace std::chrono;

	auto game_begin_time = high_resolution_clock::now();

	while (!done)
	{
		PIXScopedEvent(PIX_COLOR_INDEX(0), "Frame");
		while (SDL_PollEvent(&sdl_event))
		{
			if (sdl_event.type == SDL_QUIT)
				done = true;
			else if (sdl_event.type == SDL_KEYDOWN)
			{
				switch (sdl_event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					SDL_Event event;
					event.type = SDL_QUIT;
					event.quit.type = SDL_QUIT;
					event.quit.timestamp = SDL_GetTicks();
					SDL_PushEvent(&event);
					break;
				}
			}
		}

		static int frame_counter = 0;
		const int max_frames = 5000;
		if (frame_counter >= max_frames)
			continue;

		auto frame_begin = high_resolution_clock::now();

		milliseconds fixed_dt(16);
		{
			PIXScopedEvent(PIX_COLOR_INDEX(1), "Update");
			game.Update(fixed_dt.count() / 1000.0f);
		}
		{
			PIXScopedEvent(PIX_COLOR_INDEX(2), "Render");
			SDL_RenderClear(renderer);
			game.Render();
		}

		auto frame_middle = high_resolution_clock::now();
		frame_counter++;
		RenderText(std::format("Frame:     {}", frame_counter), { 0, 0 });
		RenderText(std::format("Time:      {:.3f}", duration_cast<milliseconds>(frame_middle - game_begin_time).count() / 1000.0f), { 0, 60 });
		RenderText(std::format("Score:     {}", game.tank ? game.tank->score : 0), { 0, 120 });
		RenderText(std::format("Accuracy:  {:.2f}", game.tank && game.tank->numShots != 0 ? ((float)game.tank->score / game.tank->numShots) : 0.0f), { 0, 180 });


		auto frame_end = high_resolution_clock::now();
		auto frame_time = duration_cast<milliseconds>(frame_end - frame_begin);

		SDL_RenderPresent(renderer);

		if (lock60fps)
			if (frame_time < fixed_dt)
				std::this_thread::sleep_for(fixed_dt - frame_time);
	}
}

void Framework::RenderText(const std::string& text, const Point& position)
{
	auto surface = TTF_RenderText_Solid(font->font, text.c_str(), SDL_Color{ 255, 255, 255 });
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect;
	rect.x = (int)position.x;
	rect.y = (int)position.y;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}