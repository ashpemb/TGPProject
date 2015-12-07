#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Level1.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "stdio.h"

#include <iomanip>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

class MenuScreen : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScreen);

	// Touch input
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//Button event
	void StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);


	void StartGame();

private:
	cocos2d::ui::Button*    _btnStart;

};


#endif // __MENU_SCENE_H__
