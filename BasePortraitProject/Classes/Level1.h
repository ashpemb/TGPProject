#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "stdio.h"

#include <iomanip>
USING_NS_CC;
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Spawner.h"
#include "gameover.h"
#include "Score.h"

using namespace std;

class Level1 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void update(float delta);

	bool onContactBegin(PhysicsContact& contact);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* touchEvent);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* touchEvent);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* touchEvent);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* touchEvent);

	void PauseButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void OpenPauseMenu();

	void updateScoreSecond(float);

	// implement the "static create()" method manually
	CREATE_FUNC(Level1);

	Player* player;
	Spawner* spawner;

	Vec2 touchPos;
	bool touching;


private:
	cocos2d::ui::Button*    _btnPause;
	cocos2d::ui::Text*		_score;
	int						newScore = 1;
};

#endif // __LEVEL1_SCENE_H__
