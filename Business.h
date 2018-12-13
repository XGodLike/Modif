#pragma once
#include "define.h"
#include "StrInfo.h"
#include "NumTrans.h"
#include "DateTrans.h"



class CBusiness:public CStrInfo
{
public:
	CBusiness(void);
	virtual ~CBusiness(void);
	virtual string excute();
public:
	map<string,string> _infomap;
private:
	string _refile;
	string _GetXmlResult();
	string _GetJsonResult();
	string _GetStringResult();
public:	
	void SetInfoMap(const string& InStr);
	void SetResultFile(const string& refile);	
	//返回结果字符串
	string GetResult();
	//获取字段值
	string GetInfo(const string& key);	
};

class CCityDate:public CStrInfo
{
public:
	CCityDate(void);
	CCityDate(const string& cityfile);
	~CCityDate(void);
private:
	string _cityfile;
	vector<string> _city;
	void _SetCityVec();
	void _SplitCityDate(string& cStr,string& dStr);
public:
	int CityInDate(string& city,string& date);	//城市，日期歧义处理
};

