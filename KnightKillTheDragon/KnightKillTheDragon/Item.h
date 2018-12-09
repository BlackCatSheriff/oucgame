#ifndef _ITEM_H
#define _ITEM_H
#include <string>
class Item
{
public:
	Item();
	Item(std::string id, int value);
	~Item();
	std::string getId() const;//�õ�������ҩˮ������	
	int getValue() const;//�õ�������ҩˮ�ļ�ֵ
	virtual void showInfo() = 0;//��ӡ������ҩˮ������
	void setId(std::string name);//��������
private:
	std::string id;//��Ʒ������
	int value;//��Ʒ�ļ�ֵ
};
#endif // !__ITEM_H__

#pragma once

