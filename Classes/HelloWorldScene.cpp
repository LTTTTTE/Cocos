#include "HelloWorldScene.h"
#include "GameScene.h"

Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::create();

	HelloWorld* layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

void HelloWorld::DrawGridWindow(const int interval, const Color4F& color)
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

bool HelloWorld::onTouchBegan(Touch* touch, Event* unusedEvent) {
	
	CCLOG("MOUSE EVENTS");
	
	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(0, 200);

	if ((Sprite*)this->getChildByName("backScene")->getBoundingBox().containsPoint(touch->getLocation()) ) {
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1, GameScene::createScene() );
		Director::getInstance()->replaceScene(scene);
	}
	
	if (((Sprite*)this->getChildByName("letUsSnowy"))->getBoundingBox().containsPoint(touch->getLocation())) {
		
		Sprite* spr_Snow = Sprite::create("Winter_96px.png");
		spr_Snow->setPosition(num(rng)*5, num(rng)+500);
		spr_Snow->setScale(0.5);
		this->addChild(spr_Snow);

		ccBezierConfig bez1;
		bez1.controlPoint_1 = Point(num(rng) * 7 - 200 , num(rng) + 300);
		bez1.controlPoint_2 = Point(num(rng) * 7 - 200 , num(rng) + 100);
		bez1.endPosition = Point(num(rng) * 7 - 200 , -100);

		Action* act_Snowy = BezierTo::create(8, bez1);
		spr_Snow->runAction(act_Snowy);
	}

	return true;
}


bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	Sprite* spr_Pill = Sprite::create("Pill_96px.png");
	spr_Pill->setPosition(700, 500);
	this->addChild(spr_Pill, 0, "backScene");

	Sprite* spr_Sleet = Sprite::create("Sleet_96px.png");
	spr_Sleet->setPosition(100, 700);
	this->addChild(spr_Sleet, 0, "letUsSnowy");

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	return true;
}
