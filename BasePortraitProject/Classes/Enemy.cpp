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
	sprite->setRotation(CC_DEGREES_TO_RADIANS(180));
	addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void Enemy::update(float delta)
{
	
}
