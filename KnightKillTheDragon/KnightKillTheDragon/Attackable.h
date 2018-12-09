#pragma once
#ifndef __ATTACKABLE_H__
#define __ATTACKABLE_H__
#include "Role.h"
#include <string>
class Attackable:public Role 
{
public:
	Attackable();
	Attackable(std::string name, int pos_x, int pos_y, int life, 
				int power , int exp , int protectPower , 
				int level , int money);
	virtual ~Attackable();
	int getLife()const;
	void setLife(int life);
	int getPower()const;
	void setPower(int power);
	int getProtectPower()const;
	void setProtectPower(int protectPower);
	int getExp()const;
	virtual void setExp(int exp);//���þ���
	int getLevel()const;
	void setLevel(int level);
	int getMoney()const;
	void setMoney(int money);

private:
	int life;//����ֵ
	int power;//������
	int protectPower;//����
	int exp;//����
	int level;//�ȼ�
	int money;//��Ǯ
};

#endif // !__ATTACKABLE_H__
