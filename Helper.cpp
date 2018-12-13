#include "stdafx.h"
#include "Helper.h"
#include "LunarData.h"
#include <stdio.h>
#include <Windows.h>

BOOL IsLeapYear(short sYear)
{
	if (sYear<1600||sYear>=6400)//压缩算法规定了的年份区间（提取器只能导出此区间的数据，Lunar.dll支持-6000到20000（不含20000）之间的年份）
	{
		return E_FAIL;
	}
	if (sYear%4==0&&sYear%100!=0||sYear%400==0)//判断闰年的条件
	{
		return TRUE;
	}else
	{
		return FALSE;
	}
}

BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays)
{
	//从日期算出距离元旦的天数
	int ret=0;
	if (DateCheck(sYear,wMonth,wDay)==0)//对输入的日期进行检查
	{
		return 0;
	}
	ret=IsLeapYear(sYear);//判断是否为闰年
	if (ret==-1)
	{
		return 0;
	}
	if (ret==1)
	{
		*nDays=DayOrdinalLeap[wMonth-1]+wDay-1;//元旦为序数0，因此减1
	}else
	{
		*nDays=DayOrdinal[wMonth-1]+wDay-1;
	}
	return 1;
}

BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay)
{
	//从年内序数计算日期
	int ret=0,i=0;
	if (sOrdinal<0)
	{
		return FALSE;
	}
	ret=IsLeapYear(sYear);
	if (ret==1)
	{
		if (sOrdinal>=366)//超出了该年的总天数
		{
			return FALSE;
		}
	}else
	{
		if (sOrdinal>=365)
		{
			return FALSE;
		}
	}
	if (ret!=-1)
	{
		//年符合，则计算;
		*wMonth=0;
		for (i=0;i<12;i++)
		{
			if (ret==1)
			{
				if (sOrdinal>=DayOrdinalLeap[i]&&sOrdinal<DayOrdinalLeap[i+1])//找出月份
				{
					*wMonth=i+1;
					*wDay=sOrdinal-DayOrdinalLeap[i]+1;//计算出“日”
					break;
				}
			}else
			{
				if (sOrdinal>=DayOrdinal[i]&&sOrdinal<DayOrdinal[i+1])
				{
					*wMonth=i+1;
					*wDay=sOrdinal-DayOrdinal[i]+1;
					break;
				}
			}
		}
	}else
	{
		*wDay=0;
		*wMonth=0;
		return FALSE;
	}
	return TRUE;
}

BOOL DateCheck(short sYear,unsigned short wMonth,unsigned short wDay)
{
	if (sYear<START_YEAR||sYear>=END_YEAR||wMonth>12||wMonth<1||wDay<1||wDay>31)
	{
		return 0;
	}
	if (wMonth==4||wMonth==6||wMonth==9||wMonth==11)
	{
		if (wDay==31)
		{
			return 0;
		}
	}else if (wMonth==2)
	{
		if (IsLeapYear(sYear)==0)
		{
			if (wDay>28)
			{
				return 0;
			}
		}else
		{
			if (wDay>29)
			{
				return 0;
			}
		}
	}
	return 1;
}

short LunarGetNewYearOrdinal(short sLunarYear)
{
	unsigned int uData=0;
	if (GetMonthInfo(sLunarYear,&uData)==FALSE)
	{
		return 0;
	}
	return (short)((uData>>17)&0x3F);//取出农历新年的年内序数
}

unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth)
{
	int i=0;//循环变量
	unsigned int DX_data=0;//该年大小月情况
	unsigned int uData=0;
	int Acc_LeapMonth=0;
	if (sLunarYear==START_YEAR-1)//农历还在起始年份的前一年
	{
		if (cPreLeapIndex==-1)//无闰月
		{
			if (bLeapMonth==TRUE)
			{
				return 0;
			}
			return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
		}else
		{
			Acc_LeapMonth=cPreLeapIndex+9;
			if (Acc_LeapMonth>wLunarMonth)
			{
				if (bLeapMonth==TRUE)
				{
					return 0;
				}
				return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
			}else
			{
				if ((bLeapMonth==TRUE&&wLunarMonth==Acc_LeapMonth)||wLunarMonth>Acc_LeapMonth)
				{
					return cPreMonth[wLunarMonth-8]-cPreMonth[wLunarMonth-9];
				}else
				{
					return cPreMonth[wLunarMonth-9]-cPreMonth[wLunarMonth-10];
				}
			}
		}
	}
	if (GetMonthInfo(sLunarYear,&uData)==FALSE)
	{
		return 0;
	}
	DX_data=(unsigned short)(uData&0x1FFF);//整年大小月情况
	Acc_LeapMonth=LunarGetLeapMonth(sLunarYear);//获取真实闰月月份
	if (bLeapMonth)//指定查询的当前月是闰月
	{
		if (Acc_LeapMonth!=wLunarMonth)
		{
			return 0;//不存在的闰月
		}
		for (i=0;i<wLunarMonth;i++)
		{
			DX_data>>=1;//右移一位，即从末尾开始找该闰月月份所在的位
		}
	}else
	{
		if (Acc_LeapMonth>0)//存在闰月
		{
			if (wLunarMonth<=Acc_LeapMonth)//月份在闰月之前，倒找需要多找一位
			{
				for (i=0;i<wLunarMonth-1;i++)
				{
					DX_data>>=1;
				}
			}else
			{
				for (i=0;i<wLunarMonth;i++)//月份在闰月之后
				{
					DX_data>>=1;
				}
			}
		}else
		{
			for (i=0;i<wLunarMonth-1;i++)//无闰月
			{
				DX_data>>=1;
			}
		}
	}
	if (DX_data&0x1)
	{
		return 30;//大月
	}else
	{
		return 29;//小月
	}
}

BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15])
{
	int i=0,pos=0,iLeapMonth=0;//循环变量，数组写入位置，闰月
	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR)
	{
		return FALSE;
	}
	for (i=0;i<15;i++)
	{
		iDayOfMonth[i]=0;//对数组清零
	}
	if (sLunarYear==START_YEAR)
	{
		if (cPreLeapIndex==-1)//处理起始年份之前一年数据
		{
			iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];//农历上一年十一月总天数
			pos++;
		}else
		{
			if (cPreLeapIndex==1)//闰十月
			{
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}else
			{
				//闰十一月或闰十二月
				iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];
				pos++;
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}
		}
		iDayOfMonth[pos]=LunarGetNewYearOrdinal(sLunarYear)-cPreMonth[2];//（闰）十二月
		pos++;
	}else
	{
		iLeapMonth=LunarGetLeapMonth(sLunarYear-1);//取得前一农历年的闰月情况
		if (iLeapMonth<11)//一月至十月的闰月
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//取上一年十一月天数
			pos++;
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//取上一年十二月天数
			pos++;
		}else
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//取上一年十一月的天数
			pos++;
			if (iLeapMonth==11)//闰十一月
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,1);//取上一年闰十一月的天数
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//取上一年十二月天数
				pos++;
			}else if (iLeapMonth==12)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//取上一年十二月天数
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,1);//取上一年闰十二月天数
				pos++;
			}
		}
	}
	iLeapMonth=LunarGetLeapMonth(sLunarYear);//获取当前农历年的闰月情况
	if (iLeapMonth==0)//无闰月
	{
		for (i=0;i<12;i++)
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//取每个农历月天数
			pos++;
		}
	}else
	{
		for (i=0;i<12;i++)
		{
			if (i==iLeapMonth)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i,1);//取闰月的天数
				pos++;
			}
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//取非闰月的天数
			pos++;
		}
	}
	return TRUE;
}

BOOL GetMonthInfo(unsigned short wYear,unsigned int* puData)
{
	int iStartPos=(wYear-START_YEAR)*3;
	unsigned int uData=0;
	if (wYear<START_YEAR||wYear>=END_YEAR)
	{
		return FALSE;
	}
	uData=cMonthInfo[iStartPos];
	uData<<=8;
	uData|=cMonthInfo[iStartPos+1];
	uData<<=8;
	uData|=cMonthInfo[iStartPos+2];
	if (puData)
	{
		*puData=uData;
	}
	return TRUE;
}

unsigned short LunarGetLeapMonth(short sLunarYear)
{
	unsigned int data=0;
	unsigned short wLeapMonth=0;
	if (GetMonthInfo(sLunarYear,&data)==FALSE)
	{
		return 0;
	}
	wLeapMonth=(unsigned short)((data>>13)&0x0F);
	return wLeapMonth;
}

BOOL Gongli2Nongli(short sYear,unsigned short wMonth,unsigned short wDay,short* sLunarYear,unsigned short* wLunarMonth,unsigned short* wLunarDay,BOOL* bLeapMonth)
{
	int DaysNum=0,LunarNewYear=0,i=0,remain_days=0;//年内序数，农历新年的公历年内序数，循环变量，剩余天数
	int DaysOfLunarMonth[15]={0};//存放农历月份天数
	int iLeapMonthPre=0,iLeapMonth=0;//农历上一年闰月，今年闰月
	int ret=GetDayOrdinal(sYear,wMonth,wDay,&DaysNum);
	if (ret==0)
	{
		return 0;//日期不正确
	}
	*sLunarYear=sYear;
	LunarNewYear=LunarGetNewYearOrdinal(*sLunarYear);
	LunarExpandDX(*sLunarYear,DaysOfLunarMonth);//获取月份天数，数组从上一年十一月开始到今年（闰）十二月，包含闰月
	iLeapMonthPre=LunarGetLeapMonth(*sLunarYear-1);
	if (iLeapMonthPre==0)
	{
		iLeapMonth=LunarGetLeapMonth(*sLunarYear);//上一年没有闰月，则查询今年闰月
	}
	*bLeapMonth=FALSE;
	remain_days=DaysNum-LunarNewYear;//距离农历新年天数
	if (iLeapMonthPre>10)
	{
		i=3;//今年正月在“DaysOfLunarMonth”中的索引，上一年十一月或十二月有闰月
	}else
	{
		i=2;//上一年十一月和十二月无闰月时，今年正月的索引
	}
	if (LunarNewYear>DaysNum)//早于农历新年
	{
		*sLunarYear-=1;//农历年减1
		while(remain_days<0)
		{
			i--;//第一次先减去是因为当前i是正月，减1表示上一年十二月（或闰十二月）
			remain_days+=DaysOfLunarMonth[i];//加上上一年十二月、十一月的总天数（含闰月）直到日数大于0
		}
		if (iLeapMonthPre>10)//如果上一年十一月或十二月存在闰月
		{
			if (iLeapMonthPre==11)//闰十一月
			{
				if (i==0)//十一月（即在闰月之前）
				{
					*wLunarMonth=11+i;//转换到月份
				}else
				{
					*wLunarMonth=10+i;
					if (*wLunarMonth==iLeapMonthPre)
					{
						*bLeapMonth=TRUE;
					}
				}
			}else if (iLeapMonthPre==12)//闰十二月
			{
				if (i<2)//在闰月之前
				{
					*wLunarMonth=11+i;
				}else
				{
					*wLunarMonth=10+i;
					if (*wLunarMonth==iLeapMonthPre)
					{
						*bLeapMonth=TRUE;
					}
				}
			}
		}else
		{
			*wLunarMonth=11+i;
		}
		*wLunarDay=remain_days;
	}else
	{
		while (remain_days>=DaysOfLunarMonth[i])
		{
			remain_days-=DaysOfLunarMonth[i];//寻找农历月
			i++;//移至下个月
		}
		if (iLeapMonthPre>10)
		{
			*wLunarMonth=i-2;
		}else
		{
			if (iLeapMonth>0)
			{
				if (i-2<iLeapMonth)
				{
					*wLunarMonth=i-1;
				}else
				{
					*wLunarMonth=i-2;
					if (*wLunarMonth==iLeapMonth)
					{
						*bLeapMonth=TRUE;
					}
				}
			}else
			{
				*wLunarMonth=i-1;
			}
		}
		*wLunarDay=remain_days;
	}
	*wLunarDay+=1;//索引转换到数量
	return TRUE;
}

BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay)
{
	int DaysOfLunarMonth[15]={0};//存放农历月份天数
	int iLeapMonthPre=0,iLeapMonth=0;//农历年闰月
	int LunarNewYear=0,i=0,remain_days=0;//年内序数，农历新年的公历年内序数，循环变量，剩余天数
	int iDaysofYear=0;
	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR||wLunarMonth<1||wLunarMonth>12||wLunarDay<1||wLunarDay>30)
	{
		return 0;//年、月、日检查
	}
	if (bLeapMonth)
	{
		if (LunarGetLeapMonth(sLunarYear)!=wLunarMonth)
		{
			return FALSE;//闰月检查
		}
	}
	if (wLunarDay>LunarGetDaysofMonth(sLunarYear,wLunarMonth,bLeapMonth))
	{
		return FALSE;//大小月检查
	}
	LunarExpandDX(sLunarYear,DaysOfLunarMonth);//大小月表（农历每月天数）
	LunarNewYear=LunarGetNewYearOrdinal(sLunarYear);//找到正月初一r公历年内序数
	iLeapMonth=LunarGetLeapMonth(sLunarYear);//找出农历年的闰月
	remain_days+=LunarNewYear;//加上正月初一的序数
	if (iLeapMonthPre>10)
	{
		i=3;//今年正月在“DaysOfLunarMonth”中的索引，上一年十一月或十二月有闰月
	}else
	{
		i=2;//上一年十一月和十二月无闰月时，今年正月的索引
	}
	if (iLeapMonth==0)
	{
		if (iLeapMonthPre>10)
		{
			for (;i<wLunarMonth+2;i++)
			{
				remain_days+=DaysOfLunarMonth[i];//年内序数累加
			}
		}else
		{
			for (;i<wLunarMonth+1;i++)
			{
				remain_days+=DaysOfLunarMonth[i];//年内序数累加
			}
		}
	}else
	{
		if (wLunarMonth<iLeapMonth||(bLeapMonth==FALSE&&wLunarMonth==iLeapMonth))//在闰月之前
		{
			for (;i<wLunarMonth+1;i++)
			{
				remain_days+=DaysOfLunarMonth[i];
			}
		}else
		{
			for (;i<wLunarMonth+2;i++)
			{
				remain_days+=DaysOfLunarMonth[i];
			}
		}
	}
	remain_days+=wLunarDay-1;//减1是因为日名转到序数
	GetDayOrdinal(sLunarYear,12,31,&iDaysofYear);//获取公历年总天数
	iDaysofYear++;//从序数转到天数
	*sYear=sLunarYear;
	if (remain_days>iDaysofYear)
	{
		remain_days-=iDaysofYear;
		*sYear+=1;//下一年
	}
	GetDateFromOrdinal(*sYear,remain_days,wMonth,wDay);
	return TRUE;
}

BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2])
{
	int index=0;//对应每公历年首个节气所在字节的索引
	unsigned short wXiaoHanOrder=0;//小寒年内序数
	unsigned short wJQData=0;//节气数据
	unsigned short wCurJQData=0;//当前计算的节气数据
	unsigned short wDays=0;//当前节气距离该年小寒的天数
	int i=0;
	if (sYear<START_YEAR||sYear>=END_YEAR||wMonth>12||wMonth<1)
	{
		return FALSE;
	}
	index=(sYear-START_YEAR)*6;//对应每公历年首个节气所在字节的索引
	wXiaoHanOrder=(unsigned short)(((cSolarTerms[index])>>6)+3);//加上3，转为小寒的年内序数
	wJQData=cSolarTerms[index];
	wCurJQData=(wJQData>>4)&0x03;//当前计算的节气与上一节气的天数差信息
	if (wMonth==1)
	{
		wJieQi[0]=wXiaoHanOrder+1;//加1转到日期
		wJieQi[1]=wCurJQData+14+wXiaoHanOrder+1;//大寒：小寒的年内序数加上距离小寒的天数
		return TRUE;
	}
	wDays=wCurJQData+14;//距离小寒的天数，当前为大寒距离小寒的天数
	for (i=1;i<wMonth;i++)
	{
		if (i%2==0)
		{
			wJQData=cSolarTerms[index+i/2];
		}
		if (i%2==1)
		{
			wCurJQData=(wJQData>>2)&0x03;
			wDays+=wCurJQData+14;
			wCurJQData=wJQData&0x03;
			wDays+=wCurJQData+14;
		}else
		{
			wCurJQData=(wJQData>>6)&0x03;
			wDays+=wCurJQData+14;
			wCurJQData=(wJQData>>4)&0x03;
			wDays+=wCurJQData+14;
		}
	}
	GetDateFromOrdinal(sYear,wDays+wXiaoHanOrder,&wMonth,&wJieQi[1]);//wMonth中的第二个节气
	GetDateFromOrdinal(sYear,wDays+wXiaoHanOrder-wCurJQData-14,&wMonth,&wJieQi[0]);//第一个节气
	return TRUE;
}

unsigned short GetDayOfWeek(short sYear,unsigned short wMonth,unsigned short wDay)
{
	unsigned int DayofWeek=0;
	int uDayOrd=0;
	if (GetDayOrdinal(sYear,wMonth,wDay,&uDayOrd)==0)
	{
		return 0;
	}
	uDayOrd++;//一年中的第几天，因为GetDayOrdinal所得到的是索引，因此要加一
	sYear--;
	DayofWeek=(sYear+sYear/4-sYear/100+sYear/400+uDayOrd)%7;//这个只是算星期的通用公式
	return DayofWeek;
}

unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth)
{
	int days1=0,days2=0;
	int ret=0;
	if (wMonth==12)
	{
		return 31;//这里为了简便，判断12月就直接返回
	}
	ret=GetDayOrdinal(sYear,wMonth,1,&days1);//本月1日在年内的序数
	if (ret==0)
	{
		return ret; 
	}
	wMonth++;
	ret=GetDayOrdinal(sYear,wMonth,1,&days2);//下个月1日的年内序数
	if (ret==0)
	{
		return ret; 
	}
	ret=days2-days1;//下个月1日的序数减本月1日的序数
	return ret;
}

BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu)
{
	unsigned short wjq[2]={0};
	int ET_index=sYear-START_YEAR;//数九、梅雨及三伏的年份索引
	if (sYear<START_YEAR||sYear>=END_YEAR)
	{
		return FALSE;
	}
	if (sYear==START_YEAR)
	{
		*sYijiu=cPreDongzhiOrder;
	}else
	{
		GetJieQi(sYear-1,12,wjq);
		*sYijiu=wjq[1]-32;
	}
	*wChuFu=((wExtermSeason[ET_index]&0x3E)>>1)+180;
	*wMoFu=(*wChuFu)+((wExtermSeason[ET_index]&0x01)==1?30:20);
	return TRUE;
}

BOOL GetMeiYu(short sYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd)
{
	int ET_index=sYear-START_YEAR;//数九、梅雨及三伏的年份索引
	if (sYear<START_YEAR||sYear>=END_YEAR)
	{
		return FALSE;
	}
	*wRuMeiOrd=((wExtermSeason[ET_index]&0xF800)>>11)+150;
	*wChuMeiOrd=((wExtermSeason[ET_index]&0x07C0)>>6)+180;
	return TRUE;
}

BOOL ShowCalendar(short sYear,unsigned short wMonth)
{
	//要显示一个月的月历，有以下几个要点：
	//1.该月1日的星期
	//2.该月的总天数
	//3.该月1日对应的农历以及农历月大小，有时甚至需要知道下个月甚至下下个月的大小
	int iDayofweek_1st=0;//该月1日星期
	short sNYear=0;
	unsigned short wNMonth=0,wNDay=0;//农历年、月、日
	BOOL bNLeapMonth=FALSE;//闰月标志
	int iDaysofmonth=0;//公历月总天数
	int iNDaysofmonth=0;//农历月总天数
	int iPos=0,iGDayIdx=1,iNDayIdx=0,iNindex=1;//输出位置、公历日，农历日，农历输出天数（同步iDaysofmonth）
	int iFillFlag=0;//填充标志，0为公历星期填充，1为农历星期填充，2为公历填充，3为农历填充
	iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//取得1日的星期
	if (iDayofweek_1st==-1)
	{
		return FALSE;//输入年月有误
	}
	iDaysofmonth=GetDaysOfMonth(sYear,wMonth);//得到本月总天数
	Gongli2Nongli(sYear,wMonth,1,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//得到公历1日的农历
	iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//得到农历月总天数
	iNDayIdx=wNDay;//取出农历日
	if (iNDaysofmonth==0)
	{
		return FALSE;
	}
	printf_s("\t\t%d年%d月 农历 ",sYear,wMonth);
	if (bNLeapMonth==1)
	{
		printf_s("闰");
	}
	if (iNDaysofmonth==29)
	{
		printf_s("%s（小）\n\n",Yueming[wNMonth-1]);
	}else if (iNDaysofmonth==30)
	{
		printf_s("%s（大）\n\n",Yueming[wNMonth-1]);
	}
	for (iPos=0;iPos<7;iPos++)
	{
		printf_s("%s\t",Xingqi[iPos]);
	}
	printf_s("\n_______________________________________________________\n\n");
	iPos=0;
	while (iNindex<=iDaysofmonth)
	{
		if (iFillFlag==0||iFillFlag==2)
		{
			if (iFillFlag==0)
			{
				while(iPos<iDayofweek_1st)//直到星期填充完
				{
					printf_s("\t");
					iPos++;//位置增加
				}
			}
			if (G_HolidayShow(sYear,wMonth,iGDayIdx)==0)
			{
				printf_s("  %2d\t",iGDayIdx);//输出农历
			}
			iPos++;
			iGDayIdx++;
			if (iGDayIdx>iDaysofmonth)
			{
				printf_s("\n");
				iPos=0;//位置重新回到开始
				iFillFlag=3;
			}else
			{
				if (iPos==7)//输出要换行了
				{
					printf_s("\n");
					iPos=0;//位置重新回到开始
					if (iFillFlag==0)
					{
						iFillFlag=1;//切换到农历星期填充
					}else
					{
						iFillFlag=3;
					}
				}
			}
		}else if (iFillFlag==1||iFillFlag==3)
		{
			if (iFillFlag==1)
			{
				while(iPos<iDayofweek_1st)//直到星期填充完
				{
					printf_s("\t");
					iPos++;//位置增加
				}
			}
			
			if (iNDayIdx<=iNDaysofmonth)
			{
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					if (iNDayIdx==1)
					{
						printf_s(" %s",Yueming[wNMonth-1]);//公历月首为农历月首
						if (iNDaysofmonth==30)
						{
							printf_s("大\t");
						}else
						{
							printf_s("小\t");
						}
					}else
					{
						printf_s(" %s\t",Riming[iNDayIdx-1]);//没有节日、节气等杂项输出时，输出农历日名
					}
				}
			}else
			{
				Gongli2Nongli(sYear,wMonth,iNindex,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//算出农历下一个月
				iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//重新得到农历月总天数
				iNDayIdx=wNDay;
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					//没有节日、节气等杂项输出时，输出农历月名
					if (bNLeapMonth==1)
					{
						printf_s("闰");
					}
					printf_s("%s",Yueming[wNMonth-1]);
					if (iNDaysofmonth==29)
					{
						printf_s("小");
					}else if (iNDaysofmonth==30)
					{
						printf_s("大");
					}
					if (bNLeapMonth==0)
					{
						printf_s("\t");
					}
				}
			}
			iPos++;
			iNDayIdx++;//农历日增加
			iNindex++;//农历已填充天数增加
			if (iPos==7)
			{
				if (!(iGDayIdx>=iDaysofmonth&&(iDaysofmonth+iDayofweek_1st)%7==0))
				{
					printf_s("\n\n");
				}
				iPos=0;
				iFillFlag=2;
			}
		}
	}
	printf_s("\n_______________________________________________________\n\n");
	return TRUE;
}

unsigned short G_HolidayShow(short sYear,unsigned short wMonth,unsigned short wDay)
{
	unsigned short wJQ_date[2]={0};//节气编号
	int iDayOrdial=0;//日期的年内序数
	int ET_index=sYear-START_YEAR;//数九、梅雨及三伏的年份索引
	int iDayofweek_1st=0;//月首星期
	int iDongzhi=0;//冬至
	unsigned short wrumei=0,wchumei=0,wchufu=0,wmofu=0;
	short sshujiu=0;
	int i=0;
	if (GetJieQi(sYear,wMonth,wJQ_date)==1)
	{
		if (wJQ_date[0]==wDay)
		{
			printf_s(" %s\t",Jieqi[((wMonth<<1)-1)%24]);//该月第一个节气
			return 1;
		}else if (wJQ_date[1]==wDay)
		{
			printf_s(" %s\t",Jieqi[(wMonth<<1)%24]);//该月第二个节气
			return 1;
		}
	}
	GetDayOrdinal(sYear,12,wJQ_date[1],&iDongzhi);//转换到年内序数
	if (GetDayOrdinal(sYear,wMonth,wDay,&iDayOrdial))
	{
		/*if (iDayOrdial==wExtermSeason[ET_index+5])
		{
			printf_s("[%s]\t",Shujiu[0]);//一九（即冬至，不需要判断了，上面冬至已经优先输出了）
			return 1;
		}else */
		GetExtremeSeason(sYear,&sshujiu,&wchufu,&wmofu);
		GetMeiYu(sYear,&wrumei,&wchumei);
		if (iDayOrdial==iDongzhi+9)
		{
			printf_s("[%s]\t",Shujiu[1]);//二九
			return 2;
		}
		if (iDayOrdial>=(sshujiu+9)&&iDayOrdial<sshujiu+81)
		{
			for (i=0;i<8;i++)
			{
				if (iDayOrdial==sshujiu+(i+1)*9)
				{
					printf_s("[%s]\t",Shujiu[i+1]);//三九至九九
					return 1;
				}
			}
		}else if (iDayOrdial==wrumei)
		{
			printf_s("[%s]\t",Meiyu[0]);//入梅
			return 1;
		}else if (iDayOrdial==wchumei)
		{
			printf_s("[%s]\t",Meiyu[1]);//出梅
			return 1;
		}else if (iDayOrdial==wchufu)
		{
			printf_s("[%s]\t",Sanfu[0]);//初伏
			return 1;
		}else if (iDayOrdial==wchufu+10)
		{
			printf_s("[%s]\t",Sanfu[1]);//中伏
			return 1;
		}else if (iDayOrdial==wmofu)
		{	printf_s("[%s]\t",Sanfu[2]);//末伏
			return 1;
		}
	}
	if (wMonth==1)
	{
		if (wDay==1)
		{
			printf_s(" 元旦\t");
			return 1;
		}
	}else if (wMonth==2)
	{
		if (wDay==14)
		{
			printf_s("情人节\t");
			return 1;
		}
	}else if (wMonth==3)
	{
		switch (wDay)
		{
		case 5:
			if (sYear>=1963)
			{
				printf_s("学雷锋日");
				return 1;
			}
			break;
		case 8:
			if (sYear>=1900)
			{
				printf_s("妇女节\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1928)
			{
				printf_s("植树节\t");
				return 1;
			}
			break;
		case 15:
			if (sYear>=1983)
			{
				printf_s("消权日\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==4)
	{
		if (wDay==1)
		{
			printf_s("愚人节\t");
			return 1;
		}
	}else if (wMonth==5)
	{
		if (sYear>=1872)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//取月首星期
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==2)//5月第二个周日母亲节
			{
				printf_s("母亲节\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>=1890)
			{
				printf_s("劳动节\t");
				return 1;
			}
			break;
		case 4:
			if (sYear>=1919)
			{
				printf_s("青年节\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1912)
			{
				printf_s("护士节\t");
				return 1;
			}
			break;
		case 31:
			if (sYear>=1989)
			{
				printf_s("无烟日\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==6)
	{
		if (sYear>=1910)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//取月首星期
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==3)//6月第三个周日父亲节
			{
				printf_s("父亲节\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>1949)
			{
				printf_s("儿童节\t");
				return 1;
			}
			break;
		case 5:
			if (sYear>=1972)
			{
				printf_s("环境日\t");
				return 1;
			}
			break;
		case 26:
			if (sYear>=1987)
			{
				printf_s("禁毒日\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==7)
	{
		switch (wDay)
		{
		case 1:
			if (sYear>=1921)
			{
				printf_s("中共诞辰");
				return 1;
			}
			break;
		case 7:
			if (sYear>=1937)
			{
				printf_s("抗战纪念");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==8)
	{
		if (wDay==1)
		{
			if (sYear>=1933)
			{
				printf_s("建军节\t");
				return 1;
			}
		}
	}else if (wMonth==9)
	{
		switch (wDay)
		{
		case 3:
			if (sYear>=1945)
			{
				printf_s("抗战胜利");
				return 1;
			}
			break;
		case 10:
			if (sYear>=1985)
			{
				printf_s("教师节\t");
				return 1;
			}
			break;
		default:
			break;
		}
	}else if (wMonth==10)
	{
		if (wDay==1)
		{
			if (sYear>=1949)
			{
				printf_s(" 国庆\t");
				return 1;
			}
		}
	}else if (wMonth==11)
	{
		if (sYear>=1941)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//取月首星期
			if ((wDay+iDayofweek_1st-1)%7==4&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==4?7:0))/7)==4)//11月第四个周四感恩节
			{
				printf_s("感恩节\t");
				return 1;
			}
		}
		if (wDay==1)
		{
			printf_s("万圣节\t");
			return 1;
		}
	}else if (wMonth==12)
	{
		switch (wDay)
		{
		case 10:
			if (sYear>=1948)
			{
				printf_s("人权日\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1936)
			{
				printf_s("西安事变");
				return 1;
			}
			break;
		case 24:
			printf_s("平安夜\t");
			return 1;
		case 25:
			printf_s("圣诞节\t");
			return 1;
		default:
			break;
		}
	}
	return 0;
}

BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth)
{
	int LeapMonth=LunarGetLeapMonth(sLYear);//取该年农历闰月
	int DayofLM_12=0;//农历十二月的总天数
	if (iLeapMonth==0)
	{
		if (iLMonth==1)
		{
			switch (iLDay)
			{
			case 1:
				printf_s(" 春节\t");
				return TRUE;
			case 15:
				printf_s("元宵节\t");
				return TRUE;
			default:
				break;
			}
		}else if (iLMonth==2)
		{
			if (iLDay==2)
			{
				printf_s("春龙节\t");
				return TRUE;
			}
		}else if (iLMonth==5)
		{
			if (iLDay==5)
			{
				printf_s("端午节\t");
				return TRUE;
			}
		}else if (iLMonth==7)
		{
			if (iLDay==7)
			{
				printf_s(" 七夕\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf_s("中元节\t");
				return TRUE;
			}
		}else if (iLMonth==8)
		{
			if (iLDay==15)
			{
				printf_s("中秋节\t");
				return TRUE;
			}
		}else if (iLMonth==9)
		{
			if (iLDay==9)
			{
				printf_s("重阳节\t");
				return TRUE;
			}
		}else if (iLMonth==10)
		{
			if (iLDay==1)
			{
				printf_s("祭祖节\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf_s("下元节\t");
				return TRUE;
			}
		}else if (iLMonth==12)
		{
			if (LeapMonth!=12)
			{
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,0);//非闰十二月
				if (iLDay==8)
				{
					printf_s("腊八节\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf_s(" 小年\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//农历十二月的最后一天是除夕
				{
					printf_s(" 除夕\t");
					return TRUE;
				}
			}
		}
	}else
	{
		if (iLeapMonth==LeapMonth)
		{
			if (iLeapMonth==12)
			{
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,1);//闰十二月
				if (iLDay==8)
				{
					printf_s("腊八节\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf_s(" 小年\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//农历十二月的最后一天是除夕
				{
					printf_s(" 除夕\t");
					return TRUE;
				}
			}
		}
	}
	return FALSE;//没有节日等
}
/*
void ShowMenu()
{
	printf_s("**************************************\n");
	printf_s("*                                    *\n");
	printf_s("*             万年历查询             *\n");
	printf_s("*                                    *\n");
	printf_s("*    %d年至%d年（不含%d年）    *\n",START_YEAR,END_YEAR,END_YEAR);
	printf_s("*                                    *\n");
	printf_s("**************************************\n");
	printf_s("\n\n");
	printf_s("◆1. 月历显示\n◆2. 公历转农历\n◆3. 农历转公历\n◆4. 节气查询\n\n\n");
	printf_s("请选择：");
}

void GL2NL()
{
	unsigned short wMonth=0,wDay=0,iLMonth=0,iLDay=0,iDayofweek=0;
	short sYear=0,sLYear=0;
	BOOL bLLeapMonth=FALSE;
	int ret=0;
	system("cls");
	printf_s("◆2. 公历转农历\n\n");
	do 
	{
		printf_s("请输入公历日期，年 月 日：>");
		scanf_s("%d %d %d",&sYear,&wMonth,&wDay);
		iDayofweek=GetDayOfWeek(sYear,wMonth,wDay);
		ret=Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&iLMonth,&iLDay,&bLLeapMonth);
		if (ret==0)
		{
			printf_s("\n您的输入有误，");
		}
	} while (ret==0);
	if (bLLeapMonth)
	{
		printf_s("%d年%d月%d日转为农历为：%d年 闰%s %s",sYear,wMonth,wDay,sLYear,Yueming[iLMonth-1],Riming[iLDay-1]);
	}else
	{
		printf_s("%d年%d月%d日转为农历为：%d年 %s %s",sYear,wMonth,wDay,sLYear,Yueming[iLMonth-1],Riming[iLDay-1]);
	}
	printf_s("  %s\n\n",Xingqi[iDayofweek]);
	system("pause");
	system("cls");
}

void NL2GL()
{
	unsigned short wMonth=0,wDay=0,iLMonth=0,iLDay=0,iDayofweek=0;
	short sYear=0,sLYear=0,bLLeapMonth=0;
	int ret=0;
	system("cls");
	printf_s("◆3. 农历转公历\n\n");
	do 
	{
		printf_s("请输入农历日期以及是否闰月（闰月用1表示，非闰月用0表示）。\n年 月 日 是否闰月：>");
		scanf_s("%d %d %d %d",&sLYear,&iLMonth,&iLDay,&bLLeapMonth);
		ret=Nongli2Gongli(sLYear,iLMonth,iLDay,bLLeapMonth,&sYear,&wMonth,&wDay);
		if (ret==0)
		{
			printf_s("\n您的输入有误，");
		}
	} while (ret==0);
	if (bLLeapMonth)
	{
		printf_s("农历 %d年 闰%s %s 转为公历为 %d年%d月%d日\n\n",sLYear,Yueming[iLMonth-1],Riming[iLDay-1],sYear,wMonth,wDay);
	}else
	{
		printf_s("农历 %d年 %s %s 转为公历为 %d年%d月%d日\n\n",sLYear,Yueming[iLMonth-1],Riming[iLDay-1],sYear,wMonth,wDay);
	}
	system("pause");
	system("cls");
}

void RL()
{
	int iYear=0;
	int iMonth=0;
	BOOL ret=FALSE;
	system("cls");
	printf_s("◆1. 月历显示\n\n");
	do 
	{
		printf_s("请输入年、月：Year Month>");
		scanf_s("%d %d",&iYear,&iMonth);
		ret=ShowCalendar(iYear,iMonth);
		ret=TRUE;
		if (ret==FALSE)
		{
			printf_s("\n您的输入有误，");
		}
	} while (ret==FALSE);
	system("pause");
	system("cls");
}

void JQ()
{
	int i=0,ret=0;
	short sYear=0,iIndex=0,sLYear=0;
	unsigned short wMonth=0,wLMonth=0,wDay=0,wLDay=0;
	BOOL bLeapMonth=FALSE;
	unsigned short JQ_date[2]={0};
	system("cls");
	printf_s("◆4. 节气查询\n\n");
	for (i=0;i<24;i++)
	{
		printf_s("% 2d. %s\t",i+1,Jieqi[i]);
		if (i%4==3)
		{
			printf_s("\n");
		}
	}
	printf_s("请输入年份以及要查询的节气编号：Year Index>");
	scanf_s("%d %d",&sYear,&iIndex);
	if (iIndex==1)
	{
		iIndex+=24;
	}
	wMonth=(iIndex)/2;//转换到月份
	do 
	{
		ret=GetJieQi(sYear,wMonth,JQ_date);//取指定月份节气（两个节气）
		if (ret==0)
		{
			printf_s("输入错误，请重新输入年份以及要查询的节气编号：Year Index>");
			scanf_s("%d %d",&sYear,&iIndex);
			if (iIndex==1)
			{
				iIndex+=24;
			}
			wMonth=(iIndex)/2;
		}
	} while (ret==0);
	if (iIndex%2==0)
	{
		wDay=(int)JQ_date[0];//第一个节气
	}else
	{
		wDay=(int)JQ_date[1];//第二个节气
	}
	if (Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&wLMonth,&wLDay,&bLeapMonth)==0)//转到农历
	{
		printf_s("查询农历失败\n");
	}else
	{
		printf_s("%d年 %s 时间为 %d月%d日，农历 ",sYear,Jieqi[(iIndex-1)%24],wMonth,wDay);
		if (bLeapMonth==TRUE)//如果是闰月
		{
			printf_s("闰");
		}
		printf_s("%d年 %s %s\n\n",sLYear,Yueming[wLMonth-1],Riming[wLDay-1]);
	}
	system("pause");
	system("cls");
}
*/