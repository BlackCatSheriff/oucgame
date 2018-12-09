#include <iostream>
#include <ctime>
#include "Item.h"
#include "ConstTable.h"
using namespace std;

Item::Item() {
	unsigned seed = static_cast<unsigned>(time(NULL));
	srand(seed);
	id = SHOPLIST[rand() % SHOPLISTCOUNT];
	value = 0;
}
Item::~Item() {}

Item::Item(std::string id, int value)
{
	this->id = id;
	this->value = value;
}
std::string Item::getId()const {//�õ�������ҩˮ������
	return id;
}
int Item::getValue()const {//�õ�������ҩˮ�ļ�ֵ
	return value;
}

void Item::setId(std::string name)
{
	this -> id = name;
}
