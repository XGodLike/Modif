#pragma once
#include "define.h"
#include "Config.h"
#include "Business.h"
#include "SmsBusiness.h"
#include "TelBusiness.h"
#include "ChatBusiness.h"
#include "RadioBusiness.h"
#include "MovieBusiness.h"
#include "MusicBusiness.h"
#include "StockBusiness.h"
#include "RemindBusiness.h"
#include "CommandBusiness.h"
#include "WeatherBusiness.h"
#include "NavigateBusiness.h"
#include "LimitlineBusiness.h"

#define PROJECT "project"
#define RFILETYPE "file"
#define TYPE "type"

enum BUSINESS_TYPE
{
	NAGIGATE = 0,
	COMMAND,
	REMIND,
	CHAT,
	MUSIC,
	SMS,
	MOVIE,
	TEL,
	RADIO,
	WEATHER,
	STOCK,
	LIMITLINE
};



class CVcyberBusiness:public CBusiness
{
public:
	CVcyberBusiness(void);
	 ~CVcyberBusiness(void);
public:	
	CBusiness* _business;
	map<string,BUSINESS_TYPE> _typemap;
	string _project;
	BUSINESS_TYPE _type;
	string _refile;
private:
	void _SetTypeMap();
	void _GetInfo();	
	void _GetBuninessType(const string& BusinessType);
	void _CreateBusiness(const BUSINESS_TYPE type);
public:	
	string excute();
	string Modif(const string& InStr);
	
};

