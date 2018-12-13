#pragma once
#include "Business.h"

class CMovieBusiness:public CBusiness
{
public:
	CMovieBusiness(void);
	~CMovieBusiness(void);
public:
	string excute();
};

