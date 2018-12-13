#include "stdafx.h"
#include "LimitlineBusiness.h"


CLimitlineBusiness::CLimitlineBusiness(void)
{
	_datetrans = new CDateTrans();
	_citydate = new CCityDate();
}


CLimitlineBusiness::~CLimitlineBusiness(void)
{
	delete _datetrans;
	_datetrans = nullptr;
	delete _citydate ;
	_citydate = nullptr;
}

string CLimitlineBusiness::excute()
{
	_date = GetInfo(LIMITLINEDATE);
	_city = GetInfo(LIMITLINECITY);
	
	_citydate->CityInDate(_city,_date);

	string tran_date;
	_datetrans->DateSwitch(tran_date,_date);

	_infomap[LIMITLINEDATE] = tran_date.c_str();
	_infomap[LIMITLINECITY] = _city.c_str();
	return GetResult();
}