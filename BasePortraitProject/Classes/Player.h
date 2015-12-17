#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
#include <algorithm>
#include <string>
using namespace std;
#include "Bullet.h"
#include "Enemy.h"

class Player : public Node
{
public:
	Player();
	~Player();

	virtual bool init() override;
	static Player* create();
	void update(float delta);
	void shoot(float);
	void setTouchPos(Vec2 pos, bool touching);

	float speed = 150;
	float fireRate = 5;
	Vec2 touchPos;
	bool touching;

	static const int categoryBitmask = 0x2;
	static const string dieSound;
};

