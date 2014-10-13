// WriteDownDlg.h : header file
//

#if !defined(AFX_WRITEDOWNDLG_H__D01D1303_CF44_4047_B820_57E161970F23__INCLUDED_)
#define AFX_WRITEDOWNDLG_H__D01D1303_CF44_4047_B820_57E161970F23__INCLUDED_

#include "InputWnd.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWriteDownDlg dialog

class CWriteDownDlg : public CDialog
{
// Construction
public:
	CInputWnd m_InputWnd;
	CWriteDownDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteDownDlg)
	enum { IDD = IDD_WRITEDOWN_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteDownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWriteDownDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRecognize();
	afx_msg void OnClear();
	afx_msg void OnLearn();
	afx_msg void OnSave();
	afx_msg void OnExit();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePattern();

private:
	 CFont m_font;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtCho();
	afx_msg void OnBnClickedButtJung();
	afx_msg void OnBnClickedButtJong();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDOWNDLG_H__D01D1303_CF44_4047_B820_57E161970F23__INCLUDED_)
