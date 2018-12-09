#pragma once
#ifndef __CONSTTABLE_H__
#define __CONSTTABLE_H__

const int WALL = 0;
const int ROAD = 1;
const int DOOR = 2;
const int NPC = 4;
const int PLAYER = 1;
const int MONSTER = -1;
const int MISSLOWER = 1;
const int MISSUPPER = 200;
const int BORNX = 5;   //��ʼλ��x
const int BORNY = 14;	//��ʼλ��y
const int BORNLIFE = 120; //��ʼ����ֵ
const int MAXLIFE = 250;//������ֵ
const int BORNPOWER = 25;	//��ʼ������
const int BORNPROTECTPOWER = 8;	//��ʼ������
const int BORNEXP = 0; //��ʼ����ֵ
const int BORNLEVEL = 1; //��ʼ�ȼ�
const int BORNMONEY = 100;	//��ʼ��Ǯ
const int BORNENERGY = 10; //��ʼ����ֵ
const int MAXENERHY = 50;//������ֵ
const int BORNMISS = 30; //��ʼ����ֵ
const int BORNSPEED = 1; //��ʼ�ٶ�
const int MONSTERMAXNUM = 15;//��ͼ����������
const int SHOPLISTCOUNT = 6;//�����������Ŀ
const std::string SHOPLIST[SHOPLISTCOUNT] = { "��","��","����","����","����","Ь��" };//�����궫��
//const std::string SHOPLIST[SHOPLISTCOUNT] = { "DAO","JIAN","GONGJIAN","KAIJIA","DUNPAI","XIEZI" };//�����궫��
const int WAREHOUSE = 3;//��ͼ�������ֿ�
const int WEAPONHOUSE = 4;//��ͼ������������
const int HOSPITAL = 5;//��ͼ������ҽԺ
const char PLAYERATTR = 't';//����ͼ�����ͼֱ������A����������
const char PLAYERBAG = 'b';//����ͼ�����ͼֱ������B�����ﱳ��
const char MAINMENUE = 'm';//����ͼ�����ͼֱ������M�ص������棬�����Զ��浵
const int MAPROW = 12;
const int MAPCOLUMN = 50;
const int KNIFEPOWER = 1;        //���Ĺ���������
const int KNIFECONSUME = 1;      //�����;ò���
const int SWORDPOWER = 1;        //���Ĺ���������
const int SWORDCONSUME = 1;      //�����;ò���
const int SHOECONSUME = 1;       //Ь���;ò���
const int SHOEMOVEPOWER = 1;     //Ь���ƶ��ٶȲ���
const int BOWPOWER = 1;          //�����Ĺ���������
const int BOWCONSUME = 1;        //�������;ò���
const int STABPOWER = 1;         //���׵Ĺ���������
const int STABCONSUME = 1;       //���׵��;ò���
const int STABPROTECTPOWER = 1;  //���׵ķ���������
const int SHIELDCONSUME = 1;     //�ܵ��;ò���
const int SHIELDPROTECTPOWER = 1;//�ܵķ���������
const int WARESHOPCAPACITY = 25;    //�ֿ��С
const int BAGCOUNTCAPACITY = 10;	//������С
const int MONSTERLISTCOUNT = 10;	//������������
const std::string MONSTERLIST[MONSTERLISTCOUNT] = { "�ʹ���","������","�ǹ���","��������",
												"�Ӳ���","�ǲ���" ,"ɵ����" ,"̫����" ,
													"������" ,"��ѩ�ǹ���"};	//��������
const int INITMONSTERLIFE = 80;//��͵ȼ��Ĺ�����ֵ����������ĵȼ�����������������
const int INITMONSTERPOWER = 10;//��͵ȼ��Ĺֹ���������������ĵȼ�����������������
const int INITMONSTEREXP = 5;//��͵ȼ��Ĺ־��飬��������ĵȼ�����������������
const int INITMONSTERMONEY = 10;//��͵ȼ��Ĺֽ�Ǯ����������ĵȼ�����������������
const int INITMONSTERKPROTECTPOWER = 6;//��͵ȼ��Ĺַ���������������ĵȼ�����������������
const int DRAGONLIFE = 1000;
const int DRAGONPOWER = 100;
const int DRAGONPROTECTPOWER = 100;
const int DRAGONMONEY = 100000;
const int DRAGONEXP = 1000;
const int DRAGONLEVEL = 100;
#endif // !__CONSTTABLE_H__
