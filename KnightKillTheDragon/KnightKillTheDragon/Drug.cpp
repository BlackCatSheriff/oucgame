#include <iostream>
#include<iomanip>
using namespace std;
#include"Drug.h"

Drug::Drug() {}//Ĭ�Ϲ��캯��
Drug::Drug(std::string id, int value, char type, int weight) :Item(id, value) {
	this->type = type;
	this->weight = weight;
}//����ҩˮ�����ֺͼ�ֵ

Drug::~Drug() {}

//��ӡ��ҩˮ������
void Drug::showInfo() {
	cout << setw(6) << "����" << setw(8) << "��ֵ" << setw(8) << "����" << setw(8) << "�ɻָ���" << endl;
	cout << setw(6) << getId() << setw(8) << getValue() << setw(8) << getType() << setw(8) << getWeight() << endl;
}
char Drug::getType()const
{
	return type;
}
int Drug::getWeight()const
{
	return weight;
}