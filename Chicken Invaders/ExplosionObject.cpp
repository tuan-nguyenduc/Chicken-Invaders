#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clips()
{
	for (int i = 0; i < 8; i++)
	{
		frame_clip_[i].x = i * EXPLOSION_WIDTH_FRAME;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = EXPLOSION_WIDTH_FRAME;
		frame_clip_[i].h = EXPLOSION_HEIGHT_FRAME;
	}
}

void ExplosionObject::Show(SDL_Renderer* screen)
{
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, EXPLOSION_WIDTH_FRAME, EXPLOSION_HEIGHT_FRAME };
	if (current_clip != NULL)
	{
		renderQuad.w = current_clip->w;
		renderQuad.h = current_clip->h;
	}

	SDL_RenderCopy(screen, p_object_, current_clip, &renderQuad);
}

