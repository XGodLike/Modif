#pragma once
#include "Business.h"

class CRemindBusiness:public CBusiness
{
public:
	CRemindBusiness(void);
	~CRemindBusiness(void);
private:
public:
	string excute();
};

