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
	//查看是否含有百十千万亿
	bool _CheckContaiUnit(const string& str);
	//查看是否
	//得到包含百十千万亿的转化
	string _GetUnitTran(const string& str);
	//得到纯数字的转换
	string _GetNumTran(const string& str);
public:
	void TranToNumber(string& DstNum,const string& SrcNum);
};

