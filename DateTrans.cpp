#include "stdafx.h"
#include "DateTrans.h"

/*
ע�⣬���֧��������ո�Ŀ¼�¡�ũ�����.txt���еķ������¸�֧����Ƚϸ��ӣ�
���Խ���Ϊ�磨ע�⣬��������������ָ���������ݡ����������ġ�â�֡�С���
���¶����¶����������ѩ��С����12��������ļ�Ϊ��������1998��12��7��(��
ѩ)���¸�֧Ϊ���ӣ����ڴ˻����Ͻ���ǰ�ƺͺ��ơ��ո�֧��2000��1��7�գ�����
�գ�Ϊ�ο���ֻҪ����������֪���ո�֧��ʱ��֧���Ǹ����ո�֧������ģ���
�ɸ����յ���������¶�Ӧ��ϵ���ס����üף��ҡ����ñ������������죬�����ɵ�
�����졢����ɣ�ʱ��֧��Ϊ��ÿ����СʱΪһ����֧��������ǰһ���23ʱ��1ʱΪ
��ʱ��1ʱ��3ʱΪ��ʱ���������ơ�
*/

/*
�����е������㷨���õ���һ��ͨ���㷨����ʽ���£�
W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
Y���������D����һ������һ���е�����������1��Ҳ������һ������һ�����ǵڼ��졣
�����ʽ������֤��һ���ǿ��еģ��ͱ�����֧�ֵ������������������ȷ�ġ�
*/
char *Riming[30]={"��һ","����","����","����","����","����","����","����","����","��ʮ","ʮһ","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","��ʮ","إһ","إ��","إ��","إ��","إ��","إ��","إ��","إ��","إ��","��ʮ"};
char *Yueming[12]={"����","����","����","����","����","����","����","����","����","ʮ��","����","����"};
char *Tiangan[10]={"��", "��", "��", "��", "��", "��", "��", "��", "��", "��"};
char *Dizhi[12]={"��", "��", "��", "î", "��", "��", "��", "δ", "��", "��", "��", "��"};
char *Shengxiao[12]={"��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" };
char *Jieqi[24]={"����", "С��", "��", "����", "��ˮ", "����", "����", "����", "����", "����", "С��", "â��", "����", "С��", "����", "����", "����", "��¶", "���", "��¶", "˪��", "����", "Сѩ", "��ѩ"};
char *Xingqi[7]={"������","����һ","���ڶ�","������","������","������","������"};
char *Shujiu[9]={"һ��","����","����","�ľ�","���","����","�߾�","�˾�","�ž�"};
char *Meiyu[2]={"��÷","��÷"};
char *Sanfu[3]={"����","�з�","ĩ��"};

unsigned short DayOrdinal[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};
unsigned short DayOrdinalLeap[13]={0,31,60,91,121,152,182,213,244,274,305,335,366};


CDateTrans::CDateTrans(void)
{
#ifndef LOAD_RESOURCE
	char szFilePath[MAX_SIZE];
	GetCurrentDirectory(MAX_SIZE,szFilePath);
	strcat_s(szFilePath,"\\model\\Modif_Date.dct");	
	_datefile = szFilePath;
#endif
	_GetDiffDate();	
	_SetDateDict();	
	//_GetHoliday();
	_SetNL();
	_SetGL();
	_SetJQ();
}

CDateTrans::CDateTrans(const string& weekfile):_datefile(weekfile)
{
	_SetDateDict();
	_GetDiffDate();
}

CDateTrans::~CDateTrans(void)
{

}

void CDateTrans::_SetDateDict()
{
	_weekmap.insert(make_pair("��һ",1));
	_weekmap.insert(make_pair("�ܶ�",2));
	_weekmap.insert(make_pair("����",3));
	_weekmap.insert(make_pair("����",4));
	_weekmap.insert(make_pair("����",5));
	_weekmap.insert(make_pair("����",6));
	_weekmap.insert(make_pair("����",0));
	_weekmap.insert(make_pair("��ĩ",0));//��ĩ���������մ���
	_weekmap.insert(make_pair("����",7));
	_weekmap.insert(make_pair("����һ",1));
	_weekmap.insert(make_pair("���ڶ�",2));
	_weekmap.insert(make_pair("������",3));
	_weekmap.insert(make_pair("������",4));
	_weekmap.insert(make_pair("������",5));
	_weekmap.insert(make_pair("������",6));
	_weekmap.insert(make_pair("������",0));
	_weekmap.insert(make_pair("������",7));
	_weekmap.insert(make_pair("���һ",1));
	_weekmap.insert(make_pair("��ݶ�",2));
	_weekmap.insert(make_pair("�����",3));
	_weekmap.insert(make_pair("�����",4));
	_weekmap.insert(make_pair("�����",5));
	_weekmap.insert(make_pair("�����",6));
	_weekmap.insert(make_pair("�����",0));
	_weekmap.insert(make_pair("�����",7));
	return;
}

#ifdef LOAD_RESOURCE
void CDateTrans::_GetDiffDate()
{
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT4), "DCT"); //������Դ
	nSize = SizeofResource(hInst,hsrc); //������Դ��С

	//��ȡ��Դ�׵�ַ
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_difmap,buf,"\r\n");
	//�ͷ���Դ
	delete[] buf;
	FreeResource(hglb);
}
#else
void CDateTrans::_GetDiffDate()
{
	vector<string> vtmp;
	FILE* pf;
	fopen_s(&pf,_datefile.c_str(),"rb");
	if(pf == NULL)
	{
		return  ;
	}

	string key = "";
	signed int value=0;
	char buf[MAX_SIZE]= {0};
	while (fscanf(pf,"%s",buf) != EOF)
	{
		sscanf(buf,"%[^=]=%d",(char*)key.c_str(),&value);
		_difmap.insert(make_pair(key.c_str(),value));
	}

	fclose(pf);
}
#endif
void CDateTrans::_GetHoliday()
{
	//HRSRC hsrc = 0;
	//int nSize = 0;
	//HGLOBAL hglb = 0;
	//void * sBuf = 0;
	//
	//HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	//hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT5), "DCT"); //������Դ
	//nSize = SizeofResource(hInst,hsrc); //������Դ��С
	//
	////��ȡ��Դ�׵�ַ
	//hglb = LoadResource(hInst, hsrc);
	//sBuf = LockResource(hglb);
	//char* buf = new CHAR[nSize];
	//memset(buf,NULL,sizeof(char)*nSize);
	//memcpy(buf, sBuf, nSize);
	//Split(_holidaymap,buf,"\r\n");
	////�ͷ���Դ
	//delete[] buf;
	//FreeResource(hglb);
}

void CDateTrans::_SetNL()
{
	_nlmap.insert(make_pair("����","1 1"));
	_nlmap.insert(make_pair("Ԫ����","1 15"));
	_nlmap.insert(make_pair("����","5 5"));
	_nlmap.insert(make_pair("�����","5 5"));
	_nlmap.insert(make_pair("��Ϧ","7 7"));
	_nlmap.insert(make_pair("��Ϧ��","7 7"));
	_nlmap.insert(make_pair("��Ϧ���˽�","7 7"));
	_nlmap.insert(make_pair("��Ԫ��","7 15"));
	_nlmap.insert(make_pair("����","8 15"));
	_nlmap.insert(make_pair("�����","8 15"));
	_nlmap.insert(make_pair("����","9 9"));
	_nlmap.insert(make_pair("������","9 9"));
	_nlmap.insert(make_pair("����","12 8"));
	_nlmap.insert(make_pair("���˽�","12 8"));
	_nlmap.insert(make_pair("С��","12 24"));
	_nlmap.insert(make_pair("��Ϧ","12 30"));
}

void CDateTrans::_SetGL()
{
	_glmap.insert(make_pair("���˽�","02-14"));
	_glmap.insert(make_pair("���˸�Ů��","03-08"));
	_glmap.insert(make_pair("��Ů��","03-08"));
	_glmap.insert(make_pair("ֲ����","03-12"));
	_glmap.insert(make_pair("������Ȩ����","03-15"));
	_glmap.insert(make_pair("��һ��","03-15"));
	_glmap.insert(make_pair("������","03-15"));
	_glmap.insert(make_pair("���˽�","04-01"));
	_glmap.insert(make_pair("����������","04-07"));
	_glmap.insert(make_pair("���������","04-22"));
	_glmap.insert(make_pair("�Ͷ���","05-01"));
	_glmap.insert(make_pair("��һ","05-01"));
	_glmap.insert(make_pair("�����Ͷ���","05-01"));
	_glmap.insert(make_pair("�����","05-04"));
	_glmap.insert(make_pair("���������","05-04"));
	_glmap.insert(make_pair("���ʺ�ʮ����","05-12"));
	_glmap.insert(make_pair("���ʼ�ͥ��","05-15"));
	_glmap.insert(make_pair("���ʵ�����","05-17"));
	_glmap.insert(make_pair("��ͯ��","06-01"));
	_glmap.insert(make_pair("��һ��ͯ��","06-01"));
	_glmap.insert(make_pair("���ʶ�ͯ��","06-01"));
	_glmap.insert(make_pair("���绷��������","06-05"));
	_glmap.insert(make_pair("ȫ��������","06-06"));
	_glmap.insert(make_pair("ȫ��������","06-25"));
	_glmap.insert(make_pair("���ʽ�����","06-26"));
	_glmap.insert(make_pair("������","07-01"));
	_glmap.insert(make_pair("����ս��������","07-07"));
	_glmap.insert(make_pair("������","08-01"));
	_glmap.insert(make_pair("��ʦ��","09-10"));
	_glmap.insert(make_pair("����������","09-27"));
	_glmap.insert(make_pair("����","10-01"));
	_glmap.insert(make_pair("�����","10-01"));
	_glmap.insert(make_pair("���˽�","10-06"));
	_glmap.insert(make_pair("����������","10-09"));
	_glmap.insert(make_pair("�����׼��","10-14"));
	_glmap.insert(make_pair("������ʳ��","10-16"));
	_glmap.insert(make_pair("���Ϲ���","10-24"));
	_glmap.insert(make_pair("ʥ��","12-25"));
	_glmap.insert(make_pair("ʥ����","12-25"));
	_glmap.insert(make_pair("Ԫ��","01-01"));
}

void CDateTrans::_SetJQ()
{
	_jqmap.insert(make_pair("����",1));
	_jqmap.insert(make_pair("С��",2));
	_jqmap.insert(make_pair("��",3));
	_jqmap.insert(make_pair("����",4));
	_jqmap.insert(make_pair("��ˮ",5));
	_jqmap.insert(make_pair("����",6));
	_jqmap.insert(make_pair("����",7));
	_jqmap.insert(make_pair("����",8));
	_jqmap.insert(make_pair("������",8));
	_jqmap.insert(make_pair("����",9));
	_jqmap.insert(make_pair("����",10));
	_jqmap.insert(make_pair("С��",11));
	_jqmap.insert(make_pair("â��",12));
	_jqmap.insert(make_pair("����",13));
	_jqmap.insert(make_pair("С��",14));
	_jqmap.insert(make_pair("����",15));
	_jqmap.insert(make_pair("����",16));
	_jqmap.insert(make_pair("����",17));
	_jqmap.insert(make_pair("��¶",18));
	_jqmap.insert(make_pair("���",19));
	_jqmap.insert(make_pair("��¶",20));
	_jqmap.insert(make_pair("˪��",21));
	_jqmap.insert(make_pair("����",22));
	_jqmap.insert(make_pair("Сѩ",23));
	_jqmap.insert(make_pair("��ѩ",24));
}

void CDateTrans::_GetNowTime(struct tm& nowTime)
{
	time_t st = time(0) ;
	localtime_s(&nowTime,&st);
	//strftime(nowTime, sizeof(nowTime), "%Y-%m-%d",&tTime); 
}

void CDateTrans::_GetNewFormTime(char* newTime,int difDay)
{
	int year = _nowtime.tm_year+1900;
	int month = _nowtime.tm_mon + 1;
	int day = _nowtime.tm_mday + difDay;
	_CheckDateEnd(year,month,day);
	sprintf(newTime,"%d-%02d-%02d",year,month,day);
}

bool CDateTrans::_CheckNextWeek(const string& str)
{
	if (str.find("����")!= string::npos || 
		str.find("������")!= string::npos ||
		str.find("�����")!= string::npos)
	{
		return true;
	}
	return false;
}

bool CDateTrans::_CheckCurrentWeek(const string& str)
{
	map<string,int>::iterator it = _weekmap.begin();
	for (;it!=_weekmap.end();it++)
	{
		if (strcmp((*it).first.c_str(),str.c_str()) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CDateTrans::_CheckNextDay(const string& str,int& difDay)
{
	map<string,int>::iterator it = _difmap.begin();
	for (;it!=_difmap.end();it++)
	{
		if (strcmp((*it).first.c_str(),str.c_str()) == 0)
		{
			difDay = (*it).second;
			return true;
		}
	}
	return false;
}

bool CDateTrans::_CheckHoliday(string& dateStr,const string& str)
{
	bool ret = false;
	int HolidayYear = 0;

	struct tm nowTime;
	_GetNowTime(nowTime);
	HolidayYear = nowTime.tm_year + 1900;

	map<int,map<string,string>>::iterator it = _holidaymap.find(HolidayYear);
	if (it != _holidaymap.end())
	{
		map<string,string>::iterator ot = (*it).second.find(str);
		if (ot != (*it).second.end())
		{
			dateStr = (*ot).second;
			ret =  true;
		}
	}
	else if(_CheckGL(dateStr,str,HolidayYear))//����
	{
		ret = true;
	}
	else if(_CheckNL(dateStr,str,HolidayYear))//ũ��
	{
		string NLstr = dateStr;
		_NL2GL(dateStr,NLstr);
		ret = true;
	}else if(_CheckJQ(dateStr,str,HolidayYear))//����
	{
		ret = true;
	}

	return ret;
}

bool CDateTrans::_CheckGL(string& dateStr,const string& str,const int year)
{
	int GLYear = year;
	char buf[MAX_SIZE] = {0};
	int month=0,day=0;
	map<string,string>::iterator it = _glmap.find(str);
	if (it != _glmap.end())
	{
		sscanf_s((*it).second.c_str(),"%d-%d",&month,&day);

		if (month < _nowtime.tm_mon+1 || (month == _nowtime.tm_mon+1 && day < _nowtime.tm_mday))
		{
			GLYear++;
		}
		sprintf_s(buf,"%d-%s",GLYear,(*it).second);
		dateStr = buf;
		return true;
	}
	return false;
}

bool CDateTrans::_CheckNL(string& dateStr,const string& str,const int year)
{
	char buf[MAX_SIZE] = {0};
	map<string,string>::iterator it = _nlmap.find(str);
	if (it != _nlmap.end())
	{
		sprintf_s(buf,"%d %s",year,(*it).second);
		dateStr = buf;
		return true;
	}
	return false;
}

bool CDateTrans::_CheckJQ(string& dateStr,const string& str,const int year)
{
	int i=0,ret=0;
	short sYear=year;
	short iIndex=0,sLYear=0;
	unsigned short wMonth=0,wLMonth=0,wDay=0,wLDay=0;
	BOOL bLeapMonth=FALSE;
	unsigned short JQ_date[2]={0};
	map<string,int>::iterator it = _jqmap.find(str);
	if (it != _jqmap.end())
	{
		iIndex = (*it).second;
	}
	if (iIndex==1)
	{
		iIndex+=24;
	}
	wMonth=(iIndex)/2;//ת�����·�

	ret=GetJieQi(sYear,wMonth,JQ_date);//ȡָ���·ݽ���������������
	if (ret==0)
	{
		return false;
	}
	if (iIndex%2==0)
	{
		wDay=(int)JQ_date[0];//��һ������
	}else
	{
		wDay=(int)JQ_date[1];//�ڶ�������
	}

	if (Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&wLMonth,&wLDay,&bLeapMonth)==0)//ת��ũ��
	{
		return false;
	}else
	{
		if (wMonth < _nowtime.tm_mon+1 || (wMonth == _nowtime.tm_mon+1 && wDay < _nowtime.tm_mday))
		{
			sYear++;
			ret=GetJieQi(sYear,wMonth,JQ_date);//ȡָ���·ݽ���������������
			if (ret==0)
			{
				return false;
			}
			if (iIndex%2==0)
			{
				wDay=(int)JQ_date[0];//��һ������
			}else
			{
				wDay=(int)JQ_date[1];//�ڶ�������
			}
			if (Gongli2Nongli(sYear,wMonth,wDay,&sLYear,&wLMonth,&wLDay,&bLeapMonth)==0)//ת��ũ��
			{
				return false;
			}
		}
		char buf[MAX_SIZE] = {0};
		sprintf_s(buf,"%d-%d-%d",sYear,wMonth,wDay);
		dateStr = buf;
		return true;
	}
}

bool CDateTrans::_NL2GL(string& dateStr,const string& str)
{
	unsigned short wMonth=0,wDay=0,iLMonth=0,iLDay=0,iDayofweek=0;
	short sYear=0,sLYear=0,bLLeapMonth=0;
	int ret=0;
	sscanf_s(str.c_str(),"%d %d %d",&sLYear,&iLMonth,&iLDay);
	do
	{
		ret=Nongli2Gongli(sLYear,iLMonth,iLDay,bLLeapMonth,&sYear,&wMonth,&wDay);
		if (ret==0)
		{
			bLLeapMonth = 1;
			ret=Nongli2Gongli(sLYear,iLMonth,iLDay,bLLeapMonth,&sYear,&wMonth,&wDay);
		}
		if (ret==0)
		{
			return false;
		}
	} while (sLYear++ == _nowtime.tm_year+1900 && (wMonth < _nowtime.tm_mon+1 ||(wMonth == _nowtime.tm_mon+1 && wDay < _nowtime.tm_mday)));


	char buf[MAX_SIZE] = {0};
	sprintf_s(buf,"%d-%02d-%02d",--sLYear,wMonth,wDay);
	dateStr = buf;
	return true;
}

void CDateTrans::_TranDate(string& dstDate,const string& srcDate)
{
	string tmp = srcDate;
	char chYear[32]={0},chMonth[16]={0},chDay[16]={0};
	string strYear="",strMonth = "",strDay = "";
	int year=0,month=0,day=0;
	int pos1 = -1,pos2 = -1,pos3 = -1;
	pos1 = tmp.find("��");
	string subStr="";
	if (pos1 != string::npos)
	{
		subStr = tmp.substr(0,pos1).c_str();
		strncpy(chYear,subStr.c_str(),subStr.length());
		tmp = tmp.substr(pos1+2,tmp.length()).c_str();
	}
	pos2 = tmp.find("��");
	if (pos2 != string::npos)
	{
		subStr = tmp.substr(0,pos2).c_str();
		strncpy(chMonth,subStr.c_str(),subStr.length());
		tmp = tmp.substr(pos2+2,tmp.length()).c_str();
	}
	pos3 = tmp.find("��");
	pos3 = pos3 == string::npos ? tmp.find("��"):pos3;
	if (pos3 != string::npos)
	{
		subStr = tmp.substr(0,pos3).c_str();
		strncpy(chDay,subStr.c_str(),subStr.length());
	}
	else
	{
		strncpy(chDay,tmp.c_str(),tmp.length());
	}

	//����ת��
	TranToNumber(strYear,chYear);
	TranToNumber(strMonth,chMonth);
	TranToNumber(strDay,chDay);
	year = atoi(strYear.c_str());
	month = atoi(strMonth.c_str());
	day = atoi(strDay.c_str());
	//sscanf(strYear.c_str(),"%d",&year);
	//sscanf(strMonth.c_str(),"%*[^0-9]%d%*[^0-9]",&month);
	//sscanf(strDay.c_str(),"%d",&day);

	_GetYear(year);
	_GetMonth(month);
	_GetDay(day);
	_FormDate(dstDate,year,month,day);
}

void CDateTrans::_FormDate(string& dstDate,int year,int month,int day)
{
	sprintf((char*)dstDate.c_str(),"%d-%02d-%02d",year,month,day);
	//sprintf_s((char*)dstDate.c_str(),dstDate.length(),"%4d-%2d-%2d",year,month,day);
}

void CDateTrans::_GetYear(int& year)
{
	year = year == 0 ? _nowtime.tm_year + 1900 :year;
}

void CDateTrans::_GetMonth(int& month)
{
	month = month == 0 ? _nowtime.tm_mon + 1:month;
}

void CDateTrans::_GetDay(int& day)
{
	day = day == 0 ? _nowtime.tm_mday :day;
}

bool CDateTrans::_CheckDateEnd(int& year,int& month,int& day)
{
	int months[]={31,0,31,30,31,30,31,31,30,31,30,31};
	if(year <= 0 || month < 1|| month > 12) 
		return 0;   
  
	if(year % 4 ==0 && year % 100 !=0 || year % 400 ==0)  
		months[1]=29;   
	else   
		months[1]=28;

	if (day <= 0)
	{
		// ���������
		if (month == 1)
		{
			month = 12;
			year--;
			day += months[month - 1];
			return true;
		}
		else if(month >1 && month <=12)
		{
			day += months[month - 1 - 1];
			month--;
			return true;
		}
		else
		{
			return false;
		}
	}

	int difDay = day - months[month-1];
	int difMonth = month - 12;
	if (difDay > 0)
	{
		day = difDay;
		month++;
		difMonth = month - 12;
		if (difMonth > 0)
		{
			month = difMonth;
			year++;
		}
		return true;
	}else if(difMonth > 0)
	{
		month = difMonth;
		year++;
		return true;
	}

	return false;	
}

void CDateTrans::DateSwitch(string& dstDate,const string& srcDate)
{
	//if (srcDate == "" || srcDate.empty())
	//{
	//	dstDate = "";
	//	return;
	//}
	string date = srcDate;
	_GetNowTime(_nowtime);
	int weekend = 0;
	int difday=0;
	//�Ƿ�������ܣ������ڣ�����ݵ�
	if (_CheckNextWeek(date.c_str()))
	{
		char wdate[8]={0};
		sscanf(date.c_str(),"��%s",wdate);
		weekend = 7;
		int weekday = _weekmap[wdate] - _nowtime.tm_wday;
		if (_weekmap[wdate] == 0)
		{
			difday = 2*weekend + weekday;
		}
		else
		{
			difday = weekend + weekday;
		}
	
		_GetNewFormTime((char*)dstDate.c_str(),difday);
	}
	else if(_CheckCurrentWeek(date.c_str()))
	{
		weekend = 7;
		int weekday = _weekmap[date] - _nowtime.tm_wday;
		difday = weekday < 0 ? weekend + weekday : weekday;

		_GetNewFormTime((char*)dstDate.c_str(),difday);
	}
	else if(_CheckNextDay(date.c_str(),difday))//�Ƿ�������죬����֮���
	{
		_GetNewFormTime((char*)dstDate.c_str(),difday);
	}
	else if (_CheckHoliday(dstDate,srcDate))
	{

	}
	else
	{
		_TranDate(dstDate,srcDate);
	}
}

BOOL IsLeapYear(short sYear)
{
	if (sYear<1600||sYear>=6400)//ѹ���㷨�涨�˵�������䣨��ȡ��ֻ�ܵ�������������ݣ�Lunar.dll֧��-6000��20000������20000��֮�����ݣ�
	{
		return E_FAIL;
	}
	if (sYear%4==0&&sYear%100!=0||sYear%400==0)//�ж����������
	{
		return TRUE;
	}else
	{
		return FALSE;
	}
}

BOOL GetDayOrdinal(short sYear, unsigned short wMonth, unsigned short wDay,int *nDays)
{
	//�������������Ԫ��������
	int ret=0;
	if (DateCheck(sYear,wMonth,wDay)==0)//����������ڽ��м��
	{
		return 0;
	}
	ret=IsLeapYear(sYear);//�ж��Ƿ�Ϊ����
	if (ret==-1)
	{
		return 0;
	}
	if (ret==1)
	{
		*nDays=DayOrdinalLeap[wMonth-1]+wDay-1;//Ԫ��Ϊ����0����˼�1
	}else
	{
		*nDays=DayOrdinal[wMonth-1]+wDay-1;
	}
	return 1;
}

BOOL GetDateFromOrdinal(short sYear,short sOrdinal,unsigned short* wMonth,unsigned short* wDay)
{
	//������������������
	int ret=0,i=0;
	if (sOrdinal<0)
	{
		return FALSE;
	}
	ret=IsLeapYear(sYear);
	if (ret==1)
	{
		if (sOrdinal>=366)//�����˸����������
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
		//����ϣ������;
		*wMonth=0;
		for (i=0;i<12;i++)
		{
			if (ret==1)
			{
				if (sOrdinal>=DayOrdinalLeap[i]&&sOrdinal<DayOrdinalLeap[i+1])//�ҳ��·�
				{
					*wMonth=i+1;
					*wDay=sOrdinal-DayOrdinalLeap[i]+1;//��������ա�
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
	return (short)((uData>>17)&0x3F);//ȡ��ũ���������������
}

unsigned short LunarGetDaysofMonth(short sLunarYear,unsigned short wLunarMonth,BOOL bLeapMonth)
{
	int i=0;//ѭ������
	unsigned int DX_data=0;//�����С�����
	unsigned int uData=0;
	int Acc_LeapMonth=0;
	if (sLunarYear==START_YEAR-1)//ũ��������ʼ��ݵ�ǰһ��
	{
		if (cPreLeapIndex==-1)//������
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
	DX_data=(unsigned short)(uData&0x1FFF);//�����С�����
	Acc_LeapMonth=LunarGetLeapMonth(sLunarYear);//��ȡ��ʵ�����·�
	if (bLeapMonth)//ָ����ѯ�ĵ�ǰ��������
	{
		if (Acc_LeapMonth!=wLunarMonth)
		{
			return 0;//�����ڵ�����
		}
		for (i=0;i<wLunarMonth;i++)
		{
			DX_data>>=1;//����һλ������ĩβ��ʼ�Ҹ������·����ڵ�λ
		}
	}else
	{
		if (Acc_LeapMonth>0)//��������
		{
			if (wLunarMonth<=Acc_LeapMonth)//�·�������֮ǰ��������Ҫ����һλ
			{
				for (i=0;i<wLunarMonth-1;i++)
				{
					DX_data>>=1;
				}
			}else
			{
				for (i=0;i<wLunarMonth;i++)//�·�������֮��
				{
					DX_data>>=1;
				}
			}
		}else
		{
			for (i=0;i<wLunarMonth-1;i++)//������
			{
				DX_data>>=1;
			}
		}
	}
	if (DX_data&0x1)
	{
		return 30;//����
	}else
	{
		return 29;//С��
	}
}

BOOL LunarExpandDX(short sLunarYear,int iDayOfMonth[15])
{
	int i=0,pos=0,iLeapMonth=0;//ѭ������������д��λ�ã�����
	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR)
	{
		return FALSE;
	}
	for (i=0;i<15;i++)
	{
		iDayOfMonth[i]=0;//����������
	}
	if (sLunarYear==START_YEAR)
	{
		if (cPreLeapIndex==-1)//������ʼ���֮ǰһ������
		{
			iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];//ũ����һ��ʮһ��������
			pos++;
		}else
		{
			if (cPreLeapIndex==1)//��ʮ��
			{
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}else
			{
				//��ʮһ�»���ʮ����
				iDayOfMonth[pos]=cPreMonth[2]-cPreMonth[1];
				pos++;
				iDayOfMonth[pos]=cPreMonth[3]-cPreMonth[2];
				pos++;
			}
		}
		iDayOfMonth[pos]=LunarGetNewYearOrdinal(sLunarYear)-cPreMonth[2];//����ʮ����
		pos++;
	}else
	{
		iLeapMonth=LunarGetLeapMonth(sLunarYear-1);//ȡ��ǰһũ������������
		if (iLeapMonth<11)//һ����ʮ�µ�����
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//ȡ��һ��ʮһ������
			pos++;
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
			pos++;
		}else
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,0);//ȡ��һ��ʮһ�µ�����
			pos++;
			if (iLeapMonth==11)//��ʮһ��
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,11,1);//ȡ��һ����ʮһ�µ�����
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
				pos++;
			}else if (iLeapMonth==12)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,0);//ȡ��һ��ʮ��������
				pos++;
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear-1,12,1);//ȡ��һ����ʮ��������
				pos++;
			}
		}
	}
	iLeapMonth=LunarGetLeapMonth(sLunarYear);//��ȡ��ǰũ������������
	if (iLeapMonth==0)//������
	{
		for (i=0;i<12;i++)
		{
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//ȡÿ��ũ��������
			pos++;
		}
	}else
	{
		for (i=0;i<12;i++)
		{
			if (i==iLeapMonth)
			{
				iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i,1);//ȡ���µ�����
				pos++;
			}
			iDayOfMonth[pos]=LunarGetDaysofMonth(sLunarYear,i+1,0);//ȡ�����µ�����
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
	int DaysNum=0,LunarNewYear=0,i=0,remain_days=0;//����������ũ������Ĺ�������������ѭ��������ʣ������
	int DaysOfLunarMonth[15]={0};//���ũ���·�����
	int iLeapMonthPre=0,iLeapMonth=0;//ũ����һ�����£���������
	int ret=GetDayOrdinal(sYear,wMonth,wDay,&DaysNum);
	if (ret==0)
	{
		return 0;//���ڲ���ȷ
	}
	*sLunarYear=sYear;
	LunarNewYear=LunarGetNewYearOrdinal(*sLunarYear);
	LunarExpandDX(*sLunarYear,DaysOfLunarMonth);//��ȡ�·��������������һ��ʮһ�¿�ʼ�����꣨��ʮ���£���������
	iLeapMonthPre=LunarGetLeapMonth(*sLunarYear-1);
	if (iLeapMonthPre==0)
	{
		iLeapMonth=LunarGetLeapMonth(*sLunarYear);//��һ��û�����£����ѯ��������
	}
	*bLeapMonth=FALSE;
	remain_days=DaysNum-LunarNewYear;//����ũ����������
	if (iLeapMonthPre>10)
	{
		i=3;//���������ڡ�DaysOfLunarMonth���е���������һ��ʮһ�»�ʮ����������
	}else
	{
		i=2;//��һ��ʮһ�º�ʮ����������ʱ���������µ�����
	}
	if (LunarNewYear>DaysNum)//����ũ������
	{
		*sLunarYear-=1;//ũ�����1
		while(remain_days<0)
		{
			i--;//��һ���ȼ�ȥ����Ϊ��ǰi�����£���1��ʾ��һ��ʮ���£�����ʮ���£�
			remain_days+=DaysOfLunarMonth[i];//������һ��ʮ���¡�ʮһ�µ��������������£�ֱ����������0
		}
		if (iLeapMonthPre>10)//�����һ��ʮһ�»�ʮ���´�������
		{
			if (iLeapMonthPre==11)//��ʮһ��
			{
				if (i==0)//ʮһ�£���������֮ǰ��
				{
					*wLunarMonth=11+i;//ת�����·�
				}else
				{
					*wLunarMonth=10+i;
					if (*wLunarMonth==iLeapMonthPre)
					{
						*bLeapMonth=TRUE;
					}
				}
			}else if (iLeapMonthPre==12)//��ʮ����
			{
				if (i<2)//������֮ǰ
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
			remain_days-=DaysOfLunarMonth[i];//Ѱ��ũ����
			i++;//�����¸���
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
	*wLunarDay+=1;//����ת��������
	return TRUE;
}

BOOL Nongli2Gongli(short sLunarYear,unsigned short wLunarMonth,unsigned short wLunarDay,BOOL bLeapMonth,short* sYear,unsigned short* wMonth,unsigned short* wDay)
{
	int DaysOfLunarMonth[15]={0};//���ũ���·�����
	int iLeapMonthPre=0,iLeapMonth=0;//ũ��������
	int LunarNewYear=0,i=0,remain_days=0;//����������ũ������Ĺ�������������ѭ��������ʣ������
	int iDaysofYear=0;
	if (sLunarYear<START_YEAR||sLunarYear>=END_YEAR||wLunarMonth<1||wLunarMonth>12||wLunarDay<1||wLunarDay>30)
	{
		return 0;//�ꡢ�¡��ռ��
	}
	if (bLeapMonth)
	{
		if (LunarGetLeapMonth(sLunarYear)!=wLunarMonth)
		{
			return FALSE;//���¼��
		}
	}
	if (wLunarDay>LunarGetDaysofMonth(sLunarYear,wLunarMonth,bLeapMonth))
	{
		return FALSE;//��С�¼��
	}
	LunarExpandDX(sLunarYear,DaysOfLunarMonth);//��С�±�ũ��ÿ��������
	LunarNewYear=LunarGetNewYearOrdinal(sLunarYear);//�ҵ����³�һr������������
	iLeapMonth=LunarGetLeapMonth(sLunarYear);//�ҳ�ũ���������
	remain_days+=LunarNewYear;//�������³�һ������
	if (iLeapMonthPre>10)
	{
		i=3;//���������ڡ�DaysOfLunarMonth���е���������һ��ʮһ�»�ʮ����������
	}else
	{
		i=2;//��һ��ʮһ�º�ʮ����������ʱ���������µ�����
	}
	if (iLeapMonth==0)
	{
		if (iLeapMonthPre>10)
		{
			for (;i<wLunarMonth+2;i++)
			{
				remain_days+=DaysOfLunarMonth[i];//���������ۼ�
			}
		}else
		{
			for (;i<wLunarMonth+1;i++)
			{
				remain_days+=DaysOfLunarMonth[i];//���������ۼ�
			}
		}
	}else
	{
		if (wLunarMonth<iLeapMonth||(bLeapMonth==FALSE&&wLunarMonth==iLeapMonth))//������֮ǰ
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
	remain_days+=wLunarDay-1;//��1����Ϊ����ת������
	GetDayOrdinal(sLunarYear,12,31,&iDaysofYear);//��ȡ������������
	iDaysofYear++;//������ת������
	*sYear=sLunarYear;
	if (remain_days>iDaysofYear)
	{
		remain_days-=iDaysofYear;
		*sYear+=1;//��һ��
	}
	GetDateFromOrdinal(*sYear,remain_days,wMonth,wDay);
	return TRUE;
}

BOOL GetJieQi(short sYear,unsigned short wMonth,unsigned short wJieQi[2])
{
	int index=0;//��Ӧÿ�������׸����������ֽڵ�����
	unsigned short wXiaoHanOrder=0;//С����������
	unsigned short wJQData=0;//��������
	unsigned short wCurJQData=0;//��ǰ����Ľ�������
	unsigned short wDays=0;//��ǰ�����������С��������
	int i=0;
	if (sYear<START_YEAR||sYear>=END_YEAR||wMonth>12||wMonth<1)
	{
		return FALSE;
	}
	index=(sYear-START_YEAR)*6;//��Ӧÿ�������׸����������ֽڵ�����
	wXiaoHanOrder=(unsigned short)(((cSolarTerms[index])>>6)+3);//����3��תΪС������������
	wJQData=cSolarTerms[index];
	wCurJQData=(wJQData>>4)&0x03;//��ǰ����Ľ�������һ��������������Ϣ
	if (wMonth==1)
	{
		wJieQi[0]=wXiaoHanOrder+1;//��1ת������
		wJieQi[1]=wCurJQData+14+wXiaoHanOrder+1;//�󺮣�С���������������Ͼ���С��������
		return TRUE;
	}
	wDays=wCurJQData+14;//����С������������ǰΪ�󺮾���С��������
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
	GetDateFromOrdinal(sYear,wDays+wXiaoHanOrder,&wMonth,&wJieQi[1]);//wMonth�еĵڶ�������
	GetDateFromOrdinal(sYear,wDays+wXiaoHanOrder-wCurJQData-14,&wMonth,&wJieQi[0]);//��һ������
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
	uDayOrd++;//һ���еĵڼ��죬��ΪGetDayOrdinal���õ��������������Ҫ��һ
	sYear--;
	DayofWeek=(sYear+sYear/4-sYear/100+sYear/400+uDayOrd)%7;//���ֻ�������ڵ�ͨ�ù�ʽ
	return DayofWeek;
}

unsigned short GetDaysOfMonth(short sYear,unsigned short wMonth)
{
	int days1=0,days2=0;
	int ret=0;
	if (wMonth==12)
	{
		return 31;//����Ϊ�˼�㣬�ж�12�¾�ֱ�ӷ���
	}
	ret=GetDayOrdinal(sYear,wMonth,1,&days1);//����1�������ڵ�����
	if (ret==0)
	{
		return ret; 
	}
	wMonth++;
	ret=GetDayOrdinal(sYear,wMonth,1,&days2);//�¸���1�յ���������
	if (ret==0)
	{
		return ret; 
	}
	ret=days2-days1;//�¸���1�յ�����������1�յ�����
	return ret;
}

BOOL GetExtremeSeason(short sYear,short* sYijiu,unsigned short* wChuFu,unsigned short* wMoFu)
{
	unsigned short wjq[2]={0};
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
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
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
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
	//Ҫ��ʾһ���µ������������¼���Ҫ�㣺
	//1.����1�յ�����
	//2.���µ�������
	//3.����1�ն�Ӧ��ũ���Լ�ũ���´�С����ʱ������Ҫ֪���¸����������¸��µĴ�С
	int iDayofweek_1st=0;//����1������
	short sNYear=0;
	unsigned short wNMonth=0,wNDay=0;//ũ���ꡢ�¡���
	BOOL bNLeapMonth=FALSE;//���±�־
	int iDaysofmonth=0;//������������
	int iNDaysofmonth=0;//ũ����������
	int iPos=0,iGDayIdx=1,iNDayIdx=0,iNindex=1;//���λ�á������գ�ũ���գ�ũ�����������ͬ��iDaysofmonth��
	int iFillFlag=0;//����־��0Ϊ����������䣬1Ϊũ��������䣬2Ϊ������䣬3Ϊũ�����
	iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��1�յ�����
	if (iDayofweek_1st==-1)
	{
		return FALSE;//������������
	}
	iDaysofmonth=GetDaysOfMonth(sYear,wMonth);//�õ�����������
	Gongli2Nongli(sYear,wMonth,1,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//�õ�����1�յ�ũ��
	iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//�õ�ũ����������
	iNDayIdx=wNDay;//ȡ��ũ����
	if (iNDaysofmonth==0)
	{
		return FALSE;
	}
	printf_s("\t\t%d��%d�� ũ�� ",sYear,wMonth);
	if (bNLeapMonth==1)
	{
		printf_s("��");
	}
	if (iNDaysofmonth==29)
	{
		printf_s("%s��С��\n\n",Yueming[wNMonth-1]);
	}else if (iNDaysofmonth==30)
	{
		printf_s("%s����\n\n",Yueming[wNMonth-1]);
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
				while(iPos<iDayofweek_1st)//ֱ�����������
				{
					printf_s("\t");
					iPos++;//λ������
				}
			}
			if (G_HolidayShow(sYear,wMonth,iGDayIdx)==0)
			{
				printf_s("  %2d\t",iGDayIdx);//���ũ��
			}
			iPos++;
			iGDayIdx++;
			if (iGDayIdx>iDaysofmonth)
			{
				printf_s("\n");
				iPos=0;//λ�����»ص���ʼ
				iFillFlag=3;
			}else
			{
				if (iPos==7)//���Ҫ������
				{
					printf_s("\n");
					iPos=0;//λ�����»ص���ʼ
					if (iFillFlag==0)
					{
						iFillFlag=1;//�л���ũ���������
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
				while(iPos<iDayofweek_1st)//ֱ�����������
				{
					printf_s("\t");
					iPos++;//λ������
				}
			}
			
			if (iNDayIdx<=iNDaysofmonth)
			{
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					if (iNDayIdx==1)
					{
						printf_s(" %s",Yueming[wNMonth-1]);//��������Ϊũ������
						if (iNDaysofmonth==30)
						{
							printf_s("��\t");
						}else
						{
							printf_s("С\t");
						}
					}else
					{
						printf_s(" %s\t",Riming[iNDayIdx-1]);//û�н��ա��������������ʱ�����ũ������
					}
				}
			}else
			{
				Gongli2Nongli(sYear,wMonth,iNindex,&sNYear,&wNMonth,&wNDay,&bNLeapMonth);//���ũ����һ����
				iNDaysofmonth=LunarGetDaysofMonth(sNYear,wNMonth,bNLeapMonth);//���µõ�ũ����������
				iNDayIdx=wNDay;
				if (L_HolidayShow(sNYear,wNMonth,iNDayIdx,bNLeapMonth)==0)
				{
					//û�н��ա��������������ʱ�����ũ������
					if (bNLeapMonth==1)
					{
						printf_s("��");
					}
					printf_s("%s",Yueming[wNMonth-1]);
					if (iNDaysofmonth==29)
					{
						printf_s("С");
					}else if (iNDaysofmonth==30)
					{
						printf_s("��");
					}
					if (bNLeapMonth==0)
					{
						printf_s("\t");
					}
				}
			}
			iPos++;
			iNDayIdx++;//ũ��������
			iNindex++;//ũ���������������
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
	unsigned short wJQ_date[2]={0};//�������
	int iDayOrdial=0;//���ڵ���������
	int ET_index=sYear-START_YEAR;//���š�÷�꼰�������������
	int iDayofweek_1st=0;//��������
	int iDongzhi=0;//����
	unsigned short wrumei=0,wchumei=0,wchufu=0,wmofu=0;
	short sshujiu=0;
	int i=0;
	if (GetJieQi(sYear,wMonth,wJQ_date)==1)
	{
		if (wJQ_date[0]==wDay)
		{
			printf_s(" %s\t",Jieqi[((wMonth<<1)-1)%24]);//���µ�һ������
			return 1;
		}else if (wJQ_date[1]==wDay)
		{
			printf_s(" %s\t",Jieqi[(wMonth<<1)%24]);//���µڶ�������
			return 1;
		}
	}
	GetDayOrdinal(sYear,12,wJQ_date[1],&iDongzhi);//ת������������
	if (GetDayOrdinal(sYear,wMonth,wDay,&iDayOrdial))
	{
		/*if (iDayOrdial==wExtermSeason[ET_index+5])
		{
			printf_s("[%s]\t",Shujiu[0]);//һ�ţ�������������Ҫ�ж��ˣ����涬���Ѿ���������ˣ�
			return 1;
		}else */
		GetExtremeSeason(sYear,&sshujiu,&wchufu,&wmofu);
		GetMeiYu(sYear,&wrumei,&wchumei);
		if (iDayOrdial==iDongzhi+9)
		{
			printf_s("[%s]\t",Shujiu[1]);//����
			return 2;
		}
		if (iDayOrdial>=(sshujiu+9)&&iDayOrdial<sshujiu+81)
		{
			for (i=0;i<8;i++)
			{
				if (iDayOrdial==sshujiu+(i+1)*9)
				{
					printf_s("[%s]\t",Shujiu[i+1]);//�������ž�
					return 1;
				}
			}
		}else if (iDayOrdial==wrumei)
		{
			printf_s("[%s]\t",Meiyu[0]);//��÷
			return 1;
		}else if (iDayOrdial==wchumei)
		{
			printf_s("[%s]\t",Meiyu[1]);//��÷
			return 1;
		}else if (iDayOrdial==wchufu)
		{
			printf_s("[%s]\t",Sanfu[0]);//����
			return 1;
		}else if (iDayOrdial==wchufu+10)
		{
			printf_s("[%s]\t",Sanfu[1]);//�з�
			return 1;
		}else if (iDayOrdial==wmofu)
		{	printf_s("[%s]\t",Sanfu[2]);//ĩ��
			return 1;
		}
	}
	if (wMonth==1)
	{
		if (wDay==1)
		{
			printf_s(" Ԫ��\t");
			return 1;
		}
	}else if (wMonth==2)
	{
		if (wDay==14)
		{
			printf_s("���˽�\t");
			return 1;
		}
	}else if (wMonth==3)
	{
		switch (wDay)
		{
		case 5:
			if (sYear>=1963)
			{
				printf_s("ѧ�׷���");
				return 1;
			}
			break;
		case 8:
			if (sYear>=1900)
			{
				printf_s("��Ů��\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1928)
			{
				printf_s("ֲ����\t");
				return 1;
			}
			break;
		case 15:
			if (sYear>=1983)
			{
				printf_s("��Ȩ��\t");
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
			printf_s("���˽�\t");
			return 1;
		}
	}else if (wMonth==5)
	{
		if (sYear>=1872)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==2)//5�µڶ�������ĸ�׽�
			{
				printf_s("ĸ�׽�\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>=1890)
			{
				printf_s("�Ͷ���\t");
				return 1;
			}
			break;
		case 4:
			if (sYear>=1919)
			{
				printf_s("�����\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1912)
			{
				printf_s("��ʿ��\t");
				return 1;
			}
			break;
		case 31:
			if (sYear>=1989)
			{
				printf_s("������\t");
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
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==0&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==0?7:0))/7)==3)//6�µ��������ո��׽�
			{
				printf_s("���׽�\t");
				return 1;
			}
		}
		switch (wDay)
		{
		case 1:
			if (sYear>1949)
			{
				printf_s("��ͯ��\t");
				return 1;
			}
			break;
		case 5:
			if (sYear>=1972)
			{
				printf_s("������\t");
				return 1;
			}
			break;
		case 26:
			if (sYear>=1987)
			{
				printf_s("������\t");
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
				printf_s("�й�����");
				return 1;
			}
			break;
		case 7:
			if (sYear>=1937)
			{
				printf_s("��ս����");
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
				printf_s("������\t");
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
				printf_s("��սʤ��");
				return 1;
			}
			break;
		case 10:
			if (sYear>=1985)
			{
				printf_s("��ʦ��\t");
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
				printf_s(" ����\t");
				return 1;
			}
		}
	}else if (wMonth==11)
	{
		if (sYear>=1941)
		{
			iDayofweek_1st=GetDayOfWeek(sYear,wMonth,1);//ȡ��������
			if ((wDay+iDayofweek_1st-1)%7==4&&((wDay+iDayofweek_1st-1+(iDayofweek_1st==4?7:0))/7)==4)//11�µ��ĸ����ĸж���
			{
				printf_s("�ж���\t");
				return 1;
			}
		}
		if (wDay==1)
		{
			printf_s("��ʥ��\t");
			return 1;
		}
	}else if (wMonth==12)
	{
		switch (wDay)
		{
		case 10:
			if (sYear>=1948)
			{
				printf_s("��Ȩ��\t");
				return 1;
			}
			break;
		case 12:
			if (sYear>=1936)
			{
				printf_s("�����±�");
				return 1;
			}
			break;
		case 24:
			printf_s("ƽ��ҹ\t");
			return 1;
		case 25:
			printf_s("ʥ����\t");
			return 1;
		default:
			break;
		}
	}
	return 0;
}

BOOL L_HolidayShow(int sLYear,int iLMonth,int iLDay,int iLeapMonth)
{
	int LeapMonth=LunarGetLeapMonth(sLYear);//ȡ����ũ������
	int DayofLM_12=0;//ũ��ʮ���µ�������
	if (iLeapMonth==0)
	{
		if (iLMonth==1)
		{
			switch (iLDay)
			{
			case 1:
				printf_s(" ����\t");
				return TRUE;
			case 15:
				printf_s("Ԫ����\t");
				return TRUE;
			default:
				break;
			}
		}else if (iLMonth==2)
		{
			if (iLDay==2)
			{
				printf_s("������\t");
				return TRUE;
			}
		}else if (iLMonth==5)
		{
			if (iLDay==5)
			{
				printf_s("�����\t");
				return TRUE;
			}
		}else if (iLMonth==7)
		{
			if (iLDay==7)
			{
				printf_s(" ��Ϧ\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf_s("��Ԫ��\t");
				return TRUE;
			}
		}else if (iLMonth==8)
		{
			if (iLDay==15)
			{
				printf_s("�����\t");
				return TRUE;
			}
		}else if (iLMonth==9)
		{
			if (iLDay==9)
			{
				printf_s("������\t");
				return TRUE;
			}
		}else if (iLMonth==10)
		{
			if (iLDay==1)
			{
				printf_s("�����\t");
				return TRUE;
			}else if (iLDay==15)
			{
				printf_s("��Ԫ��\t");
				return TRUE;
			}
		}else if (iLMonth==12)
		{
			if (LeapMonth!=12)
			{
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,0);//����ʮ����
				if (iLDay==8)
				{
					printf_s("���˽�\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf_s(" С��\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//ũ��ʮ���µ����һ���ǳ�Ϧ
				{
					printf_s(" ��Ϧ\t");
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
				DayofLM_12=LunarGetDaysofMonth(sLYear,12,1);//��ʮ����
				if (iLDay==8)
				{
					printf_s("���˽�\t");
					return TRUE;
				}else if (iLDay==23)
				{
					printf_s(" С��\t");
					return TRUE;
				}else if (iLDay==DayofLM_12)//ũ��ʮ���µ����һ���ǳ�Ϧ
				{
					printf_s(" ��Ϧ\t");
					return TRUE;
				}
			}
		}
	}
	return FALSE;//û�н��յ�
}