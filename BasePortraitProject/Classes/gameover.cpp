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

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->getInstance()->preloadBackgroundMusic("GameOvermusic.mp3");
	audio->getInstance()->playBackgroundMusic("GameOvermusic.mp3", true);

	return true;
}
