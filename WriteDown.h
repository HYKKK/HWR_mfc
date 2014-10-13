// WriteDown.h : main header file for the WRITEDOWN application
//

#if !defined(AFX_WRITEDOWN_H__34C392C3_2DF4_4911_99D7_54C4663599CC__INCLUDED_)
#define AFX_WRITEDOWN_H__34C392C3_2DF4_4911_99D7_54C4663599CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWriteDownApp:
// See WriteDown.cpp for the implementation of this class
//

class CWriteDownApp : public CWinApp
{
public:
	CWriteDownApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteDownApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWriteDownApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDOWN_H__34C392C3_2DF4_4911_99D7_54C4663599CC__INCLUDED_)
