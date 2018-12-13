
#define _MODIF_DLL_
#include "stdafx.h"
#include "Config.h"


CConfig::CConfig(void)
{
	 char szFilePath[MAX_SIZE];
	 GetCurrentDirectory(MAX_SIZE,szFilePath);
	 strcat_s(szFilePath,"\\Config\\config.ini");	

	 _configfile = szFilePath;
}

CConfig::CConfig(const string configfile):_configfile(configfile)
{	
}

CConfig::~CConfig(void)
{
}

void CConfig::_Split(vector<string>& VecStr,const string& InStr,const string& delimer)
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

string CConfig::_GetConfigParam(const string& NodeStr)
{
	FILE* ConfigFile;
	fopen_s(&ConfigFile,_configfile.c_str(),"rb");
	if(ConfigFile == NULL)
	{
		return "";
	}

	char buf[MAX_SIZE]={0};
	int len=GetPrivateProfileString("PROJECT",//����
			NodeStr.c_str(),				  //����
			"",								  //û�ҵ�����ʱ�ķ���ֵ
			buf,							  //Ŀ�껺������ַ
			MAX_SIZE,						  //Ŀ�껺��������
			_configfile.c_str());			  //�����ļ���׼ȷ·��

	fclose(ConfigFile);
	return buf;
}

void CConfig::_SetSwitchDateVec(const string& InStr)
{
	_Split(_switchproject,InStr,",");
}

void CConfig::Init(const string& NodeStr)
{
	string str = _GetConfigParam(NodeStr);
	_SetSwitchDateVec(str);
}

bool CConfig::CheckSwitch(const string& project)
{
	vector<string>::iterator it = find(_switchproject.begin(),_switchproject.end(),project);
	return it != _switchproject.end() ? true : false;
}
