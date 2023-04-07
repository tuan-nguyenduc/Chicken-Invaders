#include "ChickenObject.h"

ChickenObject::ChickenObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT / 2;
	x_val_ = 0;
	y_val_ = 0;
	frame_ = 0;

}

ChickenObject::~ChickenObject()
{

}

void ChickenObject::set_clips()
{
	for (int i = 0;i < 18;i++) {
		frame_clip_[i].x = i * CHICKEN_WIDTH;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = CHICKEN_WIDTH;
		frame_clip_[i].h = CHICKEN_HEIGHT;
	}
}

void ChickenObject::Show(SDL_Renderer* screen)
{
	frame_++;
	if (frame_ >= 18)
	{
		frame_ = 0;
	}
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, CHICKEN_WIDTH, CHICKEN_HEIGHT };
	SDL_RenderCopy(screen, p_object_, current_clip, &renderQuad);
}

void ChickenObject::Move(const int& x_border, const int& y_border)
{
	rect_.y += y_val_;
	if (rect_.y > SCREEN_HEIGHT)
	{
		rect_.y = 0;
		int rand_x = rand() % 1150;
		if (rand_x < 50) {
			rand_x = SCREEN_HEIGHT * 0.3;
		}
		rect_.x = rand_x;
	}

}

void ChickenObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* des)
{
	if (p_bullet != NULL)
	{
		bool ret = p_bullet->LoadImg("img//egg.png", des);
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->SetRect(this->rect_.x + CHICKEN_WIDTH * 0.35, rect_.y);
			p_bullet->set_y_val(CHICKEN_BULLET_SPEED);
			p_bullet_list_.push_back(p_bullet);
		}
	}
}

void ChickenObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->Render(des);
				p_bullet->HandleMoveEgg(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				p_bullet->SetRect(this->rect_.x + CHICKEN_WIDTH * 0.35, this->rect_.y + CHICKEN_HEIGHT);
				p_bullet->set_is_move(true);
			}
		}
	}
}