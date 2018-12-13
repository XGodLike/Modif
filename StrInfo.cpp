#include "stdafx.h"
#include "StrInfo.h"


CStrInfo::CStrInfo(void)
{
}


CStrInfo::~CStrInfo(void)
{
}

void CStrInfo::Split(vector<string>& VecStr,const string& InStr,const string& delimer)
{
	string tmp = InStr;
	char* p_str = (char*)tmp.c_str();
	char* p_next = nullptr;
	char* pstr = strtok_s(p_str,delimer.c_str(),&p_next);
	while (pstr != NULL)
	{
		VecStr.push_back(pstr);
		pstr = strtok_s(NULL,delimer.c_str(),&p_next);
	}
	return ;
}

void CStrInfo::Split(map<string,int>& VecStr,const string& InStr,const string& delimer)
{
	vector<string> vtmp;
	string tmp = InStr;
	char* p_str = (char*)tmp.c_str();
	char* p_next = nullptr;
	char* pstr = strtok_s(p_str,delimer.c_str(),&p_next);
	while (pstr != NULL)
	{
		vtmp.push_back(pstr);
		pstr = strtok_s(NULL,delimer.c_str(),&p_next);
	}
	char key[32] = {0};
	signed int value = 0;
	vector<string>::iterator it = vtmp.begin();
	for (;it!=vtmp.end();it++)
	{
		sscanf((*it).c_str(),"%[^=]=%d",key,&value);
		VecStr.insert(make_pair(key,value));
	}
	return ;
}

void CStrInfo::Split(map<string,string>& VecStr,const string& InStr,const string& delimer)
{
	vector<string> vtmp;
	string tmp = InStr;
	char* p_str = (char*)tmp.c_str();
	char* p_next = nullptr;
	char* pstr = strtok_s(p_str,delimer.c_str(),&p_next);
	while (pstr != NULL)
	{
		vtmp.push_back(pstr);
		pstr = strtok_s(NULL,delimer.c_str(),&p_next);
	}
	char key[32] = {0};
	char value[32] = {0};
	vector<string>::iterator it = vtmp.begin();
	for (;it!=vtmp.end();it++)
	{
		sscanf((*it).c_str(),"%[^\t]\t%s",key,value);
		VecStr.insert(make_pair(key,value));
	}
	return ;
}

void CStrInfo::Split(map<int,map<string,string>>& VecStr,const string& InStr,const string& delimer)
{
	vector<string> vtmp;
	string tmp = InStr;
	char* p_str = (char*)tmp.c_str();
	char* p_next = nullptr;
	char* pstr = strtok_s(p_str,delimer.c_str(),&p_next);
	while (pstr != NULL)
	{
		vtmp.push_back(pstr);
		pstr = strtok_s(NULL,delimer.c_str(),&p_next);
	}
	int key = 0;
	char value[64] = {0};
	char holiday[32] = {0};
	char holDate[32]={0};
	map<string,string> mtmp;
	vector<string>::iterator it = vtmp.begin();
	int dkey = 0;
	for (;it!=vtmp.end();it++)
	{			
		sscanf((*it).c_str(),"%d\t%s",&key,value);
		if (dkey == key || dkey == 0)
		{
			sscanf(value,"%[^=]=%s",holiday,holDate);
			mtmp.insert(make_pair(holiday,holDate));
			dkey = key;
		}
		else
		{
			VecStr.insert(make_pair(key,mtmp));
			mtmp.clear();
			dkey = 0;
		}
	}
	if (!mtmp.empty())
	{
		VecStr.insert(make_pair(key,mtmp));
	}
	return ;
}