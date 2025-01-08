#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

Player::Player(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	playerSprite = Sprite::create("Assets/horseman.png");
	playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 140));

	auto playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
	playerSprite->setPhysicsBody(playerBody);

	layer->addChild(playerSprite, 100);
}

void Player::Update(float dt)
{
	if (!isMoving)
		return;

	if (facingLeft)
		playerSprite->setPositionX(playerSprite->getPositionX() - (PLAYER_MOVE_SPEED * dt));
	else
		playerSprite->setPositionX(playerSprite->getPositionX() + (PLAYER_MOVE_SPEED * dt));
}
