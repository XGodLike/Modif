#include "stdafx.h"
#include "NumTrans.h"


CNumTrans::CNumTrans(void)
{
	_SetNumberDict();
	_SetUnitDict();
}

CNumTrans::~CNumTrans(void)
{
}
/*
void CNumTrans::TranToNumber(string& DstNum,const string& SrcNum)
{
	if (SrcNum == "")
	{
		return;
	}
	int numCount = -1;
	string NumInt = "";
	string NumDec = "";
	string integer = "";
	string decimals = "";
	char intbuf[MAX_SIZE] = {0};
	char decbuf[MAX_SIZE] = {0};
	if (SrcNum.find("点") != string::npos)
	{
		sscanf(SrcNum.c_str(),"%[^\点]点%s\n",intbuf,decbuf);
		integer = intbuf;
		decimals = decbuf;
	}
	else
	{
		integer = SrcNum;
	}
	

	char buf[64];
	int num=-1;
	int unit = -1;
	char Hanzi[3] = {0};
	if (decimals != "")
	{
		NumDec.append(".");
		for (int i = 0;i < decimals.length();i++)
		{
			if (_GetHanzi(Hanzi,&decimals[i])) i++;
			num = _NumTrans(Hanzi);
			if (num != -1)
			{
				sprintf_s(buf, "%d", num); 
				NumDec.append(buf);
			}
			else
			{
				NumDec.append(Hanzi);
			}
		}
	}
	
	if (_CheckContaiUnit(integer))
	{
		for (int i = 0; i < integer.length(); i++)
		{
			if (_GetHanzi(Hanzi,&integer[i])) i++;
			if (_Nummap.find(Hanzi) != _Nummap.end())
			{
				num = _NumTrans(Hanzi);
				if (i != integer.length()-1)
				{
					if (_GetHanzi(Hanzi,&integer[++i])) i++;
				}
			
				if (_Unitmap.find(Hanzi) != _Unitmap.end())
				{
					unit = _UnitTrans(Hanzi);
					numCount += num*unit;
				}
				else
				{
					if (i != integer.length()-1)
						i -= 2;
					numCount += num;
				}
			}
			else if (_Unitmap.find(Hanzi) != _Unitmap.end())
			{
				num = _UnitTrans(Hanzi);
				if(num != -1)
				{
					numCount += num;
				}	
			}
			else if(numCount > -1)
			{
				sprintf_s(buf,"%d",numCount + 1);
				NumInt.append(buf);	
				NumInt.append(Hanzi);	
				numCount = -1;
			}
			else
			{
				NumInt.append(Hanzi);
			}
		}
		if(numCount > -1)
		{
			sprintf_s(buf,"%d",numCount + 1);
			NumInt.append(buf);	
		}
	}
	else
	{
		for (int i = 0; i < integer.length(); i++)
		{
			if (_GetHanzi(Hanzi,&integer[i])) i++;
			num = _NumTrans(Hanzi);
			if (num != -1)
			{
				sprintf_s(buf,"%d",num);
				NumInt.append(buf);
			}
			else
			{
				NumInt.append(Hanzi);
			}
		}
	}
	DstNum = NumInt + NumDec;
}
*/
void CNumTrans::TranToNumber(string& DstNum,const string& SrcNum)
{
	if (SrcNum == "")
	{
		return;
	}
	int numCount = -1;
	string NumInt = "";
	string NumDec = "";
	string integer = "";
	string decimals = "";
	char intbuf[MAX_SIZE] = {0};
	char decbuf[MAX_SIZE] = {0};
	int pos = SrcNum.find("点");
	if (pos != string::npos)
	{
		integer = SrcNum.substr(0,pos);
		decimals = SrcNum.substr(pos + string("点").length(),SrcNum.length());
		//sscanf(SrcNum.c_str(),"%[^\点]点%s\n",intbuf,decbuf);
		//integer = intbuf;
		//decimals = decbuf;
	}
	else
	{
		integer = SrcNum;
	}

	if (decimals != "")
	{
		NumDec.append(".");
		string tmp = _GetNumTran(decimals);
		NumDec.append(tmp);
	}

	if (_CheckContaiUnit(integer))
	{
		NumInt = _GetUnitTran(integer);
	}
	else
	{
		NumInt = _GetNumTran(integer);
	}
	DstNum = NumInt + NumDec;
}

void CNumTrans::_SetNumberDict()
{
	_Nummap.insert(make_pair("零",0));
	_Nummap.insert(make_pair("一",1));
	_Nummap.insert(make_pair("幺",1));
	_Nummap.insert(make_pair("二",2));
	_Nummap.insert(make_pair("两",2));
	_Nummap.insert(make_pair("三",3));
	_Nummap.insert(make_pair("四",4));
	_Nummap.insert(make_pair("五",5));
	_Nummap.insert(make_pair("六",6));
	_Nummap.insert(make_pair("七",7));
	_Nummap.insert(make_pair("八",8));
	_Nummap.insert(make_pair("九",9));
}

void CNumTrans::_SetUnitDict()
{
	_Unitmap.insert(make_pair("十",10));
	_Unitmap.insert(make_pair("百",100));
	_Unitmap.insert(make_pair("千",1000));
	_Unitmap.insert(make_pair("万",10000));
	_Unitmap.insert(make_pair("亿",100000000));
}

bool CNumTrans::_CheckContaiUnit(const string& str)
{
	char Hanzi[3] = {0};
	for (int i=0;i<str.length();i++)
	{
		if (str[i] < 0 || str[i] > 127)
		{
			Hanzi[0] = str[i];
			i++;
			Hanzi[1] = str[i];
		}
		else
		{
			Hanzi[0] =str[i];
			Hanzi[1] = 0;
		}
		if (_Unitmap.find(Hanzi) != _Unitmap.end())
		{
			return true;
		}
	}
	return false;
}

string CNumTrans::_GetUnitTran(const string& str)
{
	int num = -1;
	int unit = -1;
	int numCount = -1;//////////////////////////0
	string SubNum = "";
	string NumInt = "";
	char Hanzi[3] = {0};
	char buf[64] = {0};
	int charCount = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (_GetHanzi(Hanzi,&str[i])) i++;


		if (_Nummap.find(Hanzi) != _Nummap.end())
		{
			num = _NumTrans(Hanzi);
			if (i != str.length()-1)
			{
				if (_GetHanzi(Hanzi,&str[++i])) 
				{
					charCount = 2;
					i++;
				}
			}
			else charCount = 0;

			if (_Unitmap.find(Hanzi) != _Unitmap.end())
			{
				unit = _UnitTrans(Hanzi);
				numCount += num*unit;
			}
			else if (_Nummap.find(Hanzi) != _Nummap.end() && numCount == -1)//数字后面还是数字就用数字转换法来做
			{
				sprintf_s(buf,"%d",num);
				NumInt.append(buf);	
				i -= charCount;
			}
			else
			{
				i -= charCount;
				numCount += num;
			}

			charCount = 1;
		}
		else if (_Unitmap.find(Hanzi) != _Unitmap.end())
		{
			num = _UnitTrans(Hanzi);
			if(num != -1)
			{
				numCount += num;
			}	
		}
		else if(numCount > -1)
		{
			sprintf_s(buf,"%d",numCount + 1);
			//sprintf_s(buf,"%d",numCount);
			NumInt.append(buf);	
			NumInt.append(Hanzi);	
			numCount = -1;
		}
		else
		{
			NumInt.append(Hanzi);
		}
	}
	if(numCount > -1)
	{
		sprintf_s(buf,"%d",numCount + 1);//为啥要+1？？？？
		//sprintf_s(buf,"%d",numCount);
		NumInt.append(buf);	
	}
	return NumInt;
}

//string CNumTrans::_GetUnitTran(const string& str)
//{
//	//例子：一千零五十二
//	int Numstr[64] = {NULL};//[1,5,2]
//	int Unitstr[64] = {NULL};//[1000,10,1]
//	char NextHanzi[3] = {NULL};
//	char Hanzi[3] = {NULL};
//	int index = 0;
//	for (int i = 0; i < str.length(); i++)
//	{
//		if (_GetHanzi(Hanzi,&str[i])) i++;
//		
//		if(_Nummap.find(Hanzi) != _Nummap.end())
//		{		
//			if (_Nummap[Hanzi] == 0)
//			{
//				continue;
//			}
//			else
//			{
//				Numstr[index] = _Nummap[Hanzi];
//			}
//		}
//		else if(_Unitmap.find(Hanzi) != _Unitmap.end())
//		{
//			Numstr[index] = 1;
//			Unitstr[index] = _Unitmap[Hanzi];
//			index++;
//			continue;
//		}
//
//		if (i < str.length() - 1)
//		{
//			i++;
//			if (_GetHanzi(NextHanzi,&str[i]))
//			{
//				if(_Unitmap.find(NextHanzi) != _Unitmap.end())
//				{
//					Unitstr[index] = _Unitmap[NextHanzi];
//					i++;
//				}
//				else
//				{
//					i -= 2;
//				}
//			}	 
//		}else
//		{
//			Unitstr[index] = 1;
//		}
//		index++;
//	}
//	int Count = 0;
//	char buf[64] = {NULL};
//	for (int i = 0; i < index; i++)
//	{
//		if (i > 0 && Unitstr[i] > Unitstr[i-1] )
//		{
//			Count += Numstr[i];
//			Count *= Unitstr[i];
//			continue;
//		}
//		Count += Numstr[i]*Unitstr[i];
//	}
//	sprintf_s(buf,"%d",Count);
//	return buf;
//}

string CNumTrans::_GetNumTran(const string& str)
{
	int num=-1;
	string NumDec = "";
	char Hanzi[3] = {0};
	char buf[64] = {0};
	for (int i = 0;i < str.length();i++)
	{
		if (_GetHanzi(Hanzi,&str[i])) i++;
		num = _NumTrans(Hanzi);
		if (num != -1)
		{
			sprintf_s(buf, "%d", num); 
			NumDec.append(buf);
		}
		else
		{
			NumDec.append(Hanzi);
		}
	}
	return NumDec;
}

int CNumTrans::_NumTrans(const char* strNum)
{
	return _Nummap.find(strNum) != _Nummap.end() ? _Nummap[strNum] : -1;
}

int CNumTrans::_UnitTrans(const char* strUnit)
{
	return _Unitmap.find(strUnit) != _Unitmap.end() ? _Unitmap[strUnit] : -1;
}

bool CNumTrans::_GetHanzi(char* Hanzi, const char* str)
{
	if (str[0] > 127 || str[0] <0)
	{
		Hanzi[0] = *str;
		Hanzi[1] = *(str+1);
		return true;
	}else
	{
		Hanzi[0] = *str;
		Hanzi[1] = 0;
		return false;
	}
	
}