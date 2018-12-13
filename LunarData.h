//�� ��ũ�����ݡ�
//�� ����ʱ�䣺2016-02-15 08:47:53 ���꣨��� ���£��󣩳��� ����һ
//�� ��ȡ�������ܴ�СΪ��2206 �ֽڡ�
//�� ע�⣬���������Ѿ����У�Բ���֤��ȷ�������޸ģ����򽫵��´���

//E-mail: paradise300@163.com

#ifndef _LUNARDATA_H_
#define _LUNARDATA_H_

#define START_YEAR 1900	//����������ʼ��ݣ�������
#define END_YEAR 2100	//����������ֹ��ݣ����������꣩

//1899��ũ��ʮ�¼��Ժ��������������ӦcPreMonth�е���ţ���ǰΪ-1����ʾ1899��ũ��ʮ���Ժ������¡�
char const cPreLeapIndex=-1;

//1899��ũ��ʮ�¼��Ժ���·ݣ�ÿ�³�һ��1900���ڵ�������
//cPreMonth�зֱ��Ӧũ����ʮ�¡�ʮһ�¡�ʮ���¡����¡�
char const cPreMonth[4]={-59,-29,0,30};

//ũ���·���Ϣ��һ����3���ֽڱ�ʾ
//+-----------------------------------------------------------------------+
//| ��23λ |        ��22-17λ       |  ��16-13λ |       ��12-0λ         |
//|--------+------------------------+------------+------------------------|
//|  ����  | ũ�����³�һ���������� |    ����    | һ��λ��Ӧһ���·ݴ�С |
//+-----------------------------------------------------------------------+
//�·ݴ�С�������·�С���ڵ�λ���·ݴ���ڸ�λ�������������λ��
//��1900��Ϊ����3���ֽڵ�����չ���ɶ�����λ��
//  0       011110        1000                     1 0 1 1 0 1 1 0 1 0 0 1 0
//����  1��31�գ����ڣ�  �����   ������������ʮ���£�ʮһ�¡�������¡����¡����¡������µ�����
//ũ���·ݶ�Ӧ��λΪ0����ʾ�����Ϊ29�죨С�£���Ϊ1��ʾ��30�죨���£���
unsigned char const cMonthInfo[600]={
	0x3D,0x16,0xD2,0x62,0x07,0x52,0x4C,0x0E,0xA5,0x38,0xB6,0x4A,	//1900-1903
	0x5C,0x06,0x4B,0x44,0x0A,0x9B,0x30,0x95,0x56,0x56,0x05,0x6A,	//1904-1907
	0x40,0x0B,0x59,0x2A,0x57,0x52,0x50,0x07,0x52,0x3A,0xDB,0x25,	//1908-1911
	0x60,0x0B,0x25,0x48,0x0A,0x4B,0x32,0xB4,0xAB,0x58,0x02,0xAD,	//1912-1915
	0x42,0x05,0x6B,0x2C,0x4B,0x69,0x52,0x0D,0xA9,0x3E,0xFD,0x92,	//1916-1919
	0x64,0x0E,0x92,0x4C,0x0D,0x25,0x36,0xBA,0x4D,0x5C,0x0A,0x56,	//1920-1923
	0x46,0x02,0xB6,0x2E,0x95,0xB5,0x56,0x06,0xD4,0x40,0x0E,0xA9,	//1924-1927
	0x2C,0x5E,0x92,0x50,0x0E,0x92,0x3A,0xCD,0x26,0x5E,0x05,0x2B,	//1928-1931
	0x48,0x0A,0x57,0x32,0xB2,0xB6,0x58,0x0B,0x5A,0x44,0x06,0xD4,	//1932-1935
	0x2E,0x6E,0xC9,0x52,0x07,0x49,0x3C,0xF6,0x93,0x62,0x0A,0x93,	//1936-1939
	0x4C,0x05,0x2B,0x34,0xCA,0x5B,0x5A,0x0A,0xAD,0x46,0x05,0x6A,	//1940-1943
	0x30,0x9B,0x55,0x56,0x0B,0xA4,0x40,0x0B,0x49,0x2A,0x5A,0x93,	//1944-1947
	0x50,0x0A,0x95,0x38,0xF5,0x2D,0x5E,0x05,0x36,0x48,0x0A,0xAD,	//1948-1951
	0x34,0xB5,0xAA,0x58,0x05,0xB2,0x42,0x0D,0xA5,0x2E,0x7D,0x4A,	//1952-1955
	0x54,0x0D,0x4A,0x3D,0x0A,0x95,0x60,0x0A,0x97,0x4C,0x05,0x56,	//1956-1959
	0x36,0xCA,0xB5,0x5A,0x0A,0xD5,0x46,0x06,0xD2,0x30,0x8E,0xA5,	//1960-1963
	0x56,0x0E,0xA5,0x40,0x06,0x4A,0x28,0x6C,0x97,0x4E,0x0A,0x9B,	//1964-1967
	0x3A,0xF5,0x5A,0x5E,0x05,0x6A,0x48,0x0B,0x69,0x34,0xB7,0x52,	//1968-1971
	0x5A,0x0B,0x52,0x42,0x0B,0x25,0x2C,0x96,0x4B,0x52,0x0A,0x4B,	//1972-1975
	0x3D,0x14,0xAB,0x60,0x02,0xAD,0x4A,0x05,0x6D,0x36,0xCB,0x69,	//1976-1979
	0x5C,0x0D,0xA9,0x46,0x0D,0x92,0x30,0x9D,0x25,0x56,0x0D,0x25,	//1980-1983
	0x41,0x5A,0x4D,0x64,0x0A,0x56,0x4E,0x02,0xB6,0x38,0xC5,0xB5,	//1984-1987
	0x5E,0x06,0xD5,0x48,0x0E,0xA9,0x34,0xBE,0x92,0x5A,0x0E,0x92,	//1988-1991
	0x44,0x0D,0x26,0x2C,0x6A,0x56,0x50,0x0A,0x57,0x3D,0x14,0xD6,	//1992-1995
	0x62,0x03,0x5A,0x4A,0x06,0xD5,0x36,0xB6,0xC9,0x5C,0x07,0x49,	//1996-1999
	0x46,0x06,0x93,0x2E,0x95,0x2B,0x54,0x05,0x2B,0x3E,0x0A,0x5B,	//2000-2003
	0x2A,0x55,0x5A,0x4E,0x05,0x6A,0x38,0xFB,0x55,0x60,0x0B,0xA4,	//2004-2007
	0x4A,0x0B,0x49,0x32,0xBA,0x93,0x58,0x0A,0x95,0x42,0x05,0x2D,	//2008-2011
	0x2C,0x8A,0xAD,0x50,0x0A,0xB5,0x3D,0x35,0xAA,0x62,0x05,0xD2,	//2012-2015
	0x4C,0x0D,0xA5,0x36,0xDD,0x4A,0x5C,0x0D,0x4A,0x46,0x0C,0x95,	//2016-2019
	0x30,0x95,0x2E,0x54,0x05,0x56,0x3E,0x0A,0xB5,0x2A,0x55,0xB2,	//2020-2023
	0x50,0x06,0xD2,0x38,0xCE,0xA5,0x5E,0x07,0x25,0x48,0x06,0x4B,	//2024-2027
	0x32,0xAC,0x97,0x56,0x0C,0xAB,0x42,0x05,0x5A,0x2C,0x6A,0xD6,	//2028-2031
	0x52,0x0B,0x69,0x3D,0x77,0x52,0x62,0x0B,0x52,0x4C,0x0B,0x25,	//2032-2035
	0x36,0xDA,0x4B,0x5A,0x0A,0x4B,0x44,0x04,0xAB,0x2E,0xA5,0x5B,	//2036-2039
	0x54,0x05,0xAD,0x3E,0x0B,0x6A,0x2A,0x5B,0x52,0x50,0x0D,0x92,	//2040-2043
	0x3A,0xFD,0x25,0x5E,0x0D,0x25,0x48,0x0A,0x55,0x32,0xB4,0xAD,	//2044-2047
	0x58,0x04,0xB6,0x40,0x05,0xB5,0x2C,0x6D,0xAA,0x52,0x0E,0xC9,	//2048-2051
	0x3F,0x1E,0x92,0x62,0x0E,0x92,0x4C,0x0D,0x26,0x36,0xCA,0x56,	//2052-2055
	0x5A,0x0A,0x57,0x44,0x05,0x56,0x2E,0x86,0xD5,0x54,0x07,0x55,	//2056-2059
	0x40,0x07,0x49,0x28,0x6E,0x93,0x4E,0x06,0x93,0x38,0xF5,0x2B,	//2060-2063
	0x5E,0x05,0x2B,0x46,0x0A,0x5B,0x32,0xB5,0x5A,0x58,0x05,0x6A,	//2064-2067
	0x42,0x0B,0x65,0x2C,0x97,0x4A,0x52,0x0B,0x4A,0x3D,0x1A,0x95,	//2068-2071
	0x62,0x0A,0x95,0x4A,0x05,0x2D,0x34,0xCA,0xAD,0x5A,0x0A,0xB5,	//2072-2075
	0x46,0x05,0xAA,0x2E,0x8B,0xA5,0x54,0x0D,0xA5,0x40,0x0D,0x4A,	//2076-2079
	0x2A,0x7C,0x95,0x4E,0x0C,0x96,0x38,0xF9,0x4E,0x5E,0x05,0x56,	//2080-2083
	0x48,0x0A,0xB5,0x32,0xB5,0xB2,0x58,0x06,0xD2,0x42,0x0E,0xA5,	//2084-2087
	0x2E,0x8E,0x4A,0x50,0x06,0x8B,0x3B,0x0C,0x97,0x60,0x04,0xAB,	//2088-2091
	0x4A,0x05,0x5B,0x34,0xCA,0xD6,0x5A,0x0B,0x6A,0x46,0x07,0x52,	//2092-2095
	0x30,0x97,0x25,0x54,0x0B,0x45,0x3E,0x0A,0x8B,0x28,0x54,0x9B 	//2096-2099
};

//��ʮ�Ľ�����Ϣ��һ����6���ֽڱ�ʾ��ÿ������ʹ����λ���ݡ�
//+-------------------------------------------------------+
//| ��һ�ֽ������λ |  ��һ�ֽ�����6λ�������ֽڹ�46��λ |
//|------------------+------------------------------------|
//|С��������������3 | ÿ������������һ��������������23�� |
//+-------------------------------------------------------+
//С�������������Ѹ�����ʣ�µ�23�������ֱ��Ӧ��23�����ݣ������º��壺
//+-------------------------------------------------------+
//|  ������λ | ���� |                ����                |
//|-----------+------+------------------------------------|
//|     00    | 14�� |  ��ǰ��Ӧ�Ľ���������һ����Ϊ14��  |
//|-----------+------+------------------------------------|
//|     01    | 15�� |  ��ǰ��Ӧ�Ľ���������һ����Ϊ15��  |
//|-----------+------+------------------------------------|
//|     10    | 16�� |  ��ǰ��Ӧ�Ľ���������һ����Ϊ16��  |
//|-----------+------+------------------------------------|
//|     11    | 17�� |  ��ǰ��Ӧ�Ľ���������һ����Ϊ17��  |
//+-------------------------------------------------------+
//����˳��
//С�� �� ���� ��ˮ ���� ���� ���� ���� ���� С�� â�� ����
//С�� ���� ���� ���� ��¶ ��� ��¶ ˪�� ���� Сѩ ��ѩ ����
unsigned char const cSolarTerms[1200]={
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1900-1901
	0x94,0x59,0x69,0xA6,0x65,0x55,0x95,0x55,0x99,0xA9,0x95,0x55,	//1902-1903
	0xC5,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1904-1905
	0x94,0x59,0x66,0xA6,0x65,0x55,0x95,0x55,0x99,0xA9,0x95,0x55,	//1906-1907
	0xC5,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1908-1909
	0x94,0x59,0x66,0xA6,0x65,0x55,0x95,0x55,0x99,0xA9,0x95,0x55,	//1910-1911
	0xC5,0x55,0x9A,0x69,0x99,0x51,0x85,0x56,0x66,0x9A,0x65,0x54,	//1912-1913
	0x91,0x56,0x66,0xA6,0x65,0x55,0x95,0x25,0x69,0xA6,0x95,0x55,	//1914-1915
	0x95,0x55,0x9A,0x69,0x96,0x45,0x85,0x56,0x5A,0x9A,0x59,0x51,	//1916-1917
	0x91,0x56,0x66,0xA6,0x65,0x54,0x95,0x25,0x69,0xA6,0x95,0x55,	//1918-1919
	0x95,0x55,0x9A,0x69,0x96,0x45,0x85,0x55,0x9A,0x9A,0x59,0x51,	//1920-1921
	0x91,0x56,0x66,0xA6,0x65,0x54,0x94,0x59,0x69,0xA6,0x95,0x55,	//1922-1923
	0x95,0x55,0x9A,0x69,0x96,0x45,0x85,0x55,0x9A,0x9A,0x59,0x51,	//1924-1925
	0x91,0x56,0x66,0x9A,0x65,0x54,0x94,0x59,0x69,0xA6,0x65,0x55,	//1926-1927
	0x95,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1928-1929
	0x91,0x56,0x66,0x9A,0x65,0x54,0x94,0x59,0x69,0xA6,0x65,0x55,	//1930-1931
	0x95,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1932-1933
	0x91,0x56,0x66,0x9A,0x65,0x54,0x94,0x59,0x66,0xA6,0x65,0x55,	//1934-1935
	0x95,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1936-1937
	0x91,0x56,0x66,0x9A,0x65,0x54,0x94,0x59,0x66,0xA6,0x65,0x55,	//1938-1939
	0x95,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1940-1941
	0x91,0x56,0x66,0x9A,0x65,0x54,0x94,0x59,0x66,0xA6,0x65,0x55,	//1942-1943
	0x95,0x55,0x69,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x96,0x45,	//1944-1945
	0x85,0x56,0x66,0x9A,0x59,0x54,0x91,0x56,0x66,0xA6,0x65,0x55,	//1946-1947
	0x95,0x25,0x69,0xA6,0x95,0x55,0x55,0x55,0x9A,0x69,0x96,0x45,	//1948-1949
	0x85,0x55,0x9A,0x9A,0x59,0x54,0x91,0x56,0x66,0xA6,0x65,0x55,	//1950-1951
	0x95,0x25,0x69,0xA6,0x95,0x55,0x55,0x55,0x9A,0x69,0x96,0x45,	//1952-1953
	0x85,0x55,0x9A,0x9A,0x59,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1954-1955
	0x95,0x19,0x69,0xA6,0x95,0x55,0x55,0x55,0x9A,0x69,0x96,0x45,	//1956-1957
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1958-1959
	0x94,0x59,0x69,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x95,0x55,	//1960-1961
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1962-1963
	0x94,0x59,0x69,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x95,0x55,	//1964-1965
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1966-1967
	0x94,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x95,0x55,	//1968-1969
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x65,0x54,	//1970-1971
	0x94,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA9,0x95,0x55,	//1972-1973
	0x85,0x55,0x9A,0x69,0x99,0x51,0x91,0x56,0x66,0x9A,0x59,0x54,	//1974-1975
	0x94,0x56,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//1976-1977
	0x85,0x55,0x9A,0x69,0x96,0x51,0x85,0x56,0x5A,0x9A,0x59,0x54,	//1978-1979
	0x94,0x56,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//1980-1981
	0x85,0x55,0x9A,0x69,0x96,0x45,0x85,0x55,0x9A,0x9A,0x59,0x54,	//1982-1983
	0x91,0x56,0x66,0x9A,0x65,0x55,0x55,0x25,0x69,0xA6,0x95,0x55,	//1984-1985
	0x55,0x55,0x9A,0x69,0x96,0x45,0x85,0x55,0x9A,0x6A,0x59,0x51,	//1986-1987
	0x91,0x56,0x66,0x9A,0x65,0x54,0x55,0x19,0x69,0xA6,0x65,0x55,	//1988-1989
	0x55,0x55,0x99,0xA9,0x96,0x45,0x85,0x55,0x9A,0x69,0x99,0x51,	//1990-1991
	0x91,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x69,0xA6,0x65,0x55,	//1992-1993
	0x55,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1994-1995
	0x91,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//1996-1997
	0x55,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//1998-1999
	0x91,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//2000-2001
	0x55,0x55,0x99,0xA9,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//2002-2003
	0x91,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//2004-2005
	0x55,0x55,0x69,0xA6,0x95,0x55,0x85,0x55,0x9A,0x69,0x99,0x51,	//2006-2007
	0x91,0x56,0x66,0x9A,0x59,0x54,0x54,0x56,0x66,0xA6,0x65,0x55,	//2008-2009
	0x55,0x55,0x69,0xA6,0x95,0x55,0x85,0x55,0x9A,0x69,0x96,0x51,	//2010-2011
	0x91,0x56,0x5A,0x9A,0x59,0x54,0x54,0x56,0x66,0x9A,0x65,0x55,	//2012-2013
	0x55,0x55,0x69,0xA6,0x95,0x55,0x85,0x55,0x9A,0x69,0x96,0x45,	//2014-2015
	0x85,0x55,0x9A,0x9A,0x59,0x54,0x51,0x56,0x66,0x9A,0x65,0x55,	//2016-2017
	0x55,0x25,0x69,0xA6,0x95,0x55,0x55,0x55,0x99,0xA9,0x96,0x45,	//2018-2019
	0x85,0x55,0x9A,0x69,0x99,0x54,0x51,0x56,0x66,0x9A,0x65,0x54,	//2020-2021
	0x55,0x19,0x69,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x96,0x45,	//2022-2023
	0x85,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2024-2025
	0x54,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x95,0x55,	//2026-2027
	0x85,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2028-2029
	0x54,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x99,0xA9,0x95,0x55,	//2030-2031
	0x85,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2032-2033
	0x54,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//2034-2035
	0x85,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2036-2037
	0x54,0x59,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//2038-2039
	0x85,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x5A,0x9A,0x59,0x54,	//2040-2041
	0x54,0x56,0x66,0xA6,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//2042-2043
	0x85,0x55,0x9A,0x69,0x96,0x51,0x51,0x55,0x9A,0x9A,0x59,0x54,	//2044-2045
	0x54,0x56,0x66,0x9A,0x65,0x55,0x55,0x55,0x69,0xA6,0x95,0x55,	//2046-2047
	0x85,0x55,0x99,0xA9,0x96,0x45,0x45,0x55,0x9A,0x69,0x99,0x54,	//2048-2049
	0x51,0x56,0x66,0x9A,0x65,0x55,0x55,0x19,0x69,0xA6,0x65,0x55,	//2050-2051
	0x55,0x55,0x99,0xA9,0x96,0x45,0x45,0x55,0x9A,0x69,0x99,0x54,	//2052-2053
	0x51,0x56,0x66,0x9A,0x65,0x55,0x55,0x19,0x66,0xA6,0x65,0x55,	//2054-2055
	0x55,0x55,0x99,0xA9,0x96,0x45,0x45,0x55,0x9A,0x69,0x99,0x51,	//2056-2057
	0x51,0x56,0x66,0x9A,0x65,0x54,0x55,0x19,0x66,0xA6,0x65,0x55,	//2058-2059
	0x55,0x55,0x99,0xA9,0x95,0x55,0x45,0x55,0x9A,0x69,0x99,0x51,	//2060-2061
	0x51,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//2062-2063
	0x55,0x55,0x99,0xA9,0x95,0x55,0x45,0x55,0x9A,0x69,0x99,0x51,	//2064-2065
	0x51,0x56,0x66,0x9A,0x65,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//2066-2067
	0x55,0x55,0x69,0xA6,0x95,0x55,0x45,0x55,0x9A,0x69,0x99,0x51,	//2068-2069
	0x51,0x56,0x5A,0x9A,0x59,0x54,0x54,0x59,0x66,0xA6,0x65,0x55,	//2070-2071
	0x55,0x55,0x69,0xA6,0x95,0x55,0x45,0x55,0x9A,0x69,0x96,0x51,	//2072-2073
	0x51,0x56,0x5A,0x9A,0x59,0x54,0x54,0x56,0x66,0x9A,0x65,0x55,	//2074-2075
	0x55,0x55,0x69,0xA6,0x95,0x55,0x45,0x55,0x9A,0x69,0x96,0x51,	//2076-2077
	0x51,0x55,0x9A,0x6A,0x59,0x54,0x54,0x56,0x66,0x9A,0x65,0x55,	//2078-2079
	0x55,0x55,0x69,0xA6,0x95,0x55,0x45,0x55,0x99,0xA9,0x96,0x45,	//2080-2081
	0x51,0x55,0x9A,0x69,0x99,0x54,0x51,0x56,0x66,0x9A,0x65,0x55,	//2082-2083
	0x55,0x19,0x69,0xA6,0x65,0x55,0x15,0x55,0x99,0xA9,0x96,0x45,	//2084-2085
	0x45,0x55,0x9A,0x69,0x99,0x54,0x51,0x56,0x66,0x9A,0x65,0x55,	//2086-2087
	0x55,0x19,0x66,0xA6,0x65,0x55,0x15,0x55,0x99,0xA9,0x96,0x45,	//2088-2089
	0x45,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2090-2091
	0x55,0x19,0x66,0xA6,0x65,0x55,0x15,0x55,0x99,0xA9,0x95,0x55,	//2092-2093
	0x45,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54,	//2094-2095
	0x54,0x59,0x66,0xA6,0x65,0x55,0x15,0x55,0x99,0xA6,0x95,0x55,	//2096-2097
	0x45,0x55,0x9A,0x69,0x99,0x51,0x51,0x56,0x66,0x9A,0x65,0x54 	//2098-2099
};

//1899�궬������1900�������������������ݽ�������1900�ꡰ���š��ļ����ϡ�
char const cPreDongzhiOrder=-10;

//ÿ�����š���÷����÷��������Ϣ��һ���������ֽڱ�ʾ��
//+---------------------------------------------------+
//|  ��15-11λ |  ��10-6λ  |  ��5-1λ   |   ��ĩλ   |
//|------------+------------+------------+------------|
//|    ��÷    |    ��÷    |    ����    |    ĩ��    |
//+---------------------------------------------------+
//1.��һ�š����Ƕ��������󵽡��žš���ÿ�����š����9�죬��˳������������ʡ����š���Ϣʡ�ԡ�
//2.����������ġ��з����ڡ���������10�죬����ĩ�����ڡ��з�����10���20�죬��ˡ��з�����Ϣʡ�ԡ�
//��÷��Ϣ������������150Ϊ��÷��һ�յ�����������
//��÷��Ϣ������������180Ϊ��÷��һ�յ�����������
//������Ϣ������������180Ϊ������һ�յ�����������
//ĩ����Ϣ������λΪ��1������ʾĩ���������30�죬Ϊ��0����ʾĩ���������20�졣
unsigned short const wExtermSeason[200]={
	0x6261,0x3C2A,0x62E1,0x3CAA,0x6361,0x34E8,0x5B9F,0x8268,0x5C1F,0x7AA6,	//1900-1909
	0x545D,0x7B27,0x54DD,0x7365,0x4A1B,0x73E5,0x4A9B,0x6C23,0x42D9,0x6CA3,	//1910-1919
	0x436C,0x64E1,0x3BAA,0x6261,0x3C2A,0x5A9F,0x3468,0x5B1F,0x84E8,0x535D,	//1920-1929
	0x7A26,0x53DD,0x7AA7,0x4C1B,0x72E5,0x4C9B,0x7365,0x41D9,0x6BA3,0x4259,	//1930-1939
	0x6C23,0x3AAA,0x6461,0x3B2A,0x64E1,0x3368,0x5A1F,0x33E8,0x5A9F,0x7C26,	//1940-1949
	0x52DD,0x7CA6,0x535D,0x71E5,0x4B9B,0x7265,0x4C1B,0x6AA3,0x4459,0x6B23,	//1950-1959
	0x44D9,0x6361,0x3A2A,0x63E1,0x3AAA,0x5C1F,0x32E8,0x5C9F,0x3368,0x51DD,	//1960-1969
	0x7BA6,0x525D,0x7C26,0x4A9B,0x7465,0x4B1B,0x74E5,0x4359,0x6A23,0x43D9,	//1970-1979
	0x6AA3,0x3C17,0x62E1,0x3CAA,0x6361,0x31E8,0x5B9F,0x3268,0x5C1F,0x7AA6,	//1980-1989
	0x545D,0x7B26,0x54DD,0x7364,0x4A1B,0x73E5,0x4A9B,0x6C23,0x42D9,0x6CA3,	//1990-1999
	0x4359,0x61E1,0x3B97,0x6261,0x3C2A,0x5A9F,0x3468,0x5B1F,0x34E8,0x535D,	//2000-2009
	0x7A26,0x53DD,0x7AA6,0x4C1B,0x72E4,0x4C9B,0x7365,0x41D9,0x6BA3,0x4259,	//2010-2019
	0x6C23,0x3A97,0x6461,0x3B17,0x61E1,0x3368,0x5A1F,0x33E8,0x5A9F,0x2C26,	//2020-2029
	0x52DD,0x7CA6,0x535D,0x71E4,0x4B9B,0x7264,0x4C1B,0x6AA3,0x4459,0x6B23,	//2030-2039
	0x41D9,0x6361,0x3A17,0x63E1,0x3AAA,0x5C1F,0x32E8,0x5C9F,0x3368,0x51DD,	//2040-2049
	0x2BA6,0x525D,0x7C26,0x4A9B,0x7464,0x4B1B,0x71E5,0x4359,0x6A23,0x43D9,	//2050-2059
	0x6AA3,0x3C17,0x62E1,0x3C97,0x6361,0x31E8,0x5B9F,0x3268,0x5C1F,0x2AA6,	//2060-2069
	0x545D,0x2B26,0x51DD,0x7364,0x4A1B,0x73E4,0x4A9B,0x6C23,0x42D9,0x6CA3,	//2070-2079
	0x4359,0x61E1,0x3B97,0x6261,0x3C17,0x5A9F,0x3468,0x5B1F,0x31E8,0x535D,	//2080-2089
	0x2A26,0x53DD,0x2AA6,0x4C1B,0x72E4,0x4C9B,0x7364,0x41D9,0x6BA3,0x4259 	//2090-2099
};

#endif //_LUNARDATA_H_