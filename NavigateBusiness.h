#pragma once
#include "Business.h"

#define  PLACENAME "navigate_place"
#define  AROUNDNAME "navigate_around"
#define  VIANAME "navigate_via"


class CNavigateBusiness:public CBusiness
{
public:
	CNavigateBusiness(void);
	CNavigateBusiness(const string& navfile);
	~CNavigateBusiness(void);	
private:
	CNumTrans _numtrans;
	string _placename;
	string _aroundname;
	string _vianame;
	string _navfile;
	vector<string> _address;
	void _SplitSentence(vector<string>& VecSentence,const string& POI);
	string _POISwitch(const string& POI);
	void _GetAddressVec();
public:
	string excute();
};

