// Pattern.cpp: implementation of the CPattern class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WriteDown.h"
#include "Pattern.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPattern::CPattern() : m_Num(0), m_Modified(FALSE)
{
	LoadPattern(DFLT_F_NAME);
	m_NumDefault = m_Num;

	LoadPattern(USER_F_NAME);
}

CPattern::~CPattern()
{
	// 메모리 해제
	for (int i = 0; i < m_Num; i++){
		delete m_Pattern[i];
		delete m_Value[i];
	}
}

void CPattern::AddPattern(char *pattern, char *value)
{
	_AddPattern(pattern, value);
	m_Modified = TRUE;
}

void CPattern::_AddPattern(char *pattern, char *value)
{
	char *temp;

	// 패턴을 복사함
	temp = new char[strlen(pattern) + 1];
	strcpy(temp, pattern);
	m_Pattern[m_Num] = temp;

	// 값을 복사함
	temp = new char[strlen(value) + 1];
	strcpy(temp, value);
	m_Value[m_Num] = temp;

	m_Num++;
}

void CPattern::LoadPattern(char *filename)
{
	fstream fs(filename, ios::in | ios::nocreate);
	char ptn[MAX_PTN_LEN], val[MAX_VAL_LEN];

	// 파일 열기 에러
	if (fs.fail()){
		CString msg = filename;
		msg += " 파일을 열 수 없습니다";
		AfxMessageBox(msg);
		return;
	}

	// 파일로부터 내용 읽기
	while (!fs.eof()){
		fs.getline(val, MAX_VAL_LEN, '\t');
		fs.getline(ptn, MAX_PTN_LEN, '\n');

		if (strlen(ptn) && strlen(val)) _AddPattern(ptn, val);
	}
}

int CPattern::SavePattern()
{
	if (!m_Modified) return 0;

	fstream fs(USER_F_NAME, ios::out);
	int i;

	// 파일 열기 에러
	if (fs.fail()){
		CString msg = "userptn.txt 파일을 열 수 없습니다";
		AfxMessageBox(msg);
		return 0;
	}

	// 사용자 패턴 저장
	for (i = m_NumDefault; i < m_Num; i++){
		fs << m_Value[i] << '\t' << m_Pattern[i] << endl;
	}

	m_Modified = FALSE;

	return m_Num - m_NumDefault;
}
