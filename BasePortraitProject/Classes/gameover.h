#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "menuscreen.h"
#include "stdio.h"
#include "Score.h"

#include <iomanip>
USING_NS_CC;

class GameOver : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Touch input
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//Button event
	void RestartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void ExitButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

private:
// buttons
	cocos2d::ui::Button*    _btnRestart;
	cocos2d::ui::Button*	_btnExit;
	cocos2d::ui::Text*		_score;

};

#endif // __GAMEOVER_SCENE_H__
