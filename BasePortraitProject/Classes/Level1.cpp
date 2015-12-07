#include "Level1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
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

	player = Player::create();
	player->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 80));
	rootNode->addChild(player);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Level1::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Level1::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Level1::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Level1::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);
	touching = false;

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->getInstance()->preloadBackgroundMusic("level1music.mp3");
	audio->getInstance()->playBackgroundMusic("level1music.mp3", true);

	scheduleUpdate();

	return true;
}

void Level1::update(float delta)
{
	player->setTouchPos(touchPos, touching);
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
