#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	Scene* scene = HelloWorld::create();

	return scene;
}

bool HelloWorld::init()
{
	
	if (!Scene::init())
	{
		return false;
	}
	
	this->createWorld();

	auto listener_keyboard = EventListenerKeyboard::create();
	listener_keyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener_keyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_keyboard, this);

	this->layer_inven();
	this->scheduleUpdate();

	return true;
}

bool HelloWorld::createWorld()
{

	for (int i = 0; i < 10; i++) {

		auto spr = Sprite::create("tree_1.png");
		spr->setPosition(50 + 50 * i, 50 + 50 * i);
		spr_tree.push_back(spr);
		this->addChild(spr_tree[i]);

	}


	auto spr_man = Sprite::create("man.png");
	spr_man->setPosition(winsize.width / 2, winsize.height / 2);
	this->addChild(spr_man, 1, "man");
	
	return true;

}

bool HelloWorld::layer_inven()
{
	layer_spr_inven = Layer::create();

	auto spr_inven = Sprite::create("inven.png");
	spr_inven->setScale(0.3);
	layer_spr_inven->addChild(spr_inven, 2, "inven");
	spr_inven->setVisible(true);
	this->addChild(layer_spr_inven);

	auto spr_man = Sprite::create("man.png");
	spr_man->setScale(1.5);
	spr_man->setPosition(-80, 70);
	layer_spr_inven->addChild(spr_man, 3);

	auto label_name = Label::createWithSystemFont("", "", 34,
		Size(300, 100), TextHAlignment::CENTER, TextVAlignment::CENTER);

	layer_spr_inven->addChild(label_name, 3, "label_name");

	return true;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode e, Event *) {

	CCLOG("keyPressed");

	Sprite* spr = (Sprite*)this->getChildByName("man");

	if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

		++toggle_keyboard; vec = -3;
	}
	if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {

		++toggle_keyboard; vec = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

		++toggle_keyboard_1; vec_1 = -3;
	}
	if (e == EventKeyboard::KeyCode::KEY_UP_ARROW) {

		++toggle_keyboard_1; vec_1 = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_I) {

		if (toggle_layer_inven)
			toggle_layer_inven = false;
		else toggle_layer_inven = true;
		CCLOG("toggle_inven");
	}

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode e, Event *) {

	Sprite* spr = (Sprite*)this->getChildByName("man");

	if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		--toggle_keyboard; vec = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		--toggle_keyboard; vec = -3;
	}
	if (e == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		--toggle_keyboard_1; vec_1 = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		--toggle_keyboard_1; vec_1 = -3;
	}

}

void HelloWorld::update(float dt)
{
	Sprite* spr_man = (Sprite*)this->getChildByName("man");
	pos_man = spr_man->getPosition();

	if (toggle_keyboard == 2) {
		spr_man->setPosition(spr_man->getPosition().x + vec, spr_man->getPosition().y);
	}
	if (toggle_keyboard == 1) {
		spr_man->setPosition(spr_man->getPosition().x + vec, spr_man->getPosition().y);
	}
	if (toggle_keyboard_1 == 2) {
		spr_man->setPosition(spr_man->getPosition().x , spr_man->getPosition().y + vec_1);
	}
	if (toggle_keyboard_1 == 1) {
		spr_man->setPosition(spr_man->getPosition().x , spr_man->getPosition().y + vec_1);
	}
	
	if (toggle_layer_inven)layer_spr_inven->setVisible(true);
	else layer_spr_inven->setVisible(false);

	layer_spr_inven->setPosition(pos_man.x + 330, pos_man.y + 200);
	
	Label* label_name = (Label*)layer_spr_inven->getChildByName("label_name");
	
	//label_name->setString();


	auto follow = Follow::create(spr_man, Rect::ZERO);
	this->runAction(follow);
}
