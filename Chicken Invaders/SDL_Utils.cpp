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

bool SDL_Utils::CheckFocusWithRect(int x, int y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
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
    pos_arr[0].x = 700;
    pos_arr[0].y = 550;

    pos_arr[1].x = 700;
    pos_arr[1].y = 650;

    TextObject text_menu[menuItemNum];
    text_menu[0].setText("Play Game");
    text_menu[0].setColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].setText("Exit");
    text_menu[1].setColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    bool selected[menuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;

    SDL_Event mouse_event;
    SDL_Rect text_rect[menuItemNum];

    while (true)
    {
        SDL_RenderCopy(des, g_menu, NULL, NULL);
        for (int i = 0; i < menuItemNum; ++i)
        {
            text_menu[i].LoadFromRenderText(font, des);
            text_rect[i] = text_menu[i].GetRectAfterRenderText(des, text_menu[i].GetRect().x, text_menu[i].GetRect().y);
        }

        while (SDL_PollEvent(&mouse_event))
        {
            switch (mouse_event.type)
            {
            case SDL_QUIT:
            {
                return 1;
            }

            break;
            case SDL_MOUSEMOTION:
            {
                xm = mouse_event.motion.x;
                ym = mouse_event.motion.y;

                for (int i = 0; i < menuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_rect[i]))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].setColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].setColor(TextObject::WHITE_TEXT);
                        }
                    }


                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = mouse_event.button.x;
                ym = mouse_event.button.y;
                for (int i = 0; i < menuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, text_rect[i]))
                    {
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (mouse_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            }
            default:
                break;
            }
        }
        SDL_RenderPresent(des);
    }
    
}