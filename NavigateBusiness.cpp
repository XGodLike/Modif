#include "stdafx.h"
#include "NavigateBusiness.h"


CNavigateBusiness::CNavigateBusiness(void)
{
#ifndef LOAD_RESOURCE
	char szFilePath[MAX_SIZE];
	GetCurrentDirectory(MAX_SIZE,szFilePath);
	strcat_s(szFilePath,"\\model\\Modif_Navigate.dct");	

	_navfile = szFilePath;	
#endif
	_GetAddressVec();
}

CNavigateBusiness::CNavigateBusiness(const string& navfile):_navfile(navfile)
{
	_GetAddressVec();
}

CNavigateBusiness::~CNavigateBusiness(void)
{
}
#ifdef LOAD_RESOURCE
void CNavigateBusiness::_GetAddressVec()
{	
	HRSRC hsrc = 0;
	int nSize = 0;
	HGLOBAL hglb = 0;
	void * sBuf = 0;

	HINSTANCE hInst = GetModuleHandle(MODIF_LOCAL);
	hsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_DCT3), "DCT"); //查找资源
	nSize = SizeofResource(hInst,hsrc); //计算资源大小

	//获取资源首地址
	hglb = LoadResource(hInst, hsrc);
	sBuf = LockResource(hglb);
	char* buf = new CHAR[nSize];
	memset(buf,NULL,sizeof(char)*nSize);
	memcpy(buf, sBuf, nSize);
	Split(_address,buf,"\r\n");
	//释放资源
	delete[] buf;
	FreeResource(hglb);
}
#else
void CNavigateBusiness::_GetAddressVec()
{	
	FILE* pf;
	fopen_s(&pf,_navfile.c_str(),"rb");
	if(pf == NULL)
	{
		return ;
	}

	char buf[MAX_SIZE]= {0};
	while (fscanf(pf,"%s",buf) != EOF)
	{
		_address.push_back(buf) ;
	}
	fclose(pf);
}
#endif

void CNavigateBusiness::_SplitSentence(vector<string>& VecSentence,const string& POI)
{
	string poi = POI;

}

string CNavigateBusiness::_POISwitch(const string& POI)
{
	string poi = POI;
	string result = POI;
	vector<string>::iterator it = _address.begin();
	for (;it!=_address.end();it++)
	{
		int pos = poi.find((*it));
		if (pos != string::npos)
		{
			_numtrans.TranToNumber(result,poi);
			return result;
		}
	}
	return result;
}

string CNavigateBusiness::excute()
{
	_placename = GetInfo(PLACENAME);
	_aroundname = GetInfo(AROUNDNAME);
	_vianame = GetInfo(VIANAME);

	string tran_place = _POISwitch(_placename);
	string tran_around = _POISwitch(_aroundname);
	string tran_via = _POISwitch(_vianame);

 	_infomap[PLACENAME] = tran_place.c_str();
	_infomap[AROUNDNAME] = tran_around.c_str();
	_infomap[VIANAME] = tran_via.c_str();

	return GetResult();
}
