#pragma once

class CConfig
{
public:
	CConfig(void);
	CConfig(const string configfile);
	~CConfig(void);
	
private:
	string _configfile;
	vector<string> _switchproject;
	void _Split(vector<string>& VecStr,const string& InStr,const string& delimer);
	string _GetConfigParam(const string& NodeStr);
	void _SetSwitchDateVec(const string& InStr);
public:
	void Init(const string& InStr);
	bool CheckSwitch(const string& project);	
};

