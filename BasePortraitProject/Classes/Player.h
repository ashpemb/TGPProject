#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
#include <algorithm>
using namespace std;
#include "Bullet.h"

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

	float speed = 120;
	float fireRate = 10;
	Vec2 touchPos;
	bool touching;
};

