#include "gameover.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocostudio::timeline;
#include <algorithm>
using namespace std;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto sceneGameOver = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	sceneGameOver->addChild(layer);

	// return the scene
	return sceneGameOver;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("GameOver.csb");
	addChild(rootNode);

	this->scheduleUpdate();
	auto winSize = Director::getInstance()->getVisibleSize();

	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	//Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameOver::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameOver::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameOver::onTouchCancelled, this);

	//Add our touch listener to event listener list.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	_btnRestart = static_cast<ui::Button*>(rootNode->getChildByName("Restart"));
	_btnRestart->addTouchEventListener(CC_CALLBACK_2(GameOver::RestartButtonPressed, this));
	_btnRestart->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.60f));

	_btnExit = static_cast<ui::Button*>(rootNode->getChildByName("Exit"));
	_btnExit->addTouchEventListener(CC_CALLBACK_2(GameOver::ExitButtonPressed, this));
	_btnExit->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.40f));

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//audio->getInstance()->preloadBackgroundMusic("gameOvermusic.mp3");
	audio->getInstance()->playBackgroundMusic("gameOvermusic.mp3", true);

	return true;
}

void GameOver::RestartButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		auto gameScreen = new MenuScreen();
		CCDirector::getInstance()->replaceScene(gameScreen->createScene());
		auto winSize = Director::getInstance()->getVisibleSize();
	}
}

void GameOver::ExitButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		CCDirector::sharedDirector()->end();
	}
}

bool GameOver::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	return true;
}

void GameOver::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void GameOver::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void GameOver::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}
