#pragma once
//http://blog.csdn.net/u012424148/article/details/52792472  ����̨��ɫ
#ifndef __BATTLE_H__
#define __BATTLE_H__
#include "Monster.h"
#include "Player.h"
class Battle {
public:
	//����ս��ϵͳ��������ɹ���������
	Battle(Player &player);
	~Battle();
	void beginBattle();
	bool showResult();//չʾ������Ҵ���ս��Ʒ������ֵ���棺���ﱻ����   �٣��������ֱ�ӻسǣ���ʼ״̬
private:
	Monster *monster;
	Player &player;
	int backupPlayerLife;//ս��ǰ��������������ʱ��ָ�
	int backupPlayerEnergy;//ս��ǰ����ֵ����������ʱ��ָ�
	void showAttrPanel();//��ʾ�������
	int judegeEnd();//1 ���Ӯ  -1 ����Ӯ  0 ����ս��
};
#endif // !__BATTLE_H__
