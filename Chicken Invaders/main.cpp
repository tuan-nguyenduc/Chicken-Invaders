#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include "Spaceship.h"

BaseObject g_background;

bool Init()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (ret < 0)
	{
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Chicken Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		return false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}
	}
	return success;
}

bool LoadBackground()
{
	bool ret = g_background.LoadImg("img//bkground.png", g_screen);
	if (ret == false)
	{
		return false;
	}
	return true;
}

bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load music
	gMusic = Mix_LoadMUS("sound//background_music.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

void Close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

int main(int argc, char* argv[])
{
	if (Init() == false)
	{
		return -1;
	}

	if (LoadBackground() == false)
	{
		return -1;
	}

	if (LoadMedia() == false)
	{
		return -1;
	}


	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(gMusic, -1);
	}

	Spaceship spaceship;
	spaceship.LoadImg("img//spacecraft.png", g_screen);

	bool is_quit = false;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			spaceship.HandleInputAction(g_event, g_screen);
		};
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		spaceship.HandleBullet(g_screen);
		spaceship.Show(g_screen);
		spaceship.Move();
		SDL_RenderPresent(g_screen);
	}

	Close();
	return 0;
}