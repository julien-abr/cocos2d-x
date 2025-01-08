#include "Projectile.h"
#include "Definitions.h"

USING_NS_CC;

Projectile::Projectile(cocos2d::Layer* layer, const cocos2d::Vec2& startPosition)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // Create the projectile sprite
    projectileSprite = Sprite::create("Assets/Blaster.png");
    projectileSprite->setPosition(startPosition);

    // Create the physics body for the projectile
    auto projectileBody = PhysicsBody::createBox(projectileSprite->getContentSize());
    projectileBody->setDynamic(true);
    projectileBody->setVelocity(Vec2(0, PROJECTILE_SPEED)); // Set upward velocity
    projectileSprite->setPhysicsBody(projectileBody);

    // Add the projectile to the layer
    layer->addChild(projectileSprite, 100);

void Projectile::Update(float dt)
{
	if (projectileSprite->getPositionY() > visibleSize.height + projectileSprite->getContentSize().height)
	{
		projectileSprite->removeFromParentAndCleanup(true); // Remove if out of bounds
	}
}
