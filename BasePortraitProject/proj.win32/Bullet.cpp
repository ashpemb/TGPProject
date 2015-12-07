#include "Bullet.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Bullet* Bullet::create(Vec2 position, Vec2 direction)
{
	Bullet* bullet = new Bullet();
	if (!bullet->init())
	{
		CC_SAFE_DELETE(bullet);
		return nullptr;
	}
	bullet->autorelease();

	bullet->setPosition(position);
	bullet->setRotation(-CC_RADIANS_TO_DEGREES(direction.getAngle()));
	bullet->direction = direction;
	
	return bullet;
}

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* sprite = Sprite::create("bullet.png");
	addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void Bullet::update(float delta)
{
	setPosition(getPosition() + direction * speed * delta);
	if (getBoundingBox().getMaxY() < 0 || getBoundingBox().getMinY() > Director::getInstance()->getVisibleSize().height)
	{
		getParent()->removeChild(this);
	}
}
