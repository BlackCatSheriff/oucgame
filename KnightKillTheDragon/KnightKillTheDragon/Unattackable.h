#pragma once
#ifndef __UNATTACKABLE_H__
#define __UNATTACKABLE_H__
#include "Role.h"
#include "Container.h"
class Unattackable :public Role
{
public:
	Unattackable(Container &shop);
	virtual ~Unattackable();
	void showInfo()const;//�鿴NPC���ԣ�����Container show����
private:
	Container &shop;
};

#endif // !__UNATTACKABLE_H__
