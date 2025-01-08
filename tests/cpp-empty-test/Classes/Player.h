#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player(cocos2d::Layer *layer);

	cocos2d::Vec2 GetPosition();

	void Update(float dt);
	void Jump();

	bool isJumping = false;
	bool isMoving = false;
	bool facingLeft = true;

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *playerSprite;

	float velocityY;
	float groundY = 0.f;

};

#endif // __PLAYER_H__