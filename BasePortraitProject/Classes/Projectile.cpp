#include "Projectile.h"


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

Projectile* Projectile::create(Vec2 position, Vec2 direction)
{
	Projectile* bullet = new Projectile();
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

bool Projectile::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* sprite = Sprite::create("bullet_1.png");
	addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void Projectile::update(float delta)
{
	setPosition(getPosition() + direction * delta);
}
