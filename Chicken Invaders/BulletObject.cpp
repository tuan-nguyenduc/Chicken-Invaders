#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	if (is_move_ == true)
	{
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}

}

void BulletObject::HandleMoveEgg(const int& x_border, const int& y_border)
{
	rect_.y += y_val_;
	if (rect_.y > y_border)
	{
		is_move_ = false;
	}
}
