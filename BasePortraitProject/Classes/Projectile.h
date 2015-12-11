#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Projectile : public Node
{
public:
	Projectile();
	~Projectile();

	virtual bool init() override;
	static Projectile* create(Vec2 position, Vec2 direction);
	void update(float delta);

	Vec2 direction;
};

