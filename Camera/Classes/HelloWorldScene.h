#include "cocos2d.h"

#pragma execution_character_set("utf-8")

USING_NS_CC;

#define winsize Director::getInstance()->getWinSize()
#define MT19937 std::uniform_int_distribution<__int64>

class HelloWorld : public Scene {

public:

	int toggle_keyboard = 0;
	int toggle_keyboard_1 = 0;
	int vec = 0;
	int vec_1 = 0;
	int point = 0;
	bool toggle_layer_inven = 0;

	Vec2 pos_man;
	Layer* layer_spr_inven;

	static Scene* createScene();
	virtual bool init();

	bool createWorld();
	bool layer_inven();
	std::vector<Sprite*>spr_tree;

	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);

	void update(float dt);

	CREATE_FUNC(HelloWorld);

};

