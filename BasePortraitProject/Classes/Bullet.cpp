#include "Bullet.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Bullet* Bullet::create(Vec2 position, Vec2 direction, bool friendly)
{
	Bullet* bullet = new Bullet();
	bullet->friendly = friendly;
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
	sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	if (friendly)
	{
		sprite->getPhysicsBody()->setCategoryBitmask(categoryBitmaskPlayerBullet);
		sprite->getPhysicsBody()->setContactTestBitmask(Enemy::categoryBitmask);
		sprite->getPhysicsBody()->setCollisionBitmask(Enemy::categoryBitmask);
	}
	else
	{
		sprite->getPhysicsBody()->setCategoryBitmask(categoryBitmaskEnemyBullet);
		sprite->getPhysicsBody()->setContactTestBitmask(Player::categoryBitmask);
		sprite->getPhysicsBody()->setCollisionBitmask(Player::categoryBitmask);
	}
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
