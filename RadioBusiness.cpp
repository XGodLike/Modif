#include "stdafx.h"
#include "RadioBusiness.h"


CRadioBusiness::CRadioBusiness(void)
{
	_SetModulate();
	_mtype = "";
}


CRadioBusiness::~CRadioBusiness(void)
{
}

void CRadioBusiness::_SetModulate()
{
	_modulatetype.insert(make_pair("µ÷Æµ","FM"));
	_modulatetype.insert(make_pair("µ÷·ù","AM"));
	_modulatetype.insert(make_pair("fm","FM"));
	_modulatetype.insert(make_pair("am","AM"));
	_modulatetype.insert(make_pair("ÖÐ²¨","AM"));
	_modulatetype.insert(make_pair("Õ×ºÕ",""));
	_modulatetype.insert(make_pair("ºÕ×È",""));
}
string CRadioBusiness::_Tran2Modulate(const string radio)
{
	string radio_number = radio;
	int pos = -1;
	map<string,string>::iterator it = _modulatetype.begin();
	for (;it != _modulatetype.end();it++)
	{
		pos = radio_number.find((*it).first);
		if (pos != string::npos)
		{
			if (_mtype == "")
			{
				_mtype = (*it).second;
			}		
			radio_number = radio_number.replace(pos,(*it).first.length(),"");
		}
	}
	if (_mtype == "")
	{
		double modulradio = atof(radio_number.c_str());
		
		if (modulradio - RANGE_AM_MIN > 0.000001 && RANGE_AM_MAX - modulradio > 0.000001)
		{
			_mtype = "AM";
		}
		else if (modulradio - RANGE_FM_MIN > 0.000001 && RANGE_FM_MAX - modulradio > 0.000001)
		{
			_mtype = "FM";
		}
	}
	radio_number = _mtype + radio_number;
	return radio_number;
}

string CRadioBusiness::excute()
{
	_rate = GetInfo(RADIORATE);

	string tran_number;	
	_numtrans.TranToNumber(tran_number,_rate);

	string tran_radio;
	tran_radio = _Tran2Modulate(tran_number);

	_infomap[RADIORATE] = tran_radio.c_str();
	return GetResult();
}