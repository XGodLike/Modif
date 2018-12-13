#pragma once
#include "Business.h"

class CChatBusiness:public CBusiness
{
public:
	CChatBusiness(void);
	~CChatBusiness(void);
public:
	string excute();
};

