#include "Spawner.h"

Spawner::Spawner()
{
	
}

Spawner::~Spawner()
{

}

Spawner* Spawner::create()
{
	Spawner* spawner = new Spawner();
	if (!spawner->init())
	{
		CC_SAFE_DELETE(spawner);
		return nullptr;
	}
	spawner->autorelease();

	return spawner;
}

bool Spawner::init()
{
	if (!Node::init())
	{
		return false;
	}

	schedule(schedule_selector(Spawner::spawn), 1.0f);

	return true;
}

void Spawner::spawn(float something)
{
	Enemy* enemy = Enemy::create();
	auto winSize = Director::getInstance()->getVisibleSize();
	enemy->setPosition(RandomHelper::random_real(0.0f, winSize.width), winSize.height);
	getParent()->addChild(enemy);
}