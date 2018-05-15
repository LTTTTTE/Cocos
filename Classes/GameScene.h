#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Layer {

public:

	void DrawGridWindow(const int interval, const Color4F& color);

	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	bool onTouchBegan(Touch * touch, Event * unusedEvent);
	void removeNode(Node * node);
	virtual void update(float dt);

	static Scene* createScene();

	virtual bool init();

	std::vector<Sprite*> vec_snow;
	std::vector<Sprite*> vec_explosion;
	int toggle = 0;
	int vec = 0;
	int point = 0;

	CREATE_FUNC(GameScene);
	


};