// Modif.cpp : 定义控制台应用程序的入口点。
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
	const char* ptr = "project=test;file=json;version=3.0;gps=116.420436,39.951663;type=tel;tel_number=幺三七一六一五五七二九;limitline_city=北京;limitline_date=;radio_rate=一千零五十八点六赫兹;navigate_place=东京一号八单元五零七;weather_date=大前天北京;weather_value=天气";
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
	//配置文件测试
	//m_config->Init("switch");
	//if (m_config->CheckSwitch("ngi"))
	//{
	//	printf("1");
	//}
	//m_datetrans->DateTran(psr,str);
	////////////////////数字转换测试//////////
	//string dst= "";
	//string src[6] = {"明天一千零二十五","一千零二十五点七三","一零二五点七三",
	//"二百点六二","三五七八点九四","一万八千"};

	//for (int i= 0;i<6;i++)
	//{
	//	m_transnum->TranToNumber(dst,src[i]);
	//	printf(dst.c_str());
	//	printf("\n");
	//}
	//////////////日期转换测试//////////////////////
	//string date1 = "二零一八年二月十号";
	//string date2 = "下周日";
	//string date3 = "后天";
	//m_datetrans->DateSwitch(psr,date3);
	//printf(psr.c_str());
	////流程测试
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;weather_type=weather;weather_city=北京;weather_date=二零一八年二月十号;weather_value=天气";

	//城市日期混合的测试
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;weather_type=weather;weather_city=;weather_date=北京两千年八月十日;weather_value=天气";
	//string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=radio;radio_type=weather;radio_rate=一千零五十八点六赫兹;weather_date=北京两千年八月十日;weather_value=天气";
	string str = "project=shngi;file=;version=3.0;gps=116.420436,39.951663;type=weather;radio_rate=一千零五十八点六赫兹;navigate_place=东京一号八单元五零七;weather_date=元旦;weather_value=天气";

	string result = m_v->Modif(str);	
	time_t et = GetTickCount();
	printf("%d\n",et - st);
	printf(result.c_str());
	delete m_v;
	m_v = nullptr;

	return 0;
}

