#pragma once
#include "Business.h"
#include "NumTrans.h"
#define STOCKDIGITAL "stock_digital"
#define STOCKTYPE "stock_type"
#define STOCKNAME "stock_name"

class CStockBusiness:public CBusiness
{
public:
	CStockBusiness(void);
	CStockBusiness(const string& hs,const string& hk,const string& usa);
	~CStockBusiness(void);
private:
	string _hsfile;
	string _hkfile;
	string _usafile;
	CNumTrans _numtrans;
	string _digital;
	string _stockname;
	string _stocktype;
	map<string,string> _hsstock;
	map<string,string> _hkstock;
	map<string,string> _usastock;
	void _LoadHSStock();
	void _LoadHKStock();
	void _LoadUSAStock();
	string _FindTypeByName(const string StockName);
	string _FindTypeByCode(const string StockCode);
public:
	string excute();
};

