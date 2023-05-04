#pragma once
#ifndef SDL_UTITLS_H_
#define SDL_UTITLS_H_
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Music* gMusic = NULL;
static SDL_Texture* g_menu = NULL;

static Mix_Chunk* g_sound_bullet;
static Mix_Chunk* g_sound_explosion;
static Mix_Chunk* g_sound_chicken;

const int CHICKEN_NUM = 5;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;
const int SCREEN_BPP = 32;
const int RENDER_DRAW_COLOR = 0xff;

const int COLOR_KEY_R = 170;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 170;

namespace SDL_Utils
{
	bool isCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	SDL_Texture* LoadImg(std::string path, SDL_Renderer* screen);
	bool CheckFocusWithRect(int x, int y, const SDL_Rect& rect);
	int ShowMenu(SDL_Renderer* des, TTF_Font* font);
}





#endif 