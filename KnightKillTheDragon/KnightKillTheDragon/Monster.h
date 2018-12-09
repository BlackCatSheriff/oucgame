#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "Attackable.h"
#include "Equipment.h"
class Monster:public Attackable
{
public:
	Monster(Equipment *equipment);
	virtual ~Monster();
	virtual void showInfo()const;//�鿴��������
	Equipment *getItem()const;//���ص�����Ʒ

private:
	 Equipment *equipment;//�����װ��
};

#endif // !__MONSTER_H__
