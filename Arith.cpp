#include "stdafx.h"
#include "Arith.h"


CArith::CArith(void)
{
}


CArith::~CArith(void)
{
}

string CArith::excute()
{
	string tran_number1, tran_number2, tran_number3, tran_number4, tran_number5;
	if (HashKey(NUMBER_1))
	{
		_number1 = GetInfo(NUMBER_1);
		_numtrans.TranToNumber(tran_number1,_number1);
		_infomap[NUMBER_1] = tran_number1.c_str();
	}
	if (HashKey(NUMBER_2))
	{
		_number2 = GetInfo(NUMBER_2);
		_numtrans.TranToNumber(tran_number2,_number2);
		_infomap[NUMBER_2] = tran_number2.c_str();
	}
	if (HashKey(NUMBER_3))
	{
		_number3 = GetInfo(NUMBER_3);
		_numtrans.TranToNumber(tran_number3,_number3);
		_infomap[NUMBER_3] = tran_number3.c_str();
	}
	if (HashKey(NUMBER_4))
	{
		_number4 = GetInfo(NUMBER_4);
		_numtrans.TranToNumber(tran_number4,_number4);
		_infomap[NUMBER_4] = tran_number4.c_str();
	}
	if (HashKey(NUMBER_5))
	{
		_number5 = GetInfo(NUMBER_5);
		_numtrans.TranToNumber(tran_number5,_number5);
		_infomap[NUMBER_5] = tran_number5.c_str();
	}

	return GetResult();
}