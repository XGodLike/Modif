#pragma once
#include "define.h"
#include "NumTrans.h"
#include "StrInfo.h"
#include "LunarData.h"



//判断闰年，参数：年份，返回值：0-平年，1-闰年
BOOL IsLeapYear(short sYear);

//计算日期在年内的序数，参数：年，月，日，年内序数，返回值：0-失败，1-成功
BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays);

//从年内序数计算月、日，参数：年，年内序数，月，日，返回值：0-失败，1-成功
BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay);

//检验年、月、日的合法性，参数：年，月，日，返回值：0-失败，1-成功
BOOL DateCheck(short sYear,unsigned short wMonth,unsigned short wDay);

//获取农历新年的公历年内序数，参数：农历年，返回值：农历新年的公历年内序数
short LunarGetNewYearOrdinal(short sLunarYear);

//获取农历月的天数，参数：农历年，农历月，是否为闰月，返回值：该农历月的天数，为0代表参数无效
unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth);

//展开大小月数据表（某一年的），参数：农历年，从上一年十一月开始到当前年份（闰）十二月的每月天数，返回值：0-失败，1-成功
BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15]);

//获取农历某一年的闰月情况，参数：农历年，返回值，该年的闰月月份，0表示无闰月
unsigned short LunarGetLeapMonth(short sLunarYear);

//获取农历月份信息
BOOL GetMonthInfo(unsigned short wYear,unsigned int* puData);

//公历转农历，参数：公历年、月、日，农历年、月、日，是否为闰月，返回值：0-失败，1-成功
BOOL Gongli2Nongli(short sYear,unsigned short wMonth,unsigned short wDay,short* sLunarYear,unsigned short* wLunarMonth,unsigned short* wLunarDay,BOOL* bLeapMonth);

//农历转公历，参数：家历年、月、日，是否为闰月，公历年、月、日，返回值：0-失败，1-成功
BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay);

//得到指定年份的节气信息，首个是小寒
BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2]);

//计算星期，返回-1表示输入的年月日不正确或者超出年份范围
unsigned short GetDayOfWeek(short sYear,unsigned short wMonth,unsigned short wDay);

//计算某个月的天数，返回天数，如果返回0表示年或月有误
unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth);

//公历节日及节气显示，参数：公历年、公历月、公历日
unsigned short G_HolidayShow(short sYear,unsigned short wMonth,unsigned short wDay);

//农历节日及杂项显示，参数：农历年、农历月、农历日、农历闰月
BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth);

//查询某一年的数九及三伏，参数：公历年、上一年冬至（即一九）、初伏、末伏
BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu);

//查询某一年的入梅、出梅，参数：公历年，入梅，出梅
BOOL GetMeiYu(short sYear,unsigned short* wRuMeiOrd,unsigned short* wChuMeiOrd);


class CDateTrans:public CNumTrans,public CStrInfo
{
public:
	CDateTrans(void);
	~CDateTrans(void);
	CDateTrans(const string& weekfile);
private:
	string _datefile;
	struct tm _nowtime;
	map<string,int> _weekmap;//日期对应的天数
	map<string,int> _difmap;//与“今天”相差的天数
	map<int,map<string,string>> _holidaymap;
	map<string,string> _glmap;//公历
	map<string,string> _nlmap;//农历
	map<string,int> _jqmap;//节气
	void _SetDateDict();
	void _GetDiffDate();
	void _GetHoliday();
	void _SetNL();
	void _SetGL();
	void _SetJQ();
	void _GetNowTime(struct tm& nowTime);
	void _GetNewFormTime(char* newTime,int difDay);
	//下周、下礼拜之类转换
	bool _CheckNextWeek(const string& str);
	//下当前周
	bool _CheckCurrentWeek(const string& str);
	//今天、明天之类转换
	bool _CheckNextDay(const string& str,int& difDay);
	//判断是否是假期，暂时写死
	bool _CheckHoliday(string& dateStr,const string& str);
	bool _CheckGL(string& dateStr,const string& str,const int year);
	bool _CheckNL(string& dateStr,const string& str,const int year);
	bool _CheckJQ(string& dateStr,const string& str,const int year);
	//农历转公历
	bool _NL2GL(string& dateStr,const string& str);
	//日期之类转换；几月几号
	void _TranDate(string& dstDate,const string& srcDate);
	//日期格式化
	void _FormDate(string& dstDate,int year,int month,int day);

	//年份获取
	void _GetYear(int& year);
	//月份获取
	void _GetMonth(int& month);
	//日期获取
	void _GetDay(int& day);
	//判断是否需要进位month:[1,12]
	bool _CheckDateEnd(int& year,int& month,int& day);
public:
	void DateSwitch(string& dstDate,const string& srcDate);
};

