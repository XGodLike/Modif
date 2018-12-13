// Modif.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Modif.h"
#include "define.h"
#include "VcyberBusiness.h"


const char*  execute(const char * src)
{
	void* result = malloc(MAX_SIZE*10);
	if (result == NULL)
	{
		return nullptr;
	}
	memset(result,NULL,MAX_SIZE*10);
	CVcyberBusiness m_v;
	string strDst = m_v.Modif(src);
	strncpy((char*)result,strDst.c_str(),strDst.length());
	return (const char*)result;
}

void release(const char * dst)
{
	free((void*)dst);
}

int _tmain2(int argc, _TCHAR* argv[])
{
	time_t st = GetTickCount();
	const char* ptr = "project=test;file=json;version=3.0;gps=116.420436,39.951663;type=tel;tel_number=������һ��һ�����߶���;limitline_city=����;limitline_date=;radio_rate=һǧ����ʮ�˵�������;navigate_place=����һ�Ű˵�Ԫ������;weather_date=��ǰ�챱��;weather_value=����";
	const char* buf = execute(ptr);
	printf(buf);
	release(buf);
	time_t et = GetTickCount();
	printf("%d\n",et - st);
	system("pause");
	return 0;
}

int _tmain1(int argc, _TCHAR* argv[])
{
	CVcyberBusiness* m_v = new CVcyberBusiness();
	time_t st = GetTickCount();
	string psr="";
	//�����ļ�����
	//m_config->Init("switch");
	//if (m_config->CheckSwitch("ngi"))
	//{
	//	printf("1");
	//}
	//m_datetrans->DateTran(psr,str);
	////////////////////����ת������//////////
	//string dst= "";
	//string src[6] = {"����һǧ���ʮ��","һǧ���ʮ�������","һ����������",
	//"���ٵ�����","�����߰˵����","һ���ǧ"};

	//for (int i= 0;i<6;i++)
	//{
	//	m_transnum->TranToNumber(dst,src[i]);
	//	printf(dst.c_str());
	//	printf("\n");
	//}
	//////////////����ת������//////////////////////
	//string date1 = "����һ�������ʮ��";
	//string date2 = "������";
	//string date3 = "����";
	//m_datetrans->DateSwitch(psr,date3);
	//printf(psr.c_str());
	////���̲���
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;weather_type=weather;weather_city=����;weather_date=����һ�������ʮ��;weather_value=����";

	//�������ڻ�ϵĲ���
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;weather_type=weather;weather_city=;weather_date=������ǧ�����ʮ��;weather_value=����";
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=radio;radio_type=weather;radio_rate=һǧ����ʮ�˵�������;weather_date=������ǧ�����ʮ��;weather_value=����";
	string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;radio_rate=һǧ����ʮ�˵�������;navigate_place=����һ�Ű˵�Ԫ������;weather_date=Ԫ��;weather_value=����";

	string result = m_v->Modif(str);	
	time_t et = GetTickCount();
	printf("%d\n",et - st);
	printf(result.c_str());
	delete m_v;
	m_v = nullptr;

	return 0;
}

