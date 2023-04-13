#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include "Spaceship.h"
#include "ChickenObject.h"
#include "BulletObject.h"
#include <vector>


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
	bool ret = g_background.LoadImg("img//bkground1.png", g_screen);
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

	//Init spaceship
	Spaceship* spaceship = new Spaceship();
	spaceship->LoadImg("img//spacecraft.png", g_screen);

	//Init chickens
	ChickenObject* chickens = new ChickenObject[CHICKEN_NUM];

	for (int c = 0; c < CHICKEN_NUM; c++)
	{
		ChickenObject* chicken = (chickens + c);
		if (chickens != NULL)
		{
			chicken->LoadImg("img//chicken.png", g_screen);
			chicken->set_clips();
			int rand_x = rand() % 1150;
			if (rand_x < 50) {
				rand_x = SCREEN_HEIGHT * 0.3;
			}
			chicken->SetRect(rand_x, SCREEN_HEIGHT -  c * 400);
			chicken->set_y_val_(CHICKEN_SPEED);
			//Init chicken egg
			BulletObject* p_bullet = new BulletObject();
			chicken->InitBullet(p_bullet, g_screen);
		}
	}



	bool is_quit = false;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			spaceship->HandleInputAction(g_event, g_screen);
		};
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		spaceship->Move();
		spaceship->Show(g_screen);
		spaceship->HandleBullet(g_screen);
		

		for (int cc = 0; cc < CHICKEN_NUM; cc++)
		{
			ChickenObject* chicken = (chickens + cc);
			if (chicken != NULL)
			{
				chicken->Move(SCREEN_WIDTH, SCREEN_HEIGHT);
				chicken->Show(g_screen);
				chicken->HandleBullet(g_screen);

				// Handle Collision of spaceship and chickens and eggs
				SDL_Rect sRect = spaceship->GetRect();
				SDL_Rect cRect = chicken->GetRectFrame();

				// Collision of spaceship and eggs
				bool sCol1 = false;
				// Collision of spaceship and chickens
				bool sCol2 = false;

				std::vector<BulletObject*> eggs_list = chicken->getBulletList();
				for (int e = 0; e < eggs_list.size(); ++e)
				{
					BulletObject* egg = eggs_list.at(e);
					if (egg != NULL)
					{
						sCol1 = SDL_Utils::isCollision(egg->GetRect(), sRect);
						if (sCol1)
						{
							chicken->RemoveBullet(e);
							break;
						}
					}
				}
				sCol2 = SDL_Utils::isCollision(sRect, cRect);

				if (sCol1 || sCol2)
				{
					if (MessageBox(NULL, L"Game Over!",L"Info", MB_OK || MB_ICONSTOP) == IDOK)
					{
						chicken->Free();
						Close();
						SDL_Quit();
						return 0;
					}
				}


			}
		}

		// Handle Collision of bullet and chickens
		std::vector<BulletObject*> bullet_list = spaceship->get_bullet_list();
		for (int b = 0; b < bullet_list.size(); ++b)
		{
			BulletObject* bullet = bullet_list.at(b);
			if (bullet != NULL)
			{
				for (int c = 0; c < CHICKEN_NUM;++c)
				{
					ChickenObject* chicken = (chickens + c);
					if (chicken != NULL)
					{
						
						SDL_Rect cRect = chicken->GetRectFrame();
						SDL_Rect bRect = bullet->GetRect();

						bool bCol = SDL_Utils::isCollision(bRect, cRect);

						if (bCol)
						{
							spaceship->RemoveBullet(b);
							chicken->Reset(SCREEN_HEIGHT + c * 400);
						}
					}
				}
			}
		}

		
		SDL_RenderPresent(g_screen);
	}

	Close();
	return 0;
}