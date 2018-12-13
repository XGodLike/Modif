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

//===============================================================================
/*
void ShowMenu(void);//��ʾ�˵�
void GL2NL(void);//����תũ��
void NL2GL(void);//ũ��ת����
void RL(void);//��ʾһ���µ�����
void JQ(void);//������ѯ
*/
#endif //_HELPER_H_