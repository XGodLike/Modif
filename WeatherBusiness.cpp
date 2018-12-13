#include "stdafx.h"
#include "WeatherBusiness.h"


CWeatherBusiness::CWeatherBusiness(void)
{
}


CWeatherBusiness::~CWeatherBusiness(void)
{
}

string CWeatherBusiness::excute()
{
	_date = GetInfo(WEATHERDATE);
	_city = GetInfo(WEATHERCITY); 

	_citydate.CityInDate(_city,_date);

	string tran_date = "";
	_datetrans.DateSwitch(tran_date,_date);

	_infomap[WEATHERDATE] = tran_date.c_str();
	_infomap[WEATHERCITY] = _city.c_str();
	return GetResult();
}