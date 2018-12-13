#pragma once
#include "define.h"
#include "NumTrans.h"
#include "StrInfo.h"
#include "LunarData.h"



//�ж����꣬��������ݣ�����ֵ��0-ƽ�꣬1-����
BOOL IsLeapYear(short sYear);

//�������������ڵ��������������꣬�£��գ���������������ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays);

//���������������¡��գ��������꣬�����������£��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay);

//�����ꡢ�¡��յĺϷ��ԣ��������꣬�£��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL DateCheck(short sYear,unsigned short wMonth,unsigned short wDay);

//��ȡũ������Ĺ�������������������ũ���꣬����ֵ��ũ������Ĺ�����������
short LunarGetNewYearOrdinal(short sLunarYear);

//��ȡũ���µ�������������ũ���꣬ũ���£��Ƿ�Ϊ���£�����ֵ����ũ���µ�������Ϊ0���������Ч
unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth);

//չ����С�����ݱ�ĳһ��ģ���������ũ���꣬����һ��ʮһ�¿�ʼ����ǰ��ݣ���ʮ���µ�ÿ������������ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15]);

//��ȡũ��ĳһ������������������ũ���꣬����ֵ������������·ݣ�0��ʾ������
unsigned short LunarGetLeapMonth(short sLunarYear);

//��ȡũ���·���Ϣ
BOOL GetMonthInfo(unsigned short wYear,unsigned int* puData);

//����תũ���������������ꡢ�¡��գ�ũ���ꡢ�¡��գ��Ƿ�Ϊ���£�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL Gongli2Nongli(short sYear,unsigned short wMonth,unsigned short wDay,short* sLunarYear,unsigned short* wLunarMonth,unsigned short* wLunarDay,BOOL* bLeapMonth);

//ũ��ת�����������������ꡢ�¡��գ��Ƿ�Ϊ���£������ꡢ�¡��գ�����ֵ��0-ʧ�ܣ�1-�ɹ�
BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay);

//�õ�ָ����ݵĽ�����Ϣ���׸���С��
BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2]);

//�������ڣ�����-1��ʾ����������ղ���ȷ���߳�����ݷ�Χ
unsigned short GetDayOfWeek(short sYear,unsigned short wMonth,unsigned short wDay);

//����ĳ���µ������������������������0��ʾ���������
unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth);

//�������ռ�������ʾ�������������ꡢ�����¡�������
unsigned short G_HolidayShow(short sYear,unsigned short wMonth,unsigned short wDay);

//ũ�����ռ�������ʾ��������ũ���ꡢũ���¡�ũ���ա�ũ������
BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth);

//��ѯĳһ������ż������������������ꡢ��һ�궬������һ�ţ���������ĩ��
BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu);

//��ѯĳһ�����÷����÷�������������꣬��÷����÷
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
	map<string,int> _weekmap;//���ڶ�Ӧ������
	map<string,int> _difmap;//�롰���족��������
	map<int,map<string,string>> _holidaymap;
	map<string,string> _glmap;//����
	map<string,string> _nlmap;//ũ��
	map<string,int> _jqmap;//����
	void _SetDateDict();
	void _GetDiffDate();
	void _GetHoliday();
	void _SetNL();
	void _SetGL();
	void _SetJQ();
	void _GetNowTime(struct tm& nowTime);
	void _GetNewFormTime(char* newTime,int difDay);
	//���ܡ������֮��ת��
	bool _CheckNextWeek(const string& str);
	//�µ�ǰ��
	bool _CheckCurrentWeek(const string& str);
	//���졢����֮��ת��
	bool _CheckNextDay(const string& str,int& difDay);
	//�ж��Ƿ��Ǽ��ڣ���ʱд��
	bool _CheckHoliday(string& dateStr,const string& str);
	bool _CheckGL(string& dateStr,const string& str,const int year);
	bool _CheckNL(string& dateStr,const string& str,const int year);
	bool _CheckJQ(string& dateStr,const string& str,const int year);
	//ũ��ת����
	bool _NL2GL(string& dateStr,const string& str);
	//����֮��ת�������¼���
	void _TranDate(string& dstDate,const string& srcDate);
	//���ڸ�ʽ��
	void _FormDate(string& dstDate,int year,int month,int day);

	//��ݻ�ȡ
	void _GetYear(int& year);
	//�·ݻ�ȡ
	void _GetMonth(int& month);
	//���ڻ�ȡ
	void _GetDay(int& day);
	//�ж��Ƿ���Ҫ��λmonth:[1,12]
	bool _CheckDateEnd(int& year,int& month,int& day);
public:
	void DateSwitch(string& dstDate,const string& srcDate);
};

