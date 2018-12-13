#include "stdafx.h"
#include "StockBusiness.h"


CStockBusiness::CStockBusiness(void)
{
#ifndef LOAD_RESOURCE
	char szFilePath[MAX_SIZE];
	GetCurrentDirectory(MAX_SIZE,szFilePath);
	//strcat_s(szFilePath,"\\Config\\Navigate.txt");	

	_hsfile = szFilePath + (string)"\\model\\Modif_HS.dct";
	_hkfile = szFilePath + (string)"\\model\\Modif_HK.dct";
	_usafile = szFilePath + (string) "\\model\\Modif_USA.dct";
#endif
	_LoadHSStock();
	_LoadHKStock();
	_LoadUSAStock();
}

CStockBusiness::CStockBusiness(const string& hs,const string& hk,const string& usa):_hsfile(hs),_hkfile(hk),_usafile(usa)
{
	_LoadHSStock();
	_LoadHKStock();
	_LoadUSAStock();
}

CStockBusiness::~CStockBusiness(void)
{
}

#ifdef LOAD_RESOURCE
void CStockBusiness::_LoadHSStock()
{
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT6), "DCT"); //查找资源
	nSize = SizeofResource(hInst,hsrc); //计算资源大小

	//获取资源首地址
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_hsstock,buf,"\r\n");
	//释放资源
	delete[] buf;
	FreeResource(hglb);
}

void CStockBusiness::_LoadHKStock()
{
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT8), "DCT"); //查找资源
	nSize = SizeofResource(hInst,hsrc); //计算资源大小

	//获取资源首地址
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_hkstock,buf,"\r\n");
	//释放资源
	delete[] buf;
	FreeResource(hglb);
}

void CStockBusiness::_LoadUSAStock()
{
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT7), "DCT"); //查找资源
	nSize = SizeofResource(hInst,hsrc); //计算资源大小

	//获取资源首地址
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_usastock,buf,"\r\n");
	//释放资源
	delete[] buf;
	FreeResource(hglb);
}
#else
void CStockBusiness::_LoadHSStock()
{
	FILE* pf;
	fopen_s(&pf,_hsfile.c_str(),"rb");
	if(pf == NULL)
	{
		return ;
	}

	char name[MAX_SIZE] = {0};
	char code[MAX_SIZE] = {0};
	char buf[MAX_SIZE]= {0};
	while (fgets(buf,MAX_SIZE,pf) != NULL)
	{
		sscanf(buf,"%s %s\r\n",name,code);
		_hsstock.insert(make_pair(name,code)) ;
	}
	fclose(pf);
}

void CStockBusiness::_LoadHKStock()
{
	FILE* pf;
	fopen_s(&pf,_hkfile.c_str(),"rb");
	if(pf == NULL)
	{
		return ;
	}

	char name[MAX_SIZE] = {0};
	char code[MAX_SIZE] = {0};
	char buf[MAX_SIZE]= {0};
	while (fgets(buf,MAX_SIZE,pf) != NULL)
	{
		sscanf(buf,"%s %s\r\n",name,code);
		_hkstock.insert(make_pair(name,code)) ;
	}
	fclose(pf);
}

void CStockBusiness::_LoadUSAStock()
{
	FILE* pf;
	fopen_s(&pf,_usafile.c_str(),"rb");
	if(pf == NULL)
	{
		return ;
	}

	char name[MAX_SIZE] = {0};
	char code[MAX_SIZE] = {0};
	char buf[MAX_SIZE]= {0};
	while (fgets(buf,MAX_SIZE,pf) != NULL)
	{
		sscanf(buf,"%s %s\r\n",name,code);
		_usastock.insert(make_pair(name,code)) ;
	}
	fclose(pf);
}
#endif
string CStockBusiness::_FindTypeByName(const string StockName)
{
	//map<string,string>::iterator it = _hsstock.find(StockName);
	//if (it != _hsstock.end())
	//{
	//	return "HS";
	//}
	// it = _hkstock.find(StockName);
	// if (it != _hkstock.end())
	// {
	//	 return "HK";
	// }
	map<string,string>::iterator it = _hsstock.begin();
	for (;it != _hsstock.end();it++)
	{
		if ((*it).first.find(StockName) != string::npos)
		{
			return "HS";
		}
	}
	
	it = _hkstock.begin();
	for (;it != _hkstock.end();it++)
	{
		if ((*it).first.find(StockName) != string::npos)
		{
			return "HK";
		}
	}

	it = _usastock.begin();
	for (;it != _usastock.end();it++)
	{
		if ((*it).first.find(StockName) != string::npos)
		{
			return "USA";
		}
	}

	 return "";
}

string CStockBusiness::_FindTypeByCode(const string StockCode)
{
	map<string,string>::iterator it = _hsstock.begin();
	for (;it != _hsstock.end();it++)
	{
		if ((*it).second == StockCode)
		{
			return "HS";
		}
	}
	it = _hkstock.begin();
	for (;it != _hkstock.end();it++)
	{
		if ((*it).second == StockCode)
		{
			return "HK";
		}
	}
	return "";
}

string CStockBusiness::excute()
{
	_digital = GetInfo(STOCKDIGITAL);
	_stockname = GetInfo(STOCKNAME);
	_stocktype = GetInfo(STOCKTYPE);

	//转数字
	string tran_digital;
	_numtrans.TranToNumber(tran_digital,_digital);

	//根据名字或代码查找类型
	string stock_type ;
	if (_stocktype != "" && !_stocktype.empty())
	{
		stock_type = _stocktype;
	}
	else if (_stockname != "" && !_stockname.empty())
	{
		stock_type = _FindTypeByName(_stockname);
	}
	else if (tran_digital != "" && !tran_digital.empty())
	{
		stock_type = _FindTypeByCode(tran_digital);
	}
	
	_infomap[STOCKDIGITAL] = tran_digital.c_str();
	_infomap[STOCKTYPE] = stock_type.c_str();
	return GetResult();
}