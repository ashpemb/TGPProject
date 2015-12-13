#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "Level1.h"
#include "menuscreen.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "stdio.h"

#include <iomanip>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

class PauseScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PauseScene);

	// Touch input
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//Button event
	void ResumeButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void QuitButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void ReturnToGame();
	void QuitToMenu();

private:
	cocos2d::ui::Button*    _btnResume;
	cocos2d::ui::Button*	_btnQuit;

};


#endif // __PAUSE_SCENE_H__