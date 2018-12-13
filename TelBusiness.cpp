#include "stdafx.h"
#include "TelBusiness.h"


CTelBusiness::CTelBusiness(void)
{
}


CTelBusiness::~CTelBusiness(void)
{
}

string CTelBusiness::excute()
{
	_number = GetInfo(TELNUMBER);

	string tran_number;
	_numtrans.TranToNumber(tran_number,_number);

	_infomap[TELNUMBER] = tran_number.c_str();
	return GetResult();
}