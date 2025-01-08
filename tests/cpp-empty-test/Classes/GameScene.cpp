#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

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

    //Spawn player
    player = new Player(this);

    // Create a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();

    // Assign callback functions for key press and release
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::OnKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::OnKeyReleased, this);

    // Add the listener to the event dispatcher
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();
    return true;
}

void GameScene::SetPhysicsWorld(cocos2d::PhysicsWorld* world)
{
    sceneWorld = world;
}

void GameScene::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    // CCLOG("Key pressed: %d", static_cast<int>(keyCode));

    // Add the key to the active keys set
    activeKeys.insert(keyCode);

    if (player)
    {
        // Check movement keys
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            player->isMoving = true;
            player->facingLeft = true;
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_D)
        {
            player->isMoving = true;
            player->facingLeft = false;
        }

        // Jump
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !player->isJumping || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !player->isJumping)
        {
            player->Jump();
        }
    }
}

void GameScene::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    // Remove the key from the active keys set
    activeKeys.erase(keyCode);

    if (player)
    {
        // Check if any movement keys are still active
        if (activeKeys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != activeKeys.end() ||
            activeKeys.find(EventKeyboard::KeyCode::KEY_A) != activeKeys.end())
        {
            player->isMoving = true;
            player->facingLeft = true;
        }
        else if (activeKeys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != activeKeys.end() ||
            activeKeys.find(EventKeyboard::KeyCode::KEY_D) != activeKeys.end())
        {
            player->isMoving = true;
            player->facingLeft = false;
        }
        else
        {
            player->isMoving = false; // Stop moving if no movement keys are pressed
        }
    }
}

void GameScene::update(float dt)
{
    if (player)
        player->Update(dt);

    for (auto projectile : projectiles)
    {
        projectile->Update(dt);
    }
}

void GameScene::SpawnProjectile()
{
    Vec2 startPosition = player->GetPosition();
    auto projectile = new Projectile(this, startPosition);
    projectiles.push_back(projectile); 
}
