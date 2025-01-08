#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"

class Projectile
{
public:
	Projectile(cocos2d::Layer* layer, const cocos2d::Vec2& startPosition);

	void Update(float dt);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* projectileSprite;
};

#endif // __PROJECTILE_H__