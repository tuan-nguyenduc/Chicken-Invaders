#pragma once
#ifndef CHICKEN_OBJECT_H_
#define CHICKEN_OBJECT_H_

#include "SDL_Utils.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define CHICKEN_WIDTH 75
#define CHICKEN_HEIGHT 68
#define CHICKEN_SPEED 2
#define CHICKEN_BULLET_SPEED 5

class ChickenObject : public BaseObject
{
public:
	ChickenObject();
	~ChickenObject();

	void set_x_val_(const int& xVal) { x_val_ = xVal; }
	void set_y_val_(const int& yVal) { y_val_ = yVal; }
	int get_x_val_() { return x_val_; }
	int get_y_val_() { return y_val_; }

	void Move(const int& x_border, const int& y_border);
	void set_clips();
	void Show(SDL_Renderer* screen);

	void setBulletList(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
	std::vector<BulletObject*> getBulletList() const { return p_bullet_list_; }
	void InitBullet(BulletObject* p_bullet, SDL_Renderer* des);
	void HandleBullet(SDL_Renderer* des);

private:
	int x_val_;
	int y_val_;


	std::vector<BulletObject*> p_bullet_list_;
	int frame_;
	SDL_Rect frame_clip_[18];
};



#endif
