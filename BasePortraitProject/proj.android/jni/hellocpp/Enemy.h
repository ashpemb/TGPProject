#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Enemy : public Node
{
public:
	Enemy();
	~Enemy();

	virtual bool init() override;
	static Enemy* create();
	void update(float delta);
	void die();

	float speed = 100;

	static const int categoryBitmask = 0x1;
};

