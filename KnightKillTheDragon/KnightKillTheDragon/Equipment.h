#ifndef _EQUIPMENT_H
#define _EQUIPMENT_H
#include <string>
#include "Item.h"
//#include "Player.h"
class Equipment :public Item
{
public:
	Equipment(std::string id, int value, int power, int consume, int protectPower, int movePower);//���캯����ʼ�����������ƺͼ�ֵ�����Ե�
	~Equipment();
	Equipment(const Equipment &equipment);//���ƹ��캯��
	void showInfo();///��ӡ����������

	int getPower()const; //��������Ĺ�����
						 //int setPower();

	int getConsume()const;//����������;�

	int getProtectPower()const;//��������ķ����������ף�
							   //int setProtectPower();

	int getMovePower()const; //����������ƶ��ٶ�
							 //int setMovePower();
	Equipment();
	void initEquipment(int index,int money);//ͨ�������ı���ж�������Ʒ��ͨ����Ǯ��Ӧ�������ԣ��õ�һ���������Ե�ʵ��,û����������
private:
	int power; //װ���Ĺ�����
	int consume;//װ�����;�
	int protectPower;//����
	int movePower;//�ƶ��ٶ�
};


#endif // !_EQUIPMENT_H
#pragma once

