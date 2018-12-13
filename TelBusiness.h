#pragma once
#include "Business.h"
#include "NumTrans.h"
#define TELNUMBER "tel_num"

class CTelBusiness:public CBusiness
{
public:
	CTelBusiness(void);
	~CTelBusiness(void);
private:
	string _number;
	CNumTrans _numtrans;
public:
	string excute();
};

