#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

Player* Player::create()
{
	Player* player = new Player();
	if (!player->init())
	{
		CC_SAFE_DELETE(player);
		return nullptr;
	}
	player->autorelease();

	return player;
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	Sprite* sprite = Sprite::create("player.png");
	addChild(sprite);

	this->scheduleUpdate();
	this->schedule(schedule_selector(Player::shoot), 1.0f / fireRate);

	return true;
}

void Player::update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();
	if (touching)
	{
		float mappedTouchX = (touchPos.x / winSize.width) * 2 - 1;//[-1, 1]
		float moveDirection = 0;
		float deadZone = 0.01f;
		if (abs(mappedTouchX) > deadZone)
		{
			moveDirection = mappedTouchX > 0 ? 1 : -1;
		}
		float newPos = getPositionX() + moveDirection * speed * delta;
		float playerHalfWidth = getBoundingBox().size.width / 2;
		setPositionX(max(playerHalfWidth, min(winSize.width - playerHalfWidth, newPos)));
	}
}

void Player::shoot(float something)
{
	getParent()->addChild(Bullet::create(getPosition() + Vec2(0, 50), Vec2(0, 1)));
}

void Player::setTouchPos(Vec2 pos, bool touching)
{
	touchPos = pos;
	this->touching = touching;
}
