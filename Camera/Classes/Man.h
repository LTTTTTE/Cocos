#pragma once

#include "cocos2d.h"

#pragma execution_character_set("utf-8")

USING_NS_CC;

#define winsize Director::getInstance()->getWinSize()

typedef struct {

	std::string item;
	int value;

}_inven;

class Man
{
public:

	std::vector<_inven>Inven;

	std::string name;
	int level;
	int hp;
	
	Man();

	std::string getName() { return name; }
	int getLevel() { return level; }
	int getHp() { return hp; }

	void setInven(_inven i);
};

