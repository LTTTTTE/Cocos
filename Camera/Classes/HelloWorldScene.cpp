#include "HelloWorldScene.h"
#include "Man.h"

Man* Player = new Man();

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

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener_keyboard = EventListenerKeyboard::create();
	listener_keyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener_keyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_keyboard, this);

	this->layer_inven();
	this->scheduleUpdate();
	
	[] {
		CCLOG("Hi");
	}();

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

	auto spr_inven_1 = Sprite::create("inven_1.png");
	spr_inven_1->setScale(0.65);
	spr_inven_1->setPosition(0, -60);
	layer_spr_inven->addChild(spr_inven_1, 3, "inven_1");

	auto spr_inven_2 = Sprite::create("inven_2.png");
	spr_inven_2->setScale(0.7);
	spr_inven_2->setAnchorPoint(Point(0, 0));
	spr_inven_2->setVisible(false);
	layer_spr_inven->addChild(spr_inven_2, 4, "inven_2");

	auto spr_man = Sprite::create("man.png");
	spr_man->setScale(1.5);
	spr_man->setPosition(-80, 70);
	layer_spr_inven->addChild(spr_man, 3);

	auto label_name = Label::createWithSystemFont("", "", 15,
		Size(100, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_name->setPosition(20, 90);
	layer_spr_inven->addChild(label_name, 3, "label_name");

	auto label_level = Label::createWithSystemFont("", "", 15,
		Size(100, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_level->setPosition(20, 70);
	layer_spr_inven->addChild(label_level, 3, "label_level");

	auto label_hp = Label::createWithSystemFont("", "", 15,
		Size(100, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_hp->setPosition(20, 50);
	layer_spr_inven->addChild(label_hp, 3, "label_hp");

	auto spr_apple = Sprite::create("Red_Apple.png");
	spr_apple->setPosition(-111, -12);
	spr_apple->setScale(0.12);
	layer_spr_inven->addChild(spr_apple, 3, "spr_apple");

	inven_item.push_back(spr_apple);

	auto spr_wood = Sprite::create("Wood.png");
	spr_wood->setPosition(-80, -12);
	spr_wood->setScale(0.12);
	spr_wood->setScaleX(0.09);
	layer_spr_inven->addChild(spr_wood, 3, "spr_wood");

	inven_item.push_back(spr_wood);

	auto spr_leaf = Sprite::create("Leaf_48px.png");
	spr_leaf->setPosition(-111, -43);
	spr_leaf->setScale(0.5);
	layer_spr_inven->addChild(spr_leaf, 3, "spr_leaf");

	inven_item.push_back(spr_leaf);

	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) 
{
	CCLOG("%f %f", touch->getLocation().x, touch->getLocation().y);

	for (int i = 0; i < inven_item.size();i++) {

		CCLOG("tried");
		CCLOG("(%f , %f)", inven_item[i]->getBoundingBox().getMidX(), inven_item[i]->getBoundingBox().getMidY());

		if (inven_item[i]->getBoundingBox().containsPoint( touch->getLocation())) {
			auto inven_2 = ((Sprite*)this->getChildByName("inven_2"));
			inven_2->setVisible(true);
			inven_2->setPosition(touch->getLocation());
			CCLOG("inven_info");
		}
	}

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
	label_name->setString(Player->getName());

	Label* label_level = (Label*)layer_spr_inven->getChildByName("label_level");
	label_level->setString(StringUtils::format("Level : %d ",Player->getLevel()));
	
	Label* label_hp = (Label*)layer_spr_inven->getChildByName("label_hp");
	label_hp->setString(StringUtils::format("Level : %d ", Player->getHp()));


	auto follow = Follow::create(spr_man, Rect::ZERO);
	this->runAction(follow);
}
