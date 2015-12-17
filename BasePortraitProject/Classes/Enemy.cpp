#include "Enemy.h"

const string Enemy::hitSound = "enemy_hit.wav";
const string Enemy::shootSound = "enemy_shoot.wav";
const string Enemy::dieSound = "enemy_die.wav";

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(Node* target = nullptr)
{
	Enemy* enemy = new Enemy();
	if (!enemy->init())
	{
		CC_SAFE_DELETE(enemy);
		return nullptr;
	}
	enemy->autorelease();

	enemy->target = target;
	
	return enemy;
}

bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* sprite = Sprite::create("enemy_0.png");
	sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getBoundingBox().size));
	sprite->getPhysicsBody()->setContactTestBitmask(Bullet::categoryBitmaskPlayerBullet | Player::categoryBitmask);
	sprite->getPhysicsBody()->setCategoryBitmask(categoryBitmask);
	sprite->getPhysicsBody()->setCollisionBitmask(Bullet::categoryBitmaskPlayerBullet | Player::categoryBitmask);
	addChild(sprite);

	this->scheduleUpdate();
	float interval = RandomHelper::random_real<float>(2, 10);
	int bullets = (int)(pow(RandomHelper::random_real<float>(0, 1), 2) * 3);
	if (bullets > 0)
	{
		Vector<FiniteTimeAction*> bulletActions;
		for (int i = 0; i < bullets; i++)
		{
			bulletActions.pushBack(DelayTime::create(RandomHelper::random_real<float>(0.5f, 1.5f)));
			bulletActions.pushBack(CallFunc::create(CC_CALLBACK_0(Enemy::shoot, this)));
		}
		runAction(Sequence::create(bulletActions));
	}

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

void Enemy::shoot()
{
	//if (getPositionY() <= Director::sharedDirector()->getVisibleSize().height) return;
	Vec2 shootDir(0, -1);
	if (target)
	{
		shootDir = (target->getPosition() - getPosition());
		shootDir.normalize();
	}
	Bullet* bullet = Bullet::create(getPosition() + Vec2(0, -50), shootDir, false);
	bullet->speed *= 0.5f;
	getParent()->addChild(bullet);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(shootSound.c_str());
}

void Enemy::die()
{
	//add score, explode, etc
	getParent()->removeChild(this);
	SimpleAudioEngine::getInstance()->playEffect(dieSound.c_str());
}
