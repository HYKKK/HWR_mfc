// Pattern.h: interface for the CPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATTERN_H__58AAECCA_8BBD_4508_8CE8_F0C3A3EBD20B__INCLUDED_)
#define AFX_PATTERN_H__58AAECCA_8BBD_4508_8CE8_F0C3A3EBD20B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream.h>

#define MAX_PATTERN 100
#define MAX_PTN_LEN 200
#define MAX_VAL_LEN 10

class CPattern  
{
public:
	int m_Num;
	int m_NumDefault;
	char* m_Pattern[MAX_PATTERN];
	char* m_Value[MAX_PATTERN];

	void AddPattern(char *pattern, char *value);
	void LoadPattern(char *filename);
	int SavePattern();

	CPattern();
	virtual ~CPattern();

private:
	void _AddPattern(char *pattern, char *value);
	int m_Modified;
};

#endif // !defined(AFX_PATTERN_H__58AAECCA_8BBD_4508_8CE8_F0C3A3EBD20B__INCLUDED_)
