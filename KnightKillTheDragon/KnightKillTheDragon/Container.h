#pragma once
#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include <vector>
#include <string>
#include "Equipment.h"
#include "Drug.h"
#include "Item.h"
#include "Attackable.h"
class Container
{
public:
	Container(int capacity);
	Container(const Container &con);
	bool push(Item* item);//��������,�ɹ��棻װ���·��ؼ�;
	void remove(Item *item);//ɾ��item
	void showGoods();//��ʾ������Ʒ����
	int getNowSize()const;//��ȡ��ǰ��Ʒ����
	int getTotalSize()const;//��ȡ�������ܴ�С
	Item *getItemByIndex(int index);//ͨ����Ʒ��Ż�ȡ��Ʒ
	~Container();
private:
	int capacity;//��������
	int num;//����������Ʒ����
	std::vector<Item*> goods;//�����ڵ���Ʒ
};

#endif // !__CONTAINER_H__
