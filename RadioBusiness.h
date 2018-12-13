#pragma once
#include "Business.h"
#include "NumTrans.h"
#define RADIORATE "radio_rate"

#define RANGE_AM_MIN 531 //535
#define RANGE_AM_MAX 1602 //1605
#define RANGE_FM_MIN 87.5
#define RANGE_FM_MAX 108

class CRadioBusiness:public CBusiness
{
public:
	CRadioBusiness(void);
	~CRadioBusiness(void);
private:
	CNumTrans _numtrans;
	map<string,string> _modulatetype;
	string _mtype;
	string _rate;
private:
	void _SetModulate();
	string _Tran2Modulate(const string radio);
public:
	string excute();
};

