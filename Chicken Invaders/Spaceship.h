#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include <vector>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define SHIP_SPEED 10
#define SHIP_HEIGHT 70
#define SHIP_WIDTH 57

class Spaceship : public BaseObject
{
public:
	Spaceship();
	~Spaceship();

	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void Move();
	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list() const
	{
		return p_bullet_list_;
	}

	void HandleBullet(SDL_Renderer* des);
private:
	std::vector<BulletObject*> p_bullet_list_;

	float x_val_;
	float y_val_;

};
#endif