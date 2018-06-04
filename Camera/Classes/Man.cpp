#include "Man.h"

Man::Man() {

	name = "È«±æ¶Ë";
	level = 1;
	hp = 100;
}

void Man::setInven(_inven i)
{
	_inven _new;
	_new.item = i.item;
	_new.value = i.value;
	for (auto j : Inven) {
		if (i.item == j.item) {
			j.value += i.value;
			CCLOG("alreadyExist");
			return;
		}
	}
	Inven.push_back(_new);

}

