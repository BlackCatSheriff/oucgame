#include<iostream>
#include<iomanip>
using namespace std;
#include"Equipment.h"
#include "ConstTable.h"

Equipment::Equipment(std::string id, int value, int power, int consume, int protectPower, int movePower) :Item(id, value) {
	this->power = power;
	this->consume = consume;
	this->protectPower = protectPower;
	this->movePower = movePower;
}//���캯����ʼ�����������ƺͼ�ֵ�����Ե�
Equipment::~Equipment() {}

Equipment::Equipment(const Equipment & equipment):Item(equipment.getId(),equipment.getValue())
{
	this->power = equipment.power;
	this->consume = equipment.consume;
	this->protectPower = equipment.protectPower;
	this->movePower = equipment.movePower;
}

//��ӡ����������
void Equipment::showInfo() {
	cout << setw(6) << "����" << setw(8) << "��ֵ" << setw(8) << "������";
	cout << setw(8) << "�;�" << setw(8) << "������" << setw(8) << "����" << endl;
	cout << setw(6) << getId() << setw(8) << getValue() << setw(8) << getPower();
	cout << setw(8) << getConsume() << setw(8) << getProtectPower() << setw(8) << getMovePower() << endl;
}

//���������Ĺ�����������
int Equipment::getPower()const {
	return power;
}
// int Equipment::setPower() {}

int Equipment::getConsume()const {
	return consume;
}
int Equipment::getProtectPower()const {
	return protectPower;
}
//int Equipment::setProtectPower() {}

int Equipment::getMovePower()const {
	return movePower;
}
//int Equipment::setMovePower()


Equipment::Equipment():Item("",0),power(0),consume(0),protectPower(0),movePower(0)
{
}

void Equipment::initEquipment(int index, int money)
{
	setId(SHOPLIST[index]);
	switch (index)
	{
	case 0: //�� knife
		power += money * KNIFEPOWER;
		consume += money * KNIFECONSUME;
		break;
	case 1: //��Sword
		power += money * SWORDPOWER;
		consume += money * SWORDCONSUME;
		break;
	case 2: //����Bow
		power += money * BOWPOWER;
		consume += money * BOWCONSUME;
	case 3: //����Stabwound
		power += money * STABPOWER;
		consume += money * STABCONSUME;
		protectPower += money * STABPROTECTPOWER;
		break;
	case 4: //�� shield
		consume += money * SHIELDCONSUME;
		protectPower += money * SHIELDPROTECTPOWER;
		break;
	case 5: //Ь��Shoe
		consume += money * SHOECONSUME;
		movePower += money * SHOEMOVEPOWER;
		break;
	default:
		break;
	}

}


