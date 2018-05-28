#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	Scene* scene = HelloWorld::create();

	return scene;
}
//

bool HelloWorld::init()
{

	if (!Scene::init())
	{
		return false;
	}

/*	auto layer_background = Layer::create();
	this->addChild(layer_background);
	
	auto spr_bg1 = Sprite::create("background_1.png");
	spr_bg1->setAnchorPoint(Point(0, 0));
	layer_background->addChild(spr_bg1);

	auto spr_bg2 = Sprite::create("background_2.png");
	spr_bg2->setAnchorPoint(Point(0, 0));
	spr_bg2->setPosition(1900, 0);
	layer_background->addChild(spr_bg2);

	auto spr_bg3 = Sprite::create("background_1.png");
	spr_bg3->setAnchorPoint(Point(0, 0));
	spr_bg3->setPosition(3800, 0);
	layer_background->addChild(spr_bg3);

	auto act_rep = RepeatForever::create(Sequence::create(MoveBy::create(16, Point(-3800, 0)), Place::create(Vec2(0, 0)), NULL));

	layer_background->runAction(act_rep);
	*/

	auto node = ParallaxNode::create();
	this->addChild(node);

	auto act_1 = MoveBy::create(10, Point(-2800, 0));
	auto act_2 = Place::create(Point(0, 0));
	auto act_3 = Sequence::create(act_1, act_2, NULL);
	auto act_4 = RepeatForever::create(act_3);
	node->runAction(act_4);

	auto spr_1 = Sprite::create("background_sky.png");
	spr_1->setAnchorPoint(Point(0, 0));
	node->addChild(spr_1, 0, Point(1, 0), Point(0, 0));

	auto spr_1_1= Sprite::create("background_sky.png");
	spr_1->setAnchorPoint(Point(0, 0));
	node->addChild(spr_1_1, 0, Point(1, 0), Point(2800, 0));


	auto spr_2 = Sprite::create("background_ground.png");
	spr_2->setAnchorPoint(Point(0, 0));
	node->addChild(spr_2, 0, Point(2, 0), Point(0, 0));

	auto spr_2_1 = Sprite::create("background_ground.png");
	spr_2_1->setAnchorPoint(Point(0, 0));
	node->addChild(spr_2_1, 0, Point(2, 0), Point(2800, 0));

	return true;
}
//
