#include "stdafx.h"
#include "Business.h"


CBusiness::CBusiness(void)
{

}

CBusiness::~CBusiness(void)
{
}

string CBusiness::excute()
{
	return "";
}

void CBusiness::SetInfoMap(const string& InStr)
{
	vector<string> vtmp;
	Split(vtmp,InStr,";");

	char key[MAX_SIZE] = {0};
	char kvalue[MAX_SIZE] = {0};
	vector<string>::iterator vt = vtmp.begin();
	for (; vt != vtmp.end(); vt++)
	{
		sscanf((*vt).c_str(),"%[^=]=%s",key,kvalue);

		_infomap.insert(make_pair(key,kvalue));
		key[0] = 0;
		kvalue[0] = 0;
	}
}

string CBusiness::GetResult()
{
	if (_refile == "xml")
	{
		return _GetXmlResult();
	}
	else if (_refile == "json")
	{
		return _GetJsonResult();
	}
	else if (_refile == "string")
	{
		return _GetStringResult();
	}
	else
	{
		return "";
	}
}

void CBusiness::SetResultFile(const string& refile)
{
	_refile = refile;
}

bool CBusiness::HashKey(const string& key)
{
	map<string,string>::iterator it = _infomap.find(key);
	if (it != _infomap.end())
	{
		return true;
	}
	return false;
}


string CBusiness::GetInfo(const string& key)
{
	map<string,string>::iterator it = _infomap.find(key);
	if (it != _infomap.end())
	{
		return (*it).second;
	}
	return "";
}

string CBusiness::_GetXmlResult()
{
	string xmlstr = "";
	char xmlbuf[MAX_SIZE] = {0};
	//map<string,string>::iterator correct = _infomap.find("correct");
	//if (correct == _infomap.end())
	//{
	//	xmlstr = "<is_correct>0</is_correct>";
	//}

	map<string,string>::iterator it = _infomap.begin();
	for (;it != _infomap.end(); it++)
	{
		xmlstr += "<" + (*it).first + ">" + (*it).second + "</" + (*it).first + ">";
	}
	return xmlstr;
}

string CBusiness::_GetJsonResult()
{
	Json::Value json;
	//map<string,string>::iterator correct = _infomap.find("correct");
	//if (correct == _infomap.end())
	//	json["is_correct"] = Json::Value(0);

	map<string,string>::iterator it = _infomap.begin();
	for (;it != _infomap.end(); it++)
	{
		json[(*it).first] = (*it).second;
	}

	Json::FastWriter write;
	return write.write(json);
}

string CBusiness::_GetStringResult()
{
	string strResult = "";
	map<string,string>::iterator it = _infomap.begin();
	for (;it != _infomap.end(); it++)
	{
		strResult += (*it).first + "=" + (*it).second + ";" ;
	}
	return strResult;
}

CCityDate::CCityDate(void)
{
	_SetCityVec();
}

CCityDate::CCityDate(const string& cityfile):_cityfile(cityfile)
{
	_SetCityVec();
}

CCityDate::~CCityDate(void)
{

}

void CCityDate::_SetCityVec()
{
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT2), "DCT"); //查找资源
	nSize = SizeofResource(hInst,hsrc); //计算资源大小
	
	//获取资源首地址
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_city,buf,"\r\n");
	//释放资源
	delete[] buf;
	FreeResource(hglb);
}

void CCityDate::_SplitCityDate(string& cStr,string& dStr)
{
	vector<string>::iterator it = find(_city.begin(),_city.end(),cStr);
	if (it != _city.end())
	{
		return;
	}

	it = find(_city.begin(),_city.end(),dStr);
	if (it != _city.end())
	{
		return;
	}

	it = _city.begin();
	int pos = -1;
	for (;it!=_city.end();it++)
	{
		pos = cStr.find(*it);
		if (pos != string::npos)
		{
			string tmp = cStr;
			cStr = (*it);
			dStr = tmp.replace(pos,(*it).length(),"");
			return ;
		}
	}
	dStr = cStr;
	cStr = "";
	return;
}

int CCityDate::CityInDate(string& city,string& date)
{
	return 0;
	//int ret = 0;
	//string cStr = "",dStr = "";
	//if (city == "" && date != "")
	//{
	//	cStr = date;
	//	ret = 1;
	//}
	//else if (city != "" && date == "")
	//{
	//	cStr = city;
	//	ret = 2;
	//}
	//else
	//{
	//	return ret;
	//}
	////_SplitCityDate(cStr,dStr);
	//city = cStr;
	//date = dStr;
	//return ret;
}
