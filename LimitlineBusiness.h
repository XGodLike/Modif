#pragma once
#include "Business.h"
#include "DateTrans.h"
#define LIMITLINEDATE "limitline_date"
#define LIMITLINECITY "limitline_city"

class CLimitlineBusiness:public CBusiness
{
public:
	CLimitlineBusiness(void);
	~CLimitlineBusiness(void);
private:
	string _date;
	string _city;
	CDateTrans* _datetrans;
	CCityDate* _citydate;
public:
	string excute();
};

