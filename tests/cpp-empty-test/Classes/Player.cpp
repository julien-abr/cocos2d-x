#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

Player::Player(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	groundY = visibleSize.height / 2 + origin.y - 260;

	playerSprite = Sprite::create("Assets/horseman.png");
	playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 140));

	auto playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
	playerSprite->setPhysicsBody(playerBody);

	layer->addChild(playerSprite, 100);
}

cocos2d::Vec2 Player::GetPosition()
{
	return playerSprite->getPosition();
}

void Player::Update(float dt)
{
	if (isMoving)
	{
		if (facingLeft)
		{
			playerSprite->setFlippedX(false);
			playerSprite->setPositionX(playerSprite->getPositionX() - (PLAYER_MOVE_SPEED * dt));
		}
		else
		{
			playerSprite->setFlippedX(true);
			playerSprite->setPositionX(playerSprite->getPositionX() + (PLAYER_MOVE_SPEED * dt));
		}
	}

	if (isJumping)
	{
		velocityY += GRAVITY * dt; 
		playerSprite->setPositionY(playerSprite->getPositionY() + velocityY * dt);

		if (playerSprite->getPositionY() <= visibleSize.height / 2 + origin.y - 150)
		{
			playerSprite->setPositionY(visibleSize.height / 2 + origin.y - 140);
			isJumping = false;                 
			velocityY = 0;                      
		}
	}
}

void Player::Jump()
{
	isJumping = true;
	velocityY = JUMP_IMPULSE;
}
