#pragma once
#include "Business.h"
#include "DateTrans.h"
#define WEATHERDATE "weather_date"
#define WEATHERCITY "weather_city"


class CWeatherBusiness:public CBusiness
{
public:
	CWeatherBusiness(void);
	~CWeatherBusiness(void);
private:
	CDateTrans _datetrans;
	CCityDate _citydate;
	string _date;
	string _city;
public:
	string excute();
};

