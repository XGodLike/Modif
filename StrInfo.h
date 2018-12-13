#pragma once
class CStrInfo
{
public:
	CStrInfo(void);
	virtual ~CStrInfo(void);
	void Split(vector<string>& VecStr,const string& InStr,const string& delimer);
	void Split(map<string,int>& VecStr,const string& InStr,const string& delimer);
	void Split(map<string,string>& VecStr,const string& InStr,const string& delimer);
	void Split(map<int,map<string,string>>& VecStr,const string& InStr,const string& delimer);
};

