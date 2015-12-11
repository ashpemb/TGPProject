#include "menuscreen.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MenuScreen::createScene()
{
	// 'scene' is an autorelease object
	auto scenemenu = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScreen::create();

	// add layer as a child to scene
	scenemenu->addChild(layer);

	// return the scene
	return scenemenu;
}

// on "init" you need to initialize your instance
bool MenuScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Menu.csb");
	addChild(rootNode);

	this->scheduleUpdate();
	auto winSize = Director::getInstance()->getVisibleSize();

	//TOUCHES

	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	//Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(MenuScreen::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MenuScreen::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MenuScreen::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MenuScreen::onTouchCancelled, this);

	//Add our touch listener to event listener list.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//BUTTONS
	//Start button
	_btnStart = static_cast<ui::Button*>(rootNode->getChildByName("Start"));
	_btnStart->addTouchEventListener(CC_CALLBACK_2(MenuScreen::StartButtonPressed, this));
	_btnStart->setPosition(Vec2(winSize.width*0.5f, winSize.height*0.43f));

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->getInstance()->preloadBackgroundMusic("menumusic.mp3");
	audio->getInstance()->preloadBackgroundMusic("level1music.mp3");
	audio->getInstance()->preloadBackgroundMusic("GameOvermusic.mp3");
	audio->getInstance()->playBackgroundMusic("menumusic.mp3", true);

	return true;
}

void MenuScreen::StartButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		this->StartGame();
	}
}

void MenuScreen::StartGame()
{
	auto gameScreen = new Level1();
	CCDirector::getInstance()->replaceScene(gameScreen->createScene());
	auto winSize = Director::getInstance()->getVisibleSize();
}

//Touch Functions
bool MenuScreen::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	return true;
}

void MenuScreen::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void MenuScreen::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void MenuScreen::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}
