#ifndef _DRUG_H
#define _DRUG_H
#include "Item.h"
//#include "Player.h"
class Drug :public Item
{
public:
	Drug();//Ĭ�Ϲ��캯��
	Drug(std::string id, int value, char type, int weight);//����ҩˮ�����ֺͼ�ֵ  
	void showInfo();//��ӡҩˮ������
	char getType()const;
	int getWeight()const;
	~Drug();


private:
	char type;//ҩˮ������
	int weight;//ҩˮ�ظ���������
};
#endif // !_DRUG_H
#pragma once