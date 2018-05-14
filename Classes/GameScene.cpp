#include "HelloWorldScene.h"
#include "GameScene.h"

Scene* GameScene::createScene() {

	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;

}

void GameScene::DrawGridWindow(const int interval, const Color4F& color)
{
	const int WIN_WIDTH = Director::getInstance()->getWinSize().width;
	const int WIN_HEIGHT = Director::getInstance()->getWinSize().height;

	DrawNode* node = DrawNode::create();
	for (int i = interval; i < WIN_HEIGHT; i += interval)
		node->drawLine(Vec2(0, i), Vec2(WIN_WIDTH, i), color);
	for (int i = interval; i < WIN_WIDTH; i += interval)
		node->drawLine(Vec2(i, 0), Vec2(i, WIN_HEIGHT), color);

	this->addChild(node);
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode e, Event *){

	Sprite* spr = (Sprite*)this->getChildByName("player");

	if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
	
		++toggle; vec = -3;
	}
	if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){

		++toggle; vec = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_SPACE){
		Action* act_bounce = JumpBy::create(0.4, Point(0, 0), 50, 1);
		spr->runAction(act_bounce);
	}

}


void GameScene::onKeyReleased(EventKeyboard::KeyCode e, Event *){

	Sprite* spr = (Sprite*)this->getChildByName("player");

	if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
		--toggle; vec = 3;
	}
	if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
		--toggle; vec = -3;
	}

}

bool GameScene::onTouchBegan(Touch* touch, Event* unusedEvent) {

	CCLOG("MOUSE EVENTS");

	Sprite* spr = (Sprite*)this->getChildByName("backScene");

	if (spr->getBoundingBox().containsPoint(touch->getLocation())) {
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1, HelloWorld::createScene());
		Director::getInstance()->replaceScene(scene);
	}

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(0, 200);

	if ((Sprite*)this->getChildByName("backScene")->getBoundingBox().containsPoint(touch->getLocation())) {
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}

	if (((Sprite*)this->getChildByName("letUsSnowy"))->getBoundingBox().containsPoint(touch->getLocation())) {

		Sprite* spr_Snow = Sprite::create("Winter_96px.png");
		spr_Snow->setPosition(num(rng) * 5, num(rng) + 500);
		spr_Snow->setScale(0.5);
		this->addChild(spr_Snow, 1, "snow");
		vec_snow.push_back(spr_Snow);    
		ccBezierConfig bez1;
		bez1.controlPoint_1 = Point(num(rng) * 7 - 200, num(rng) + 300);
		bez1.controlPoint_2 = Point(num(rng) * 7 - 200, num(rng) + 100);
		bez1.endPosition = Point(num(rng) * 7 - 200, -100);

		Action* act_Snowy = BezierTo::create(8, bez1);
		spr_Snow->runAction(act_Snowy);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::update(float dt) {

	CCLOG("%d , %d", toggle, vec);

	Sprite* spr_player = (Sprite*)this->getChildByName("player");
//	Sprite* spr_snow = (Sprite*)this->getChildByName("snow");
	
	if (toggle == 2) {
		spr_player->setPosition(spr_player->getPosition().x + vec, spr_player->getPosition().y);
	}
	if (toggle == 1) {
		spr_player->setPosition(spr_player->getPosition().x + vec, spr_player->getPosition().y);
	}
	for (int i = 0; i < vec_snow.size();) {
		if (vec_snow[i]->getBoundingBox().containsPoint(spr_player->getPosition())) {
			
			Sprite* spr_explosion = (Sprite*)this->getChildByName("explosion");
			spr_explosion->setPosition(vec_snow[i]->getPosition());
			//this->addChild(spr_explosion);

			this->removeChild(vec_snow[i]);
			vec_snow.erase(vec_snow.begin() + i);
			point++;
			
		}
		else if (vec_snow[i]->getPosition().y < 0) {
			this->removeChild(vec_snow[i]);
			vec_snow.erase(vec_snow.begin() + i);

		}
		else i++;
	}
	auto label = (Label*)this->getChildByName("point");
	label->setString(StringUtils::format("Point : %d", point));

}

///////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::init() {

	if (!Layer::init()) {


		return false;
	}

	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	Sprite* spr_Pill = Sprite::create("Pill_96px.png");
	spr_Pill->setPosition(100, 100);
	this->addChild(spr_Pill, 0, "backScene");

	Sprite* spr_IronMan = Sprite::create("Iron_Man_96px.png");
	spr_IronMan->setPosition(500, 50);
	spr_IronMan->setScale(0.7);
	this->addChild(spr_IronMan, 0, "player");
	 
	Sprite* spr_Sleet = Sprite::create("Sleet_96px.png");
	spr_Sleet->setPosition(100, 700);
	this->addChild(spr_Sleet, 0, "letUsSnowy");

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	EventListenerKeyboard* listner = EventListenerKeyboard::create();
	listner->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listner->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);

	auto label_point = Label::createWithSystemFont("", "", 20);
	label_point->setPosition(950, 700);
	this->addChild(label_point, 5, "point");
	
	auto ani_explosion = Animation::create();
	ani_explosion->setDelayPerUnit(0.05);

	Sprite* spr_explostion = Sprite::create("pixelExplosion00.png");
	spr_explostion->setPosition(500, 500);
	this->addChild(spr_explostion,0,"explosion");

	for (int i = 0; i < 8; i++) {

		ani_explosion->addSpriteFrameWithFile(StringUtils::format("pixelExplosion%02d.png", i));
	}
	auto ani_explosion_ani = Animate::create(ani_explosion);
	auto act_ani_explosion = RepeatForever::create(ani_explosion_ani);
	spr_explostion->runAction(act_ani_explosion);
	
	this->scheduleUpdate();

	return true;
}
