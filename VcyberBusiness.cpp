#include "stdafx.h"
#include "VcyberBusiness.h"


CVcyberBusiness::CVcyberBusiness(void)
{
	_SetTypeMap();
	_business = nullptr;
	_refile = "string";
}


CVcyberBusiness::~CVcyberBusiness(void)
{
	if (_business != nullptr)
	{
		delete _business;
		_business = nullptr;
	}
}

void CVcyberBusiness::_SetTypeMap()
{
	_typemap.insert(make_pair("navigate",NAGIGATE));
	_typemap.insert(make_pair("command",COMMAND));
	_typemap.insert(make_pair("remind",REMIND));
	_typemap.insert(make_pair("chat",CHAT));
	_typemap.insert(make_pair("music",MUSIC));
	_typemap.insert(make_pair("sms",SMS));
	_typemap.insert(make_pair("movie",MOVIE));
	_typemap.insert(make_pair("tel",TEL));
	_typemap.insert(make_pair("radio",RADIO));
	_typemap.insert(make_pair("weather",WEATHER));
	_typemap.insert(make_pair("stock",STOCK));
	_typemap.insert(make_pair("limitline",LIMITLINE));
}

void CVcyberBusiness::_GetInfo()
{
	map<string,string>::iterator it = _infomap.find(TYPE);
	if (it != _infomap.end())
	{
		_GetBuninessType((*it).second);
	}

	it = _infomap.find(RFILETYPE);
	if (it != _infomap.end())
	{
		 _refile = (*it).second==""?_refile:(*it).second;
	}

	it = _infomap.find(PROJECT);
	if (it != _infomap.end())
	{
		_project = (*it).second;
	}
}

void CVcyberBusiness::_GetBuninessType(const string& BusinessType)
{
	map<string,BUSINESS_TYPE>::iterator it = _typemap.find(BusinessType);
	if (it != _typemap.end())
	{
		_type = (*it).second;
	}
}

void CVcyberBusiness::_CreateBusiness(const BUSINESS_TYPE type)
{
	switch (type)
	{
	case COMMAND:
	case REMIND:
	case CHAT:
	case MUSIC:
	case SMS:
	case MOVIE:
		_business = new CBusiness();
		break;
	case TEL:
		_business = new CTelBusiness();
		break;
	case RADIO:
		_business = new CRadioBusiness();
		break;
	case WEATHER:
		_business = new CWeatherBusiness();
		break;
	case STOCK:
		_business = new CStockBusiness();
		break;
	case LIMITLINE:
		_business = new CLimitlineBusiness();
		break;
	case NAGIGATE:
		_business = new CNavigateBusiness();
		break;
	default:
		break;
	}
}

string CVcyberBusiness::excute()
{	
	string result = "";
	if (_business != nullptr)
	{
		//执行，返回结果
		result = _business->excute();
	}
	return result;
}

string CVcyberBusiness::Modif(const string& InStr)
{
	string result = InStr;
	SetInfoMap(InStr);
	_GetInfo();
	//if (CheckSwitch(_project))
	if(true)
	{
		//生成子类
		_CreateBusiness(_type);

		if (_business != nullptr)
		{
			_business->SetInfoMap(InStr);
			//设置返回文件类型
			_business->SetResultFile(_refile);
		}
		result =  excute();
	}
	
	return result;
	
}

