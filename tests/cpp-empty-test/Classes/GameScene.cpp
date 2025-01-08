#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto skySprite = Sprite::create("Assets/Sky.png");
    auto montainsSprite = Sprite::create("Assets/Mountains.png");
    auto groundSprite = Sprite::create("Assets/Ground.png");

    float skyScaleX = visibleSize.width / skySprite->getContentSize().width;
    float skyScaleY = visibleSize.height / skySprite->getContentSize().height;

    float mountainsScaleX = visibleSize.width / montainsSprite->getContentSize().width;
    float mountainsScaleY = visibleSize.height / montainsSprite->getContentSize().height;

    float groundScaleX = visibleSize.width / groundSprite->getContentSize().width;
    float groundScaleY = visibleSize.height / groundSprite->getContentSize().height;

    // Apply scale
    skySprite->setScale(skyScaleX, skyScaleY);
    skySprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    montainsSprite->setScale(mountainsScaleX, mountainsScaleY);
    montainsSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    groundSprite->setScale(groundScaleX, groundScaleY);
    groundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(skySprite);
    this->addChild(montainsSprite);

    // Add physics body for the ground
    auto groundBody = PhysicsBody::createBox(
        Size(visibleSize.width, visibleSize.height / 20),
        PhysicsMaterial(0.0f, 0.0f, 0.0f) // No bounce, no friction
    );
    groundBody->setDynamic(false); // Static body for ground (doesn't move)
    groundBody->setContactTestBitmask(true); // Enable collision callbacks
    groundBody->setPositionOffset(Vec2(0, -260));
    groundSprite->setPhysicsBody(groundBody);
    this->addChild(groundSprite);

    //Add collision edge
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);



    this->addChild(edgeNode);

    return true;
}

void GameScene::SetPhysicsWorld(cocos2d::PhysicsWorld* world)
{
    sceneWorld = world;
}
