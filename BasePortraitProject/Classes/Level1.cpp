#include "Level1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio::timeline;
#include <algorithm>
using namespace std;

Scene* Level1::createScene()
{
	// 'scene' is an autorelease object
	auto sceneLevel1 = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level1::create();

	// add layer as a child to scene
	sceneLevel1->addChild(layer);

	// return the scene
	return sceneLevel1;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("Level_1.csb");
	addChild(rootNode);

	player = CSLoader::createNode("Player.csb")->getChildByName<Sprite*>("playerShip");
	rootNode->addChild(player);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Level1::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Level1::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Level1::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Level1::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);
	touching = false;

	scheduleUpdate();

	return true;
}

void Level1::update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();
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
	addChild(Bullet::create(player->getPosition() + Vec2(0, 50), Vec2(0, 1)));
	//CCLOG("player pos %f, %f", player->getPositionX(), player->getPositionY());
}

bool Level1::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchBegan");
	touchPos = touch->getLocation();
	touching = true;
	return true;
}

void Level1::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchEnded");
	touching = false;
}

void Level1::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchMoved");
	touchPos = touch->getLocation();
	touching = true;
}

void Level1::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* touchEvent)
{
	CCLOG("TouchCancelled");
	touching = false;
}
