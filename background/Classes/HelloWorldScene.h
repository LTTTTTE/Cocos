#include "cocos2d.h"

#pragma execution_character_set("utf-8")

USING_NS_CC;

#define winsize Director::getInstance()->getWinSize()

class HelloWorld : public Scene {

public:

	static Scene* createScene();
	virtual bool init();


	CREATE_FUNC(HelloWorld);


};

