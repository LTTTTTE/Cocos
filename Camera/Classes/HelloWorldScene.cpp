#include "HelloWorldScene.h"

std::random_device rd;
std::mt19937_64 _MT19937(rd());

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
	if (e == EventKeyboard::KeyCode::KEY_SPACE) {

		if (isjumped == 0) {
			isjumped++;
		}
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
	auto follow = Follow::create(spr_man, Rect::ZERO);
	this->runAction(follow);
}
