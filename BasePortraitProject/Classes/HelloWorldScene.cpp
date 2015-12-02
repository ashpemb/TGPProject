#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <algorithm>
#include "SimpleAudioEngine.h"

using namespace std;

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("Player.csb");

    addChild(rootNode);

	player = rootNode->getChildByName<Sprite*>("playerShip");

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);
	touching = false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->getInstance()->preloadBackgroundMusic("level1music.mp3");
	audio->getInstance()->playBackgroundMusic("level1music.mp3", true);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	
	if (touching)
	{
		float mappedTouchX = (touchPos.x / winSize.width) * 2 - 1;//[-1, 1]
		float moveDirection = 0;
		float deadZone = 0.01f;
		if (abs(mappedTouchX) > deadZone)
		{
			moveDirection = mappedTouchX > 0 ? 1 : -1;
		}
		float newPos = player->getPositionX() + moveDirection * playerSpeed * delta;
		float playerHalfWidth = player->getBoundingBox().size.width / 2;
		player->setPositionX(max(playerHalfWidth, min(winSize.width - playerHalfWidth, newPos)));
	}
	//CCLOG("player pos %f, %f", player->getPositionX(), player->getPositionY());
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchBegan");
	touchPos = touch->getLocation();
	touching = true;
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchEnded");
	touching = false;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchMoved");
	touchPos = touch->getLocation();
	touching = true;
}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchCancelled");
	touching = false;
}
