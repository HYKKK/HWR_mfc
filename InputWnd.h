#if !defined(AFX_INPUTWND_H__AF6667B9_2817_4C50_BF1E_8F1FC0F9326C__INCLUDED_)
#define AFX_INPUTWND_H__AF6667B9_2817_4C50_BF1E_8F1FC0F9326C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObPoint.h"

// InputWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputWnd window

class CInputWnd : public CWnd
{
// Construction
public:
	CInputWnd();

// Attributes
public:

// Operations
public:
// Implementation
public:
	int pmX;
	int pmY;
	int mX;
	int mY;
	int initX;
	int initY;
	int endX;
	int endY;
	int pEndY;
	int ppEndY;

	int rb;//중성의 형태변수

	bool cho;
	bool jung;
	bool bTmp;
	bool bTmp2;
	
	CString choTmp;
	CString jungTmp;
	CString jongTmp;

	CString choCode;
	CString jungCode;
	CString jongCode;

	CString chof;
	CString jungf;
	CString jongf;

	CString m_SCode;
	CString lastS;
	CString m_InputDetail;
	void DrawInputPoint(CDC &dc);
	CEdit* m_pPtnExprEdit;
	CEdit* m_pPatternEdit;
	CEdit* m_pPatternEdit1;
	CEdit* m_pMaxXEdit;
	CEdit* m_pMaxYEdit;
	CEdit* m_pSCodeEdit;
	CEdit* m_pDebug;
	CString m_Input;
	CObList m_Points;
	CObList m_InputPoints;

	//bool preventDup(CStdioFile  ,CString ); 
	bool preventDupCho(CString ); 
	bool preventDupJong(CString ); 
	bool preventDupJung(CString ); 
	int makeJShape(CString);
	void MakeDB(CString);
	void clear(void);
	void inputScodeToCho(void);
	void inputScodeToJung(void);
	void inputScodeToJong(void);
	void Clear(void);
	void getKorean(CString);
	CString mergeJaso(CString,CString,CString);
	CString Simplification(CString src);
	char EvalDirection(int dx, int dy, char prev = NULL);
	virtual ~CInputWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInputWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPoint m_PrevInputPoint;
	char m_PrevInputDir;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTWND_H__AF6667B9_2817_4C50_BF1E_8F1FC0F9326C__INCLUDED_)
