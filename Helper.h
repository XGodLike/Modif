#ifndef _HELPER_H_
#define _HELPER_H_

#ifndef BOOL
typedef int BOOL;
#endif //BOOL

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/*
注意，年干支计算请参照根目录下“农历简介.txt”中的方法。月干支计算比较复杂，
是以节气为界（注意，不是中气，节气指立春、惊蛰、清明、立夏、芒种、小暑、立
秋、白露、寒露、立冬、大雪、小寒这12个，其余的即为中气），1998年12月7日(大
雪)的月干支为甲子，可在此基础上进行前推和后推。日干支以2000年1月7日（甲子
日）为参考，只要算出天数差即可知道日干支。时干支则是根据日干支来推算的，天
干根据日的天干有以下对应关系，甲、己得甲，乙、庚得丙，丙、辛得戊，丁、壬得
庚，戊、癸得壬，时地支则为按每两个小时为一个地支来计量，前一天的23时至1时为
子时，1时至3时为丑时，依此类推。
*/

/*
本例中的星期算法采用的是一个通用算法，公式如下：
W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
Y是年份数，D是这一天在这一年中的年内序数加1，也就是这一天在这一年中是第几天。
这个公式大致验证了一下是可行的，就本例所支持的年份区间内至少是正确的。
*/

char *Riming[30]={"初一","初二","初三","初四","初五","初六","初七","初八","初九","初十","十一","十二","十三","十四","十五","十六","十七","十八","十九","二十","廿一","廿二","廿三","廿四","廿五","廿六","廿七","廿八","廿九","三十"};
char *Yueming[12]={"正月","二月","三月","四月","五月","六月","七月","八月","九月","十月","冬月","腊月"};
char *Tiangan[10]={"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
char *Dizhi[12]={"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};
char *Shengxiao[12]={"鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪" };
char *Jieqi[24]={"冬至", "小寒", "大寒", "立春", "雨水", "惊蛰", "春分", "清明", "谷雨", "立夏", "小满", "芒种", "夏至", "小暑", "大暑", "立秋", "处暑", "白露", "秋分", "寒露", "霜降", "立冬", "小雪", "大雪"};
char *Xingqi[7]={"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
char *Shujiu[9]={"一九","二九","三九","四九","五九","六九","七九","八九","九九"};
char *Meiyu[2]={"入梅","出梅"};
char *Sanfu[3]={"初伏","中伏","末伏"};

unsigned short DayOrdinal[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};
unsigned short DayOrdinalLeap[13]={0,31,60,91,121,152,182,213,244,274,305,335,366};

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

//===============================================================================
/*
void ShowMenu(void);//显示菜单
void GL2NL(void);//公历转农历
void NL2GL(void);//农历转公历
void RL(void);//显示一个月的日历
void JQ(void);//节气查询
*/
#endif //_HELPER_H_