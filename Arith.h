#pragma once
#include "Business.h"

#define NUMBER_1 "num1"
#define NUMBER_2 "num2"
#define NUMBER_3 "num3"
#define NUMBER_4 "num4"
#define NUMBER_5 "num5"

class CArith:public CBusiness
{
public:
	CArith(void);
	~CArith(void);
public:
	CNumTrans _numtrans;
	string _number1;
	string _number2;
	string _number3;
	string _number4;
	string _number5;
	string excute();
};

