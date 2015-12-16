#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "Bullet.h"
#include "Player.h"

class Enemy : public Node
{
public:
	Enemy();
	~Enemy();

	virtual bool init() override;
	static Enemy* create(Node* target);
	void update(float delta);
	void shoot();
	void die();

	float speed = 100;
	float health = 30.0f;
	Node* target;

	static const int categoryBitmask = 0x1;
};

