#include "Spaceship.h"

Spaceship::Spaceship()
{
	rect_.x = SCREEN_WIDTH / 2;
	rect_.y = SCREEN_HEIGHT - SHIP_HEIGHT;
	rect_.w = SHIP_WIDTH;
	rect_.h = SHIP_HEIGHT;

	x_val_ = 0;
	y_val_ = 0;
}

Spaceship::~Spaceship()
{

}

void Spaceship::Show(SDL_Renderer* des)
{
	Render(des);
}


void Spaceship::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
		{
			y_val_ -= SHIP_SPEED;
		}
		break;

		case SDLK_s:
		{
			y_val_ += SHIP_SPEED;
		}
		break;

		case SDLK_a:
		{
			x_val_ -= SHIP_SPEED;
		}
		break;

		case SDLK_d:
		{
			x_val_ += SHIP_SPEED;
		}
		break;
		case SDLK_SPACE:
		{
			BulletObject* p_bullet = new BulletObject();
			p_bullet->LoadImg("img//blaster0.png", screen);
			p_bullet->SetRect(this->rect_.x + SHIP_WIDTH * 0.5, rect_.y - SHIP_HEIGHT + 30);
			p_bullet->set_y_val(10);
			p_bullet->set_is_move(true);

			p_bullet_list_.push_back(p_bullet);
		}
		break;
		}	
	}

	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
		{
			y_val_ += SHIP_SPEED;
		}
		break;

		case SDLK_s:
		{
			y_val_ -= SHIP_SPEED;
		}
		break;

		case SDLK_a:
		{
			x_val_ += SHIP_SPEED;
		}
		break;

		case SDLK_d:
		{
			x_val_ -= SHIP_SPEED;
		}
		break;
		}
	}

	
}

void Spaceship::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}

	
}

void Spaceship::Move()
{
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + SHIP_WIDTH > SCREEN_WIDTH)
	{
		rect_.x -= x_val_;
	}
	
	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + SHIP_HEIGHT > SCREEN_HEIGHT)
	{
		rect_.y -= y_val_;
	}
}