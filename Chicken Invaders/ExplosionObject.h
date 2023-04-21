#pragma once
#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_
#include "SDL_Utils.h"
#include "BaseObject.h"

#define EXPLOSION_FRAME_NUM 8
#define EXPLOSION_WIDTH_FRAME 150
#define EXPLOSION_HEIGHT_FRAME 160

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

	void set_clips();
	void set_frame(const int& frame) { frame_ = frame; }
	int get_frame() const { return frame_; };
	void Show(SDL_Renderer* screen);


private:
	int frame_;
	SDL_Rect frame_clip_[8];

};

#endif
