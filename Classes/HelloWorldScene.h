#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public Layer {

public:

	void DrawGridWindow(const int interval, const Color4F& color);

	bool onTouchBegan(Touch * touch, Event * unusedEvent);

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);


};
