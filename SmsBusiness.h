#pragma once
#include "Business.h"

class CSmsBusiness:public CBusiness
{
public:
	CSmsBusiness(void);
	~CSmsBusiness(void);
public:
	string excute();
};

