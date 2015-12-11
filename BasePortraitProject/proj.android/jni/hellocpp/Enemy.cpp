#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create()
{
	Enemy* enemy = new Enemy();
	if (!enemy->init())
	{
		CC_SAFE_DELETE(enemy);
		return nullptr;
	}
	enemy->autorelease();
	
	return enemy;
}

bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* sprite = Sprite::create("player.png");
	sprite->setRotation(180);
	sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	sprite->getPhysicsBody()->setContactTestBitmask(0x1);
	sprite->getPhysicsBody()->setCategoryBitmask(categoryBitmask);
	addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void Enemy::update(float delta)
{
	setPositionY(getPositionY() - speed * delta);
	if (!getBoundingBox().intersectsRect(Rect(Director::getInstance()->getVisibleOrigin(), Director::getInstance()->getVisibleSize())))
	{
		getParent()->removeChild(this);
	}
}

void Enemy::die()
{
	//add score, explode, etc
	getParent()->removeChild(this);
}
