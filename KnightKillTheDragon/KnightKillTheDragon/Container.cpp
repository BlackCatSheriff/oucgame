#include "Container.h"
#include "Item.h"
#include "Equipment.h"
#include "Drug.h"
#include "Attackable.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;



Container::Container(int capacity) :capacity(capacity) {}

Container::Container(const Container & con)
{
	this->capacity = con.capacity;
	this->num = con.num;
	for (unsigned i = 0; i < con.goods.size(); i++) {
		(this->goods).push_back(con.goods[i]);
	}
}

bool Container::push(Item* item){
	num = 0;
	++num;
	if (num <= capacity) {
		goods.push_back(item);//����Ʒ���뱳��
		//cout << "The good has been put in your bag!" << endl;
		return true;
	}
	else {
		//cout << "Sorry,your bag is full!" << endl;
		--num;
		return false;
	}
}

void Container::remove(Item * item){
	vector<Item*>goods_;
	//vector<Item*>::iterator it;
	//for (it = goods.begin(); it != goods.end(); ++it)
	//	if (*it == item)
	//		break;
	//for (vector<Item*>::iterator it1 = goods.begin(); it1 != goods.end(); ++it1) {
	//	if (it1 == it)
	//		continue;
	//	goods_.push_back(*it1);
	//}
	//�õ�������֭����fuck
	unsigned i = 999999;
	for (i = 0; i < goods.size(); i++)
		if (goods[i] == item)
			break;
	for (unsigned j = 0; j < goods.size(); j++) {
		if (j == i)
			continue;
		goods_.push_back(goods[j]);
	}
	
	goods = goods_;
	//ɾ��������Ʒ���ҵ���˳���ٿ�һ��VECTOR push ��ȥ������item����һ��goods��ָ��
}

void Container::showGoods()
{
	//cout << "����������" << endl;
	int index=0;
	for (unsigned i = 0; i < goods.size(); i++)
		cout <<i+1 <<"."<<goods[i]->getId() <<"\t";
	cout << endl;
	/*for (vector<Item*>::iterator it = goods.begin(); it != goods.end(); ++it)
		cout << (++index) << "." << *it << "\t\t";
	cout << endl;*/
}

int Container::getNowSize() const
{
	return static_cast<int>( goods.size());
}

int Container::getTotalSize() const
{
	return this->capacity;
}


Item * Container::getItemByIndex(int index)
{
	return goods[index];
}

Container::~Container() {

}


