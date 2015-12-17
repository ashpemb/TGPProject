#pragma once

#include <string>
using namespace std;
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
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
	static const string hitSound;
	static const string shootSound;
	static const string dieSound;
};

