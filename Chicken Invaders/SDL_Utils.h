#pragma once
#ifndef SDL_UTITLS_H_
#define SDL_UTITLS_H_
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Music* gMusic = NULL;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;
const int SCREEN_BPP = 32;
const int RENDER_DRAW_COLOR = 0xff;

const int COLOR_KEY_R = 170;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 170;

#endif 