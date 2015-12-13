#include "Pause.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scenemenu = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scenemenu->addChild(layer);

	// return the scene
	return scenemenu;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("PauseScene.csb");
	addChild(rootNode);

	this->scheduleUpdate();
	auto winSize = Director::getInstance()->getVisibleSize();

	//TOUCHES

	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	//Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(PauseScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PauseScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PauseScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(PauseScene::onTouchCancelled, this);

	//Add our touch listener to event listener list.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//BUTTONS
	//Start button
	_btnResume = static_cast<ui::Button*>(rootNode->getChildByName("Resume"));
	_btnResume->addTouchEventListener(CC_CALLBACK_2(PauseScene::ResumeButtonPressed, this));

	_btnQuit = static_cast<ui::Button*>(rootNode->getChildByName("Quit"));
	_btnQuit->addTouchEventListener(CC_CALLBACK_2(PauseScene::QuitButtonPressed, this));


	return true;
}

void PauseScene::ResumeButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		this->ReturnToGame();
	}
}

void PauseScene::ReturnToGame()
{
	Director::getInstance()->popScene();
}

void PauseScene::QuitButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		this->QuitToMenu();
	}
}

void PauseScene::QuitToMenu()
{
	auto Menu = MenuScreen::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(Menu);
}

//Touch Functions
bool PauseScene::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	return true;
}

void PauseScene::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void PauseScene::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void PauseScene::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}
