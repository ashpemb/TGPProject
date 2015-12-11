#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "Enemy.h"

class Spawner : public Node
{
public:
	Spawner();
	~Spawner();

	virtual bool init() override;
	static Spawner* create();
	void spawn(float);
};