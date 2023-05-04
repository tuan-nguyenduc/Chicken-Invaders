#include "SDL_Utils.h"
#include "BaseObject.h"
#include "TextObject.h";

bool SDL_Utils::isCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    //object 1 > object2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    //object1 < object2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    //object1 = object2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

SDL_Texture* SDL_Utils::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
    }
    new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
    SDL_FreeSurface(load_surface);

    return new_texture;
    
}


int SDL_Utils::ShowMenu(SDL_Renderer* des, TTF_Font* font)
{
    g_menu = LoadImg("img//img_menu.png", des);
    if (g_menu == NULL)
    {
        return 1;
    }

    const int menuItemNum = 2;
    SDL_Rect pos_arr[menuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 500;

    TextObject text_menu[menuItemNum];
    text_menu[0].setText("Play Game");
    text_menu[0].setColor(TextObject::BLACK_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].setText("Exit");
    text_menu[1].setColor(TextObject::BLACK_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);


    while (true)
    {
        SDL_RenderCopy(des, g_menu, NULL, NULL);
        for (int i = 0; i < menuItemNum; ++i)
        {
            text_menu[i].LoadFromRenderText(font, des);
            text_menu[i].RenderText(des, text_menu[i].GetRect().x, text_menu[i].GetRect().y);
        }
        SDL_RenderPresent(des);
    }
    
}