#pragma once
#include "define.h"

class CNumTrans
{
public:
	CNumTrans(void);
	~CNumTrans(void);
private:
	map<string,int> _Nummap;
	map<string,int> _Unitmap;
protected:
	void _SetNumberDict();
	void _SetUnitDict();
	int _NumTrans(const char* strNum);
	int _UnitTrans(const char* strUnit);
	bool _GetHanzi(char* Hanzi, const char* str);
	//�鿴�Ƿ��а�ʮǧ����
	bool _CheckContaiUnit(const string& str);
	//�鿴�Ƿ�
	//�õ�������ʮǧ���ڵ�ת��
	string _GetUnitTran(const string& str);
	//�õ������ֵ�ת��
	string _GetNumTran(const string& str);
public:
	void TranToNumber(string& DstNum,const string& SrcNum);
};

