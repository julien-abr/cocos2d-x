#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player(cocos2d::Layer *layer);

	void Update(float dt);
	bool isMoving = false;
	bool facingLeft = true;

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *playerSprite;

};

#endif // __PLAYER_H__