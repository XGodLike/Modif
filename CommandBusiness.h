#pragma once
#include "Business.h"

class CCommandBusiness:public CBusiness
{
public:
	CCommandBusiness(void);
	~CCommandBusiness(void);
public:
	string excute();
};

