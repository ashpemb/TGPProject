#include "Level1.h"
#include "Pause.h"
#include "AppDelegate.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "stdio.h"
USING_NS_CC;
using namespace cocostudio::timeline;
#include <algorithm>
using namespace std;

Scene* Level1::createScene()
{
	// 'scene' is an autorelease object
	auto sceneLevel1 = Scene::createWithPhysics();
	sceneLevel1->getPhysicsWorld()->setGravity(Vec2(0, 0));

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

	gameScore = new Score();

	_score = (cocos2d::ui::Text*)rootNode->getChildByName("Score");

	player = Player::create();
	player->setName("Player");
	player->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 80));
	rootNode->addChild(player);

	spawner = Spawner::create();
	rootNode->addChild(spawner);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Level1::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Level1::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Level1::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Level1::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);
	touching = false;

	_btnPause = static_cast<ui::Button*>(rootNode->getChildByName("Pause"));
	_btnPause->addTouchEventListener(CC_CALLBACK_2(Level1::PauseButtonPressed, this));

	auto collisionListener = EventListenerPhysicsContact::create();
	collisionListener->onContactBegin = CC_CALLBACK_1(Level1::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener, rootNode);

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->getInstance()->preloadBackgroundMusic("level1music.mp3");
	audio->getInstance()->playBackgroundMusic("level1music.mp3", true);

	this->scheduleUpdate();
	this->schedule(schedule_selector(Level1::updateScoreSecond), 1.0f / newScore);

	return true;
}

void Level1::update(float delta)
{
	player->setTouchPos(touchPos, touching);
	//CCLOG("player pos %f, %f", player->getPositionX(), player->getPositionY());

	int displayScore = gameScore->getScore();
	_score->setString(StringUtils::format("%d", displayScore));
}

void Level1::updateScoreSecond(float something)
{
	gameScore->updateScore(newScore);
}

bool Level1::onContactBegin(PhysicsContact& contact)
{
	for (auto collision : vector<pair<PhysicsShape*, PhysicsShape*>>{
		{contact.getShapeA(), contact.getShapeB()},
		{contact.getShapeB(), contact.getShapeA()} })
	{
		PhysicsBody* body = collision.first->getBody();
		PhysicsBody* otherBody = collision.second->getBody();
		if (body->getCategoryBitmask() == Enemy::categoryBitmask
			&& otherBody->getCategoryBitmask() == Bullet::categoryBitmaskPlayerBullet)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(body->getNode()->getParent());
			enemy->health -= 10.0f;
			if (enemy->health <= 0)
			{
				enemy->die();
				gameScore->updateScore(10);
			}
		}
		else if (body->getCategoryBitmask() == Bullet::categoryBitmaskPlayerBullet
			&& otherBody->getCategoryBitmask() == Enemy::categoryBitmask)
		{
			body->getNode()->getParent()->getParent()->removeChild(body->getNode()->getParent());
		}
		else if (body->getCategoryBitmask() == Player::categoryBitmask
			&& otherBody->getCategoryBitmask() == Enemy::categoryBitmask)
		{
			CCDirector::getInstance()->replaceScene(GameOver::createScene());
		}
		else if (body->getCategoryBitmask() == Player::categoryBitmask
			&& otherBody->getCategoryBitmask() == Bullet::categoryBitmaskEnemyBullet)
		{
			CCDirector::getInstance()->replaceScene(GameOver::createScene());
		}
	}
	
	return false;//dont solve collision
}

void Level1::PauseButtonPressed(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("touch ended.");
		this->OpenPauseMenu();
	}
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

void Level1::OpenPauseMenu()
{
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}