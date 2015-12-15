#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "Enemy.h"

class Bullet : public Node
{
public:
	Bullet();
	~Bullet();

	virtual bool init() override;
	static Bullet* create(Vec2 position, Vec2 direction);
	void update(float delta);

	Vec2 direction;
	float speed = 400;

	static const int categoryBitmask = 0x4;
};

