#pragma once
#include "Business.h"

class CMusicBusiness:public CBusiness
{
public:
	CMusicBusiness(void);
	~CMusicBusiness(void);
public:
	string excute();
};

