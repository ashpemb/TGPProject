#include "Level1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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

	return true;
}
